#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 5
void prepareKeyMatrix(const char *key, char keyMatrix[SIZE][SIZE]) {
    int i, j, k = 0;
    char *keyChars = (char *)malloc(26 * sizeof(char));
    int present[26] = {0};
    for (i = 0; key[i] != '\0'; i++) {
        char c = toupper(key[i]);
        if (c == 'J') c = 'I';
        if (c >= 'A' && c <= 'Z' && !present[c - 'A']) {
            keyChars[k++] = c;
            present[c - 'A'] = 1;
        }
    }
    
    // Fill remaining letters
    present['I' - 'A'] = 1;
    for (i = 0; i < 26; i++) {
        if (i != ('J' - 'A') && !present[i]) {
            keyChars[k++] = 'A' + i;
        }
    }
    
    // Fill the 5x5 matrix
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            keyMatrix[i][j] = keyChars[i * SIZE + j];
        }
    }
    
    free(keyChars);
}

// Find position of a character in the key matrix
void findPosition(char keyMatrix[SIZE][SIZE], char c, int *row, int *col) {
    if (c == 'J') c = 'I';
    
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (keyMatrix[i][j] == c) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

// Encrypt a digraph
void encryptDigraph(char keyMatrix[SIZE][SIZE], char a, char b) {
    int row1, col1, row2, col2;
    
    findPosition(keyMatrix, a, &row1, &col1);
    findPosition(keyMatrix, b, &row2, &col2);
    
    if (row1 == row2) {
        printf("%c%c", keyMatrix[row1][(col1 + 1) % SIZE], keyMatrix[row2][(col2 + 1) % SIZE]);
    } else if (col1 == col2) {
        printf("%c%c", keyMatrix[(row1 + 1) % SIZE][col1], keyMatrix[(row2 + 1) % SIZE][col2]);
    } else {
        printf("%c%c", keyMatrix[row1][col2], keyMatrix[row2][col1]);
    }
}

// Process plaintext (add X between double letters and at end if needed)
void processPlaintext(char *text) {
    int len = strlen(text);
    char processed[1000] = "";
    int j = 0;
    
    for (int i = 0; i < len; ) {
        if (!isalpha(text[i])) {
            i++;
            continue;
        }
        
        char first = toupper(text[i++]);
        if (first == 'J') first = 'I';
        
        char second;
        if (i < len && isalpha(text[i])) {
            second = toupper(text[i++]);
            if (second == 'J') second = 'I';
        } else {
            second = 'X';
        }
        
        if (first == second) {
            processed[j++] = first;
            processed[j++] = 'X';
            i--;
        } else {
            processed[j++] = first;
            processed[j++] = second;
        }
    }
    
    if (j % 2 != 0) {
        processed[j++] = 'X';
    }
    processed[j] = '\0';
    
    strcpy(text, processed);
}

int main() {
    // Predefined key and plaintext
    const char *key = "PLAYFAIREXAMPLE";
    char plaintext[] = "Hide the gold in the tree stump";
    
    char keyMatrix[SIZE][SIZE];
    
    // Prepare the key matrix
    prepareKeyMatrix(key, keyMatrix);
    
    // Process the plaintext
    processPlaintext(plaintext);
    
    printf("Playfair Cipher Demonstration\n");
    printf("============================\n\n");
    
    printf("Key: %s\n", key);
    printf("Original Plaintext: Hide the gold in the tree stump\n");
    
    printf("\nKey Matrix:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", keyMatrix[i][j]);
        }
        printf("\n");
    }
    
    printf("\nProcessed Plaintext: %s\n", plaintext);
    printf("Encrypted Text: ");
    
    // Encrypt each digraph
    for (int i = 0; plaintext[i] != '\0'; i += 2) {
        encryptDigraph(keyMatrix, plaintext[i], plaintext[i + 1]);
    }
    printf("\n");
    
    return 0;
}
