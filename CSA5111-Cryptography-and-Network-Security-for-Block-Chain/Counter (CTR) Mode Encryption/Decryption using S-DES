#include <stdio.h>

unsigned char sdes_encrypt(unsigned char block, unsigned char key) {
    return block ^ key;  // Simulated S-DES with XOR
}

void encrypt_ctr(unsigned char *plaintext, unsigned char key, unsigned char counter, int len, unsigned char *cipher) {
    for (int i = 0; i < len; i++) {
        unsigned char keystream = sdes_encrypt(counter + i, key);
        cipher[i] = plaintext[i] ^ keystream;
    }
}

void decrypt_ctr(unsigned char *cipher, unsigned char key, unsigned char counter, int len, unsigned char *plaintext) {
    for (int i = 0; i < len; i++) {
        unsigned char keystream = sdes_encrypt(counter + i, key);
        plaintext[i] = cipher[i] ^ keystream;
    }
}

int main() {
    unsigned char key = 0b01111101;
    unsigned char counter = 0b00000000;
    unsigned char plaintext[4] = {0b00000001, 0b00000000, 0b00100000, 0b00000100};
    unsigned char cipher[4], decrypted[4];

    encrypt_ctr(plaintext, key, counter, 4, cipher);
    printf("Cipher: ");
    for (int i = 0; i < 4; i++) printf("%02X ", cipher[i]);

    decrypt_ctr(cipher, key, counter, 4, decrypted);
    printf("\nDecrypted: ");
    for (int i = 0; i < 4; i++) printf("%02X ", decrypted[i]);
    return 0;
}
