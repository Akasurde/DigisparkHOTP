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


char *generateCode(const char *secret, uint64_t moving_factor) {
    char counter[sizeof(moving_factor)];
    size_t i;
    long S;
    
    for (i = 0;i < sizeof(counter); i++) {
        counter[i] = (moving_factor >> ((sizeof(moving_factor) - i -1) * 8)) & 0xFF;
    }
    
    int secretLen = strlength(secret);
    
    uint8_t hash[SHA1_DIGEST_LENGTH];
    hmac_sha1(secret, secretLen, counter, sizeof(moving_factor), hash, SHA1_DIGEST_LENGTH);
    
    uint8_t offset = hash[SHA1_DIGEST_LENGTH - 1] & 0xF;
    S = (((hash[offset] & 0x7f) << 24)
         | ((hash[offset + 1] & 0xff) << 16)
         | ((hash[offset + 2] & 0xff) << 8) | ((hash[offset + 3] & 0xff)));

    S = S % 1000000;
    
    static char tokenText[7] = "000000";
    
    for(int i = 5; i >= 0; i--) {
        tokenText[i] = '0' + (S % 10);
        S /= 10;
    }
    tokenText[6] = '\0';

    return tokenText;
}

int strlength(const char * string) {
    int count = 0;
    while (string[count] != '\0') {
        count++;
    }
    return count;
}
