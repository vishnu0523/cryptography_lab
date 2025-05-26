#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX 1000
#define ALPHABET_SIZE 26

// English letter frequency order from most to least frequent
const char freq_order[] = "etaoinshrdlcumwfgypbvkjxqz";

// Scoring based on frequency ranking
int letter_score(char ch) {
    ch = tolower(ch);
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (freq_order[i] == ch) return ALPHABET_SIZE - i;
    return 0;
}

int score_plaintext(char *text) {
    int score = 0;
    for (int i = 0; text[i]; i++) {
        if (isalpha(text[i])) score += letter_score(text[i]);
    }
    return score;
}

void decrypt_caesar(char *cipher, int shift, char *output) {
    for (int i = 0; cipher[i]; i++) {
        char c = cipher[i];
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            output[i] = ((c - base - shift + ALPHABET_SIZE) % ALPHABET_SIZE) + base;
        } else {
            output[i] = c;
        }
    }
    output[strlen(cipher)] = '\0';
}

typedef struct {
    int shift;
    int score;
    char text[MAX];
} DecryptionResult;

int compare(const void *a, const void *b) {
    return ((DecryptionResult *)b)->score - ((DecryptionResult *)a)->score;
}

int main() {
    char cipher[MAX];
    int top_n;

    printf("Enter ciphertext (lowercase or uppercase):\n");
    fgets(cipher, MAX, stdin);
    cipher[strcspn(cipher, "\n")] = '\0';

    printf("How many top plaintexts to show? ");
    scanf("%d", &top_n);

    DecryptionResult results[ALPHABET_SIZE];

    for (int shift = 0; shift < ALPHABET_SIZE; shift++) {
        decrypt_caesar(cipher, shift, results[shift].text);
        results[shift].shift = shift;
        results[shift].score = score_plaintext(results[shift].text);
    }

    qsort(results, ALPHABET_SIZE, sizeof(DecryptionResult), compare);

    printf("\nTop %d possible plaintexts:\n", top_n);
    for (int i = 0; i < top_n && i < ALPHABET_SIZE; i++) {
        printf("Shift %2d | Score %4d | %s\n", results[i].shift, results[i].score, results[i].text);
    }

    return 0;
}
