#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "bignum.h"

// Test for factorial of 0
void test_factorial_zero() {
    printf("Test: Factorial of 0... ");
    BigNum bn;
    bignum_factorial(&bn, 0);
    char *hex_str = bignum_to_hex_string(&bn);
    assert(strcmp(hex_str, "1") == 0);
    free(hex_str);
    bignum_free(&bn);
    printf("OK\n");
}

// Test for factorial of 1
void test_factorial_one() {
    printf("Test: Factorial of 1... ");
    BigNum bn;
    bignum_factorial(&bn, 1);
    char *hex_str = bignum_to_hex_string(&bn);
    assert(strcmp(hex_str, "1") == 0);
    free(hex_str);
    bignum_free(&bn);
    printf("OK\n");
}

// Test for factorial of 10
// 10! = 3628800 = 0x375F00
void test_factorial_ten() {
    printf("Test: Factorial of 10... ");
    BigNum bn;
    bignum_factorial(&bn, 10);
    char *hex_str = bignum_to_hex_string(&bn);
    assert(strcmp(hex_str, "375f00") == 0);
    free(hex_str);
    bignum_free(&bn);
    printf("OK\n");
}

// Test for factorial of 20
// 20! = 2432902008176640000 = 0x21C3677C82B40000
void test_factorial_twenty() {
    printf("Test: Factorial of 20... ");
    BigNum bn;
    bignum_factorial(&bn, 20);
    char *hex_str = bignum_to_hex_string(&bn);
    assert(strcmp(hex_str, "21c3677c82b40000") == 0);
    free(hex_str);
    bignum_free(&bn);
    printf("OK\n");
}


int main() {
    printf("--- Running Bignum Library Tests ---\n");
    test_factorial_zero();
    test_factorial_one();
    test_factorial_ten();
    test_factorial_twenty();
    printf("--- All tests passed ---\n");
    return 0;
}
