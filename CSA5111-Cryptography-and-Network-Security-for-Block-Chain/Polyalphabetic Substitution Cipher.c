#include <stdio.h>
#include <ctype.h>
#include <string.h>

void vigenere_cipher(const char *text, const char *key, int encrypt) {
    int text_len = strlen(text);
    int key_len = strlen(key);
    char processed_key[text_len + 1];
    char result[text_len + 1];
 
    for (int i = 0, j = 0; i < text_len; i++) {
        if (!isalpha(text[i])) {
            processed_key[i] = text[i]; 
            continue;
        }
        processed_key[i] = toupper(key[j % key_len]);
        j++;
    }
    processed_key[text_len] = '\0';
    
    // Perform encryption/decryption
    for (int i = 0; i < text_len; i++) {
        if (!isalpha(text[i])) {
            result[i] = text[i];
            continue;
        }
        
        char text_char = toupper(text[i]);
        char key_char = processed_key[i];
        
        if (encrypt) {
            // Encryption: C = (P + K) mod 26
            result[i] = 'A' + (text_char - 'A' + key_char - 'A') % 26;
        } else {
            // Decryption: P = (C - K + 26) mod 26
            result[i] = 'A' + (text_char - key_char + 26) % 26;
        }
        
        // Preserve original case
        if (islower(text[i])) {
            result[i] = tolower(result[i]);
        }
    }
    result[text_len] = '\0';
    
    printf("Original text: %s\n", text);
    printf("Key: %s\n", key);
    printf("Processed key: %s\n", processed_key);
    printf("Mode: %s\n", encrypt ? "Encryption" : "Decryption");
    printf("Result: %s\n", result);
}

int main() {
    // Predefined text and key
    const char *plaintext = "Attack at dawn!";
    const char *key = "LEMON";
    
    printf("Vigenère Cipher Demonstration\n");
    printf("============================\n\n");
    
    // Encrypt the plaintext
    printf("--- Encryption ---\n");
    vigenere_cipher(plaintext, key, 1);
    
    // Decrypt the ciphertext (using the encrypted result)
    printf("\n--- Decryption ---\n");
    const char *ciphertext = "LXFOPV EF RNHR!";
    vigenere_cipher(ciphertext, key, 0);
    
    return 0;
}
