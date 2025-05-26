#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to find modular inverse of a under modulo m
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++)
        if ((a * x) % m == 1)
            return x;
    return -1; // No inverse exists
}

int isCoprime(int a, int m) {
    int temp, b = m;
    while (b != 0) {
        temp = a % b;
        a = b;
        b = temp;
    }
    return (a == 1);
}

void encrypt(char *plaintext, char *cipher, int a, int b) {
    for (int i = 0; plaintext[i] != '\0'; i++) {
        char ch = toupper(plaintext[i]);
        if (isalpha(ch)) {
            int p = ch - 'A';
            int c = (a * p + b) % 26;
            cipher[i] = c + 'A';
        } else {
            cipher[i] = ch;
        }
    }
    cipher[strlen(plaintext)] = '\0';
}

void decrypt(char *cipher, char *plain, int a, int b) {
    int a_inv = modInverse(a, 26);
    if (a_inv == -1) {
        printf("Decryption not possible. No modular inverse for a = %d\n", a);
        return;
    }

    for (int i = 0; cipher[i] != '\0'; i++) {
        char ch = toupper(cipher[i]);
        if (isalpha(ch)) {
            int c = ch - 'A';
            int p = (a_inv * (c - b + 26)) % 26;
            plain[i] = p + 'A';
        } else {
            plain[i] = ch;
        }
    }
    plain[strlen(cipher)] = '\0';
}

int main() {
    char plaintext[] = "HELLO WORLD";
    char cipher[100], decrypted[100];
    int a = 5, b = 8; // Hardcoded key values

    if (!isCoprime(a, 26)) {
        printf("Invalid key: 'a' must be coprime with 26.\n");
        return 1;
    }

    printf("Plaintext: %s\n", plaintext);
    encrypt(plaintext, cipher, a, b);
    printf("Encrypted: %s\n", cipher);

    decrypt(cipher, decrypted, a, b);
    printf("Decrypted: %s\n", decrypted);

    return 0;
}
