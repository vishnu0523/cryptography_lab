#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define ALPHABET_SIZE 26
void monoalphabetic_cipher(char text[], const char cipher_alphabet[]) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (isupper(text[i])) {
            text[i] = toupper(cipher_alphabet[text[i] - 'A']);
        } else if (islower(text[i])) {
            text[i] = tolower(cipher_alphabet[text[i] - 'a']);
        }
    }
}
int main() {
    char text[1000];
    char cipher_alphabet[ALPHABET_SIZE + 1]; 
    
    printf("Enter text to encrypt/decrypt: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0'; 
    
    printf("Enter cipher alphabet (26 unique letters, case insensitive): ");
    fgets(cipher_alphabet, sizeof(cipher_alphabet), stdin);
    cipher_alphabet[strcspn(cipher_alphabet, "\n")] = '\0';

    if (strlen(cipher_alphabet) != ALPHABET_SIZE) {
        printf("Error: Cipher alphabet must be exactly 26 letters.\n");
        return 1;
    }

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        cipher_alphabet[i] = toupper(cipher_alphabet[i]);
    }
    
    monoalphabetic_cipher(text, cipher_alphabet);
    
    printf("Result: %s\n", text);
    
    return 0;
}
