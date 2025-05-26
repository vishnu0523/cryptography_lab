#include <stdio.h>
#include <string.h>

int shift_table[16] = {
    1, 1, 2, 2,
    2, 2, 2, 2,
    1, 2, 2, 2,
    2, 2, 2, 1
};

// PC-1 and PC-2 tables are simplified for demo
int PC1[] = { /* 56 elements */ };
int PC2[] = { /* 48 elements */ };

void left_shift(char *key, int shifts) {
    char temp[28];
    memcpy(temp, key, shifts);
    memmove(key, key + shifts, 28 - shifts);
    memcpy(key + 28 - shifts, temp, shifts);
}

void generate_keys(char *initial_key, char subkeys[16][48]) {
    char key_56[56], C[28], D[28];

    // 1. Apply PC-1 to get 56-bit key (skipped here)
    // Assume PC-1 applied and key_56 is filled

    memcpy(C, key_56, 28);
    memcpy(D, key_56 + 28, 28);

    for (int i = 0; i < 16; i++) {
        left_shift(C, shift_table[i]);
        left_shift(D, shift_table[i]);

        // Combine and apply PC-2
        char CD[56];
        memcpy(CD, C, 28);
        memcpy(CD + 28, D, 28);

        // Apply PC-2 (not shown), store in subkeys[i]
    }
}

void reverse_keys(char keys[16][48], char reversed[16][48]) {
    for (int i = 0; i < 16; i++) {
        memcpy(reversed[i], keys[15 - i], 48);
    }
}

int main() {
    char key[64] = "011011..."; // binary string (example)
    char keys[16][48], reversed_keys[16][48];

    generate_keys(key, keys);
    reverse_keys(keys, reversed_keys);

    printf("Decryption keys generated in reverse order.\n");

    // Here you'd pass reversed_keys into DES rounds for decryption.

    return 0;
}
