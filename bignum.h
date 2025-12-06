#ifndef BIGNUM_H
#define BIGNUM_H

#include <stdlib.h>

// A structure to hold the large number
typedef struct {
    unsigned char *digits;
    size_t size; // Number of bytes used
    size_t capacity; // Number of bytes allocated
} BigNum;

// Function prototypes
void bignum_init(BigNum *bn, size_t capacity);
void bignum_free(BigNum *bn);
void bignum_multiply_by_int(BigNum *bn, int factor);
char *bignum_to_hex_string(const BigNum *bn);
long double bignum_to_long_double(const BigNum *bn);
void bignum_factorial(BigNum *bn, int n);

#endif // BIGNUM_H
