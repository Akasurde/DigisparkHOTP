//
//  digispark.h
//  HOTP
//
//  Created by Abhijeet Kasurde on 26/10/16.
//  Copyright © 2016 Abhijeet Kasurde. All rights reserved.
//

#ifndef digispark_h
#define digispark_h
#include <stdint.h>

#define VERIFICATION_CODE_MODULUS (1000*1000) // Six digits
#define BITS_PER_BASE32_CHAR      5           // Base32 expands space by 8/5


char *generateCode(const char *secret, uint64_t moving_factor);
int strlength(const char *string);

#endif /* digispark_h */
