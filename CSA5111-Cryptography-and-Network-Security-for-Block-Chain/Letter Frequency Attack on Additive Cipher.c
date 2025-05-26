#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define ALPHABET_LEN 26
#define MAX_TEXT_LEN 1024
#define MAX_TOP_N 20

// English letter frequency order (most to least common)
const char english_freq_order[ALPHABET_LEN + 1] = "ETAOINSHRDLCUMWFGYPBVKJXQZ";

// Structure for letter and its frequency
typedef struct {
    char letter;
    int count;
} LetterFreq;

// Compare function for qsort (descending by count)
int cmp_freq(const void *a, const void *b) {
    LetterFreq *fa = (LetterFreq *)a;
    LetterFreq *fb = (LetterFreq *)b;
    return fb->count - fa->count;
}

// Decrypt with additive cipher key
void decrypt_with_key(const char *cipher, int key, char *plain) {
    int len = strlen(cipher);
    for (int i = 0; i < len; i++) {
        if (isalpha(cipher[i])) {
            char base = isupper(cipher[i]) ? 'A' : 'a';
            int c = toupper(cipher[i]) - 'A';
            int p = (c - key + 26) % 26;
            plain[i] = base + p;
        } else {
            plain[i] = cipher[i];
        }
    }
    plain[len] = '\0';
}

int main() {
    char cipher[MAX_TEXT_LEN];
    int top_n;

    printf("Enter the ciphertext (A-Z only, spaces allowed):\n");
    fgets(cipher, sizeof(cipher), stdin);
    cipher[strcspn(cipher, "\n")] = '\0'; // Remove newline

    printf("How many top plaintexts to display (max %d)? ", MAX_TOP_N);
    scanf("%d", &top_n);
    if (top_n < 1 || top_n > MAX_TOP_N) top_n = 5;

    // Count frequency of each letter
    int freq[ALPHABET_LEN] = {0};
    int len = strlen(cipher);
    for (int i = 0; i < len; i++) {
        if (isalpha(cipher[i]))
            freq[toupper(cipher[i]) - 'A']++;
    }

    // Build array for sorting
    LetterFreq freq_arr[ALPHABET_LEN];
    for (int i = 0; i < ALPHABET_LEN; i++) {
        freq_arr[i].letter = 'A' + i;
        freq_arr[i].count = freq[i];
    }
    qsort(freq_arr, ALPHABET_LEN, sizeof(LetterFreq), cmp_freq);

    printf("\nTop %d possible plaintexts (in rough order of likelihood):\n", top_n);
    for (int k = 0; k < top_n; k++) {
        // Assume freq_arr[k].letter maps to english_freq_order[k]
        int cipher_letter = freq_arr[k].letter - 'A';
        int assumed_plain = english_freq_order[0] - 'A'; // 'E' by default
        int key = (cipher_letter - assumed_plain + 26) % 26;
        char plain[MAX_TEXT_LEN];
        decrypt_with_key(cipher, key, plain);
        printf("%2d: key=%2d  %s\n", k + 1, key, plain);
    }
    return 0;
}
