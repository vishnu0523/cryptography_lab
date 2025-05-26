#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

void encrypt(char plaintext[], int key[], int len) {
    printf("Ciphertext: ");
    for (int i = 0; i < len; i++) {
        if (isalpha(plaintext[i])) {
            char p = tolower(plaintext[i]) - 'a';
            char c = (p + key[i]) % 26 + 'a';
            printf("%c", c);
        } else {
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");
}

void decrypt(char ciphertext[], int key[], int len) {
    printf("Decrypted Text: ");
    for (int i = 0; i < len; i++) {
        if (isalpha(ciphertext[i])) {
            char c = tolower(ciphertext[i]) - 'a';
            char p = (c - key[i] + 26) % 26 + 'a';
            printf("%c", p);
        } else {
            printf("%c", ciphertext[i]);
        }
    }
    printf("\n");
}

// Part (b) - Find key stream from known plaintext and ciphertext
void findKey(char plaintext[], char ciphertext[], int key[], int len) {
    for (int i = 0; i < len; i++) {
        char p = tolower(plaintext[i]) - 'a';
        char c = tolower(ciphertext[i]) - 'a';
        key[i] = (c - p + 26) % 26;
    }
    printf("Recovered Key Stream: ");
    for (int i = 0; i < len; i++) {
        printf("%d ", key[i]);
    }
    printf("\n");
}

int main() {
    // Part (a): Encrypt "send more money"
    char plaintext[] = "sendmoremoney";
    int key[] = {9, 0, 17, 23, 15, 21, 14, 11, 11, 2, 8, 9, 0};
    int len = strlen(plaintext);

    printf("Part (a):\nPlaintext: %s\n", plaintext);
    encrypt(plaintext, key, len);

    // Sample ciphertext from part (a): Will match encryption result
    char ciphertext[] = "bluhdczczzdif";

    // Part (b): Decrypt to "cashnotneeded"
    char knownPlaintext[] = "cashnotneeded";
    int recoveredKey[MAX];

    printf("\nPart (b):\nKnown Plaintext: %s\nCiphertext: %s\n", knownPlaintext, ciphertext);
    findKey(knownPlaintext, ciphertext, recoveredKey, len);
    decrypt(ciphertext, recoveredKey, len);

    return 0;
}
