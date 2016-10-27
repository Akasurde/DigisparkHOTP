//
//  main.c
//  HOTP
//
//  Created by Abhijeet Kasurde on 29/09/16.
//  Copyright © 2016 Abhijeet Kasurde. All rights reserved.
//

#include <stdio.h>
#include "digispark.h"

#define MAX_OTP 16 
#define MAX_KEY_LENGTH 21

int main() {
    for (int i = 0; i <= 10; i++) {
        char *c = generateCode("12345678901234567890", i);
        printf("%s\n", c);
    }
    return 0;
}
