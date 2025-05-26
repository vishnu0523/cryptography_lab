#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

char matrix[SIZE][SIZE] = {
    {'M', 'F', 'H', 'I', 'K'},
    {'U', 'N', 'O', 'P', 'Q'},
    {'Z', 'V', 'W', 'X', 'Y'},
    {'E', 'L', 'A', 'R', 'G'},
    {'D', 'S', 'T', 'B', 'C'}
};

int pos[26][2]; // Stores position of each letter in the matrix

void initializePositionMap() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            char ch = matrix[i][j];
            if (ch == 'I') pos['J' - 'A'][0] = i, pos['J' - 'A'][1] = j;
            pos[ch - 'A'][0] = i;
            pos[ch - 'A'][1] = j;
        }
    }
}

void preprocessMessage(const char* input, char* output) {
    int len = 0;
    for (int i = 0; input[i]; i++) {
        if (isalpha(input[i])) {
            char ch = toupper(input[i]);
            if (ch == 'J') ch = 'I';
            output[len++] = ch;
        }
    }
    output[len] = '\0';

    // Insert filler 'X' between double letters and at end if needed
    char final[500];
    int j = 0;
    for (int i = 0; i < len; i += 2) {
        final[j++] = output[i];
        if (i + 1 < len) {
            if (output[i] == output[i + 1]) {
                final[j++] = 'X';
                i--;
            } else {
                final[j++] = output[i + 1];
            }
        } else {
            final[j++] = 'X';
        }
    }
    final[j] = '\0';
    strcpy(output, final);
}

void encryptPair(char a, char b, char* res) {
    int row1 = pos[a - 'A'][0], col1 = pos[a - 'A'][1];
    int row2 = pos[b - 'A'][0], col2 = pos[b - 'A'][1];

    if (row1 == row2) {
        res[0] = matrix[row1][(col1 + 1) % SIZE];
        res[1] = matrix[row2][(col2 + 1) % SIZE];
    } else if (col1 == col2) {
        res[0] = matrix[(row1 + 1) % SIZE][col1];
        res[1] = matrix[(row2 + 1) % SIZE][col2];
    } else {
        res[0] = matrix[row1][col2];
        res[1] = matrix[row2][col1];
    }
}

void encryptMessage(const char* message) {
    char processed[500];
    preprocessMessage(message, processed);

    printf("Encrypted message:\n");
    for (int i = 0; processed[i]; i += 2) {
        char res[3] = {0};
        encryptPair(processed[i], processed[i + 1], res);
        printf("%c%c ", res[0], res[1]);
    }
    printf("\n");
}

int main() {
    initializePositionMap();

    const char* message = "Must see you over Cadogan West. Coming at once.";
    printf("Original message:\n%s\n", message);

    encryptMessage(message);

    return 0;
}
