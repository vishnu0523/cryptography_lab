#include <stdio.h>
#include <string.h>

void ecb_encrypt(const char *plaintext, char *ciphertext) {
    // Simple ECB encryption simulation (not secure)
    strcpy(ciphertext, plaintext); // Direct copy for demonstration
}

void cbc_encrypt(const char *plaintext, char *ciphertext, char iv) {
    // Simple CBC encryption simulation (not secure)
    for (int i = 0; i < strlen(plaintext); i++) {
        ciphertext[i] = plaintext[i] ^ iv; // XOR with IV for demonstration
        iv = ciphertext[i]; // Update IV
    }
}

int main() {
    char plaintext[] = "HELLO WORLD";
    char ecb_cipher[50], cbc_cipher[50];
    char iv = 'X'; // Initialization Vector

    ecb_encrypt(plaintext, ecb_cipher);
    cbc_encrypt(plaintext, cbc_cipher, iv);

    printf("ECB Cipher: %s\n", ecb_cipher);
    printf("CBC Cipher: %s\n", cbc_cipher);

    // Error simulation
    cbc_cipher[1] ^= 0x01; // Simulate a bit error in C1
    printf("Corrupted CBC Cipher: %s\n", cbc_cipher);

    return 0;
}
