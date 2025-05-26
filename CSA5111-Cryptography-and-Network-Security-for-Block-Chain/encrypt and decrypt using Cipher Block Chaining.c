#include <stdio.h>
#include <string.h>

unsigned char xor(unsigned char a, unsigned char b) {
    return a ^ b;
}

// Dummy S-DES Encrypt/Decrypt (XOR with key, for simulation)
unsigned char sdes_encrypt(unsigned char block, unsigned char key) {
    return block ^ key; // Simulated
}

unsigned char sdes_decrypt(unsigned char block, unsigned char key) {
    return block ^ key; // Simulated
}

void encrypt_cbc(unsigned char *plaintext, unsigned char key, unsigned char iv, int len, unsigned char *cipher) {
    unsigned char prev = iv;
    for (int i = 0; i < len; i++) {
        cipher[i] = sdes_encrypt(xor(plaintext[i], prev), key);
        prev = cipher[i];
    }
}

void decrypt_cbc(unsigned char *cipher, unsigned char key, unsigned char iv, int len, unsigned char *plaintext) {
    unsigned char prev = iv;
    for (int i = 0; i < len; i++) {
        plaintext[i] = xor(sdes_decrypt(cipher[i], key), prev);
        prev = cipher[i];
    }
}

int main() {
    unsigned char key = 0b01111110;
    unsigned char iv  = 0b10101010;
    unsigned char plaintext[2] = {0b00000001, 0b00100011};
    unsigned char cipher[2], decrypted[2];

    encrypt_cbc(plaintext, key, iv, 2, cipher);
    printf("Cipher: ");
    for (int i = 0; i < 2; i++) printf("%02X ", cipher[i]);

    decrypt_cbc(cipher, key, iv, 2, decrypted);
    printf("\nDecrypted: ");
    for (int i = 0; i < 2; i++) printf("%02X ", decrypted[i]);
    return 0;
}
