#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX 5000
#define ALPHABET 26

// English frequency order from most to least frequent
const char english_freq[] = "etaoinshrdlcumwfgypbvkjxqz";

// Structure to hold frequency of each character
typedef struct {
    char ch;
    int count;
} CharFreq;

int compare_freq(const void *a, const void *b) {
    return ((CharFreq *)b)->count - ((CharFreq *)a)->count;
}

// Score function based on how well text matches common English letters
int score_text(const char *text) {
    int score = 0;
    for (int i = 0; text[i]; i++) {
        char c = tolower(text[i]);
        switch (c) {
            case 'e': score += 13; break;
            case 't': score += 12; break;
            case 'a': score += 11; break;
            case 'o': score += 10; break;
            case 'i': score += 9; break;
            case 'n': score += 8; break;
            case 's': score += 7; break;
            case 'h': score += 6; break;
            case 'r': score += 5; break;
            case 'd': score += 4; break;
            case 'l': score += 3; break;
        }
    }
    return score;
}

void substitute(char *ciphertext, char *map, char *output) {
    for (int i = 0; ciphertext[i]; i++) {
        char c = ciphertext[i];
        if (isalpha(c)) {
            int idx = tolower(c) - 'a';
            char sub = map[idx];
            output[i] = isupper(c) ? toupper(sub) : sub;
        } else {
            output[i] = c;
        }
    }
    output[strlen(ciphertext)] = '\0';
}

void frequency_attack(const char *ciphertext, int top_n) {
    CharFreq freq[ALPHABET] = {0};
    char map[ALPHABET];
    char result[MAX];

    for (int i = 0; i < ALPHABET; i++) {
        freq[i].ch = 'a' + i;
        freq[i].count = 0;
    }

    // Count frequency of each letter
    for (int i = 0; ciphertext[i]; i++) {
        if (isalpha(ciphertext[i])) {
            char c = tolower(ciphertext[i]);
            freq[c - 'a'].count++;
        }
    }

    // Sort by frequency
    qsort(freq, ALPHABET, sizeof(CharFreq), compare_freq);

    // Try permutations of top letters for best guesses
    for (int shift = 0; shift < top_n && shift < ALPHABET; shift++) {
        // Build simple substitution map
        for (int i = 0; i < ALPHABET; i++) {
            map[freq[i].ch - 'a'] = english_freq[(i + shift) % ALPHABET];
        }
        substitute((char *)ciphertext, map, result);
        int s = score_text(result);
        printf("Guess %2d | Score: %4d | %s\n", shift + 1, s, result);
    }
}

int main() {
    char ciphertext[MAX];
    int top_n;

    printf("Enter ciphertext:\n");
    fgets(ciphertext, MAX, stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0';

    printf("How many top guesses to show? ");
    scanf("%d", &top_n);

    printf("\nTop %d plaintext guesses based on frequency analysis:\n", top_n);
    frequency_attack(ciphertext, top_n);

    return 0;
}
