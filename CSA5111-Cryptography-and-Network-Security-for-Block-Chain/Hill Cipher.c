#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MOD 26

int key[2][2] = {
    {9, 4},
    {5, 7}
};

int inverseKey[2][2]; // To be filled after computing inverse

int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++)
        if ((a * x) % m == 1)
            return x;
    return -1;
}

void getKeyInverse() {
    int det = key[0][0]*key[1][1] - key[0][1]*key[1][0];
    det = (det % MOD + MOD) % MOD;
    int detInv = modInverse(det, MOD);

    if (detInv == -1) {
        printf("Key matrix is not invertible!\n");
        return;
    }

    // Inverse matrix using adjugate and modular inverse
    inverseKey[0][0] = (key[1][1] * detInv) % MOD;
    inverseKey[0][1] = (-key[0][1] * detInv + MOD) % MOD;
    inverseKey[1][0] = (-key[1][0] * detInv + MOD) % MOD;
    inverseKey[1][1] = (key[0][0] * detInv) % MOD;
}

void preprocess(char *text) {
    int len = strlen(text), j = 0;
    char clean[500];
    for (int i = 0; i < len; i++) {
        if (isalpha(text[i])) {
            clean[j++] = tolower(text[i]);
        }
    }
    clean[j] = '\0';
    if (j % 2 != 0) {
        clean[j++] = 'x'; // Padding
        clean[j] = '\0';
    }
    strcpy(text, clean);
}

void encrypt(char *text, char *cipher) {
    int len = strlen(text), k = 0;
    for (int i = 0; i < len; i += 2) {
        int x = text[i] - 'a';
        int y = text[i + 1] - 'a';

        int c1 = (key[0][0]*x + key[0][1]*y) % MOD;
        int c2 = (key[1][0]*x + key[1][1]*y) % MOD;

        cipher[k++] = c1 + 'a';
        cipher[k++] = c2 + 'a';
    }
    cipher[k] = '\0';
}

void decrypt(char *cipher, char *plain) {
    int len = strlen(cipher), k = 0;
    for (int i = 0; i < len; i += 2) {
        int x = cipher[i] - 'a';
        int y = cipher[i + 1] - 'a';

        int p1 = (inverseKey[0][0]*x + inverseKey[0][1]*y) % MOD;
        int p2 = (inverseKey[1][0]*x + inverseKey[1][1]*y) % MOD;

        plain[k++] = p1 + 'a';
        plain[k++] = p2 + 'a';
    }
    plain[k] = '\0';
}

int main() {
    char message[] = "meet me at the usual place at ten rather than eight o clock";
    char encrypted[500], decrypted[500];

    preprocess(message);
    getKeyInverse();

    printf("Plaintext (processed): %s\n", message);

    encrypt(message, encrypted);
    printf("Encrypted text: %s\n", encrypted);

    decrypt(encrypted, decrypted);
    printf("Decrypted text: %s\n", decrypted);

    return 0;
}
