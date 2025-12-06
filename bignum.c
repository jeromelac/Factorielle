#include "bignum.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdint.h> // For uint32_t

/**
 * @brief Initializes a BigNum with a given capacity.
 *
 * @param bn The BigNum to initialize.
 * @param capacity The initial capacity in bytes.
 */
void bignum_init(BigNum *bn, size_t capacity) {
    bn->digits = (unsigned char *)malloc(capacity);
    if (bn->digits == NULL) {
        perror("Failed to allocate memory for BigNum");
        exit(EXIT_FAILURE);
    }
    memset(bn->digits, 0, capacity);
    bn->size = 1;
    bn->capacity = capacity;
    bn->digits[0] = 1; // Start with 1 for factorial calculations
}

/**
 * @brief Frees the memory used by a BigNum.
 *
 * @param bn The BigNum to free.
 */
void bignum_free(BigNum *bn) {
    if (bn && bn->digits) {
        free(bn->digits);
        bn->digits = NULL;
        bn->size = 0;
        bn->capacity = 0;
    }
}

/**
 * @brief Ensures the BigNum has enough capacity, resizing if necessary.
 *
 * @param bn The BigNum to check/resize.
 * @param required_capacity The minimum required capacity.
 */
static void bignum_ensure_capacity(BigNum *bn, size_t required_capacity) {
    if (bn->capacity < required_capacity) {
        size_t new_capacity = bn->capacity;
        while (new_capacity < required_capacity) {
            new_capacity *= 2;
        }
        unsigned char *new_digits = (unsigned char *)realloc(bn->digits, new_capacity);
        if (new_digits == NULL) {
            perror("Failed to reallocate memory for BigNum");
            bignum_free(bn);
            exit(EXIT_FAILURE);
        }
        bn->digits = new_digits;
        memset(bn->digits + bn->capacity, 0, new_capacity - bn->capacity);
        bn->capacity = new_capacity;
    }
}

/**
 * @brief Multiplies a BigNum by a small integer.
 *
 * @param bn The BigNum to multiply.
 * @param factor The integer factor.
 */
void bignum_multiply_by_int(BigNum *bn, int factor) {
    if (factor == 0) {
        bn->size = 1;
        bn->digits[0] = 0;
        return;
    }
    if (factor == 1) {
        return;
    }

    uint32_t carry = 0;
    for (size_t i = 0; i < bn->size; ++i) {
        uint32_t product = (uint32_t)bn->digits[i] * factor + carry;
        bn->digits[i] = product & 0xFF; // product % 256
        carry = product >> 8;           // product / 256
    }

    while (carry > 0) {
        bignum_ensure_capacity(bn, bn->size + 1);
        bn->digits[bn->size] = carry & 0xFF;
        carry >>= 8;
        bn->size++;
    }
}

/**
 * @brief Converts a BigNum to a hexadecimal string.
 * The caller is responsible for freeing the returned string.
 *
 * @param bn The BigNum to convert.
 * @return A dynamically allocated string with the hex representation.
 */
char *bignum_to_hex_string(const BigNum *bn) {
    if (bn == NULL || bn->size == 0) {
        return NULL;
    }

    // Each byte is 2 hex chars, plus one for null terminator
    char *hex_string = (char *)malloc(bn->size * 2 + 1);
    if (hex_string == NULL) {
        perror("Failed to allocate memory for hex string");
        return NULL;
    }

    // Find the most significant non-zero byte
    size_t first_digit_idx = bn->size - 1;
    while(first_digit_idx > 0 && bn->digits[first_digit_idx] == 0) {
        first_digit_idx--;
    }

    char *ptr = hex_string;
    // Special case for the first byte to avoid leading zero if not necessary
    sprintf(ptr, "%x", bn->digits[first_digit_idx]);
    ptr += strlen(ptr);


    for (long i = first_digit_idx - 1; i >= 0; --i) {
        sprintf(ptr, "%02x", bn->digits[i]);
        ptr += 2;
    }

    *ptr = '\0';
    return hex_string;
}

/**
 * @brief Converts a BigNum to a long double (approximation).
 *
 * @param bn The BigNum to convert.
 * @return The approximate long double value.
 */
long double bignum_to_long_double(const BigNum *bn) {
    long double result = 0.0L;
    // Iterate from the most significant byte to the least significant
    for (long i = bn->size - 1; i >= 0; --i) {
        result = result * 256.0L + bn->digits[i];
    }
    return result;
}

/**
 * @brief Calculates the factorial of n and stores it in a BigNum.
 *
 * @param bn The BigNum to store the result in.
 * @param n The number to calculate the factorial of.
 */
void bignum_factorial(BigNum *bn, int n) {
    // Start with 1
    bignum_init(bn, 16); // Initial capacity, will grow if needed
    bn->digits[0] = 1;
    bn->size = 1;

    if (n <= 1) {
        return;
    }

    for (int i = 2; i <= n; ++i) {
        bignum_multiply_by_int(bn, i);
    }
}
