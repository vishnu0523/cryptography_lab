#include <stdio.h>
#include <math.h>

int main() {
    double total_keys = 1;
    for (int i = 2; i <= 25; i++)
        total_keys *= i;

    double log2_total = log2(total_keys);
    double log2_unique = 66; // based on cryptographic estimates

    printf("Total possible Playfair keys: %.0f (approx 2^%.1f)\n", total_keys, log2_total);
    printf("Estimated unique Playfair keys: approx 2^%.0f\n", log2_unique);

    return 0;
}
