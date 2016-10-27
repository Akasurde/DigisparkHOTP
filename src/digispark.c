//
//  digispark.c
//  HOTP
//
//  Created by Abhijeet Kasurde on 26/10/16.
//  Copyright © 2016 Abhijeet Kasurde. All rights reserved.
//

#include <stdio.h>
#include "base32.h"
#include "hmac.h"
#include "sha1.h"
#include "digispark.h"
#include <time.h>

char *generateCode(const char *key, long t) {
    long tm = t;
    static char tokenText[7] = "000000";
    uint8_t secret[100];
    uint8_t hash[SHA1_DIGEST_LENGTH];
    
    // Calculate challenge
    uint8_t challenge[8];
    for (int i = 8; i--; tm >>= 8) {
        challenge[i] = tm;
    }
    
    int secretLen = (strlen(key) + 7 ) / 8 * BITS_PER_BASE32_CHAR;
    
    if (secretLen < 0 || secretLen > 100) {
        return tokenText;
    }
    
    if ((secretLen = base32_decode((const uint8_t *) key, secret, secretLen)) < 1)  {
        return tokenText;
    }
    
    
    /* Compute the HMAC_SHA1 of the secret and the challenge.*/
    hmac_sha1(secret, secretLen, challenge, 8, hash, SHA1_DIGEST_LENGTH);
    // Pick the offset where to sample our hash value for the actual verification
    // code.
    int offset = hash[SHA1_DIGEST_LENGTH - 1] & 0xF;
    
    // Compute the truncated hash in a byte-order independent loop.
    unsigned int truncatedHash = 0;
    for (int i = 0; i < 4; ++i) {
        truncatedHash <<= 8;
        truncatedHash  |= hash[offset + i];
    }
    
    // Truncate to a smaller number of digits.
    truncatedHash &= 0x7FFFFFFF;
    truncatedHash %= VERIFICATION_CODE_MODULUS;
    for(int i = 5; i >= 0; i--)
    {
        tokenText[i] = '0' + (truncatedHash % 10);
        truncatedHash /= 10;
    }
    tokenText[6] = '\0';
    
    return tokenText;
}
