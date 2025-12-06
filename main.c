#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "bignum.h"

// Foward declaration
void process_input(long n);
void print_usage(const char *prog_name);


int main(int argc, char *argv[]) {
    long n = -1;
    char *endptr;

    if (argc == 2) {
        // From command line
        errno = 0;
        n = strtol(argv[1], &endptr, 10);
        if (errno != 0 || *endptr != '\0') {
            fprintf(stderr, "Erreur : L'argument n'est pas un nombre valide.\n");
            print_usage(argv[0]);
            return 1;
        }
    } else if (argc == 1) {
        // From prompt
        char buffer[256];
        printf("Veuillez entrer un nombre entier : ");
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
             fprintf(stderr, "Erreur de lecture de l'entrée.\n");
             return 1;
        }
        // Remove newline character if present
        buffer[strcspn(buffer, "\n")] = 0;

        errno = 0;
        n = strtol(buffer, &endptr, 10);
        if (errno != 0 || *endptr != '\0' || buffer[0] == '\0') {
            fprintf(stderr, "Erreur : L'entrée n'est pas un nombre valide.\n");
            print_usage(argv[0]);
            return 1;
        }
    } else {
        print_usage(argv[0]);
        return 1;
    }

    // Validate the input
    if (n < 0 || n > 256) {
        fprintf(stderr, "Erreur : Le nombre doit être compris entre 0 et 256.\n");
        print_usage(argv[0]);
        return 1;
    }

    process_input(n);

    return 0;
}

/**
 * @brief Processes the number, calculates factorial and prints the results.
 *
 * @param n The number to process.
 */
void process_input(long n) {
    printf("Calcul de la factorielle pour %ld...\n", n);

    BigNum bn;
    bignum_factorial(&bn, n);

    // Print in scientific notation
    long double result_ld = bignum_to_long_double(&bn);
    printf("Notation scientifique : %Le\n", result_ld);

    // Print in hexadecimal
    char *hex_string = bignum_to_hex_string(&bn);
    if (hex_string) {
        printf("Hexadécimal : 0x%s\n", hex_string);
        free(hex_string);
    } else {
         fprintf(stderr, "Erreur de conversion en hexadécimal.\n");
    }

    bignum_free(&bn);
}

/**
 * @brief Prints the usage instructions for the program.
 *
 * @param prog_name The name of the program executable.
 */
void print_usage(const char *prog_name) {
    fprintf(stderr, "Usage: %s [nombre]\n", prog_name);
    fprintf(stderr, "  - Si un nombre est fourni, il sera utilisé pour le calcul.\n");
    fprintf(stderr, "  - Sinon, le programme vous demandera d'en entrer un.\n");
    fprintf(stderr, "  Le nombre doit être un entier entre 0 et 256.\n");
}
