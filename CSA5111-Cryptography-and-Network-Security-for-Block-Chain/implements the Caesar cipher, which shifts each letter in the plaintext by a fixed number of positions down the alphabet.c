#include <stdio.h>
#include <ctype.h>
#include <string.h>
void caesar_cipher(char text[], int shift) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            text[i] = (text[i] - base + shift) % 26 + base;
        }
    }
}
int main() {
    char text[1000];
    int shift;
    printf("Enter text to encrypt/decrypt: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0'; 
    printf("Enter shift value (1-25): ");
    scanf("%d", &shift);
    
    shift = shift % 26;
    if (shift < 0) shift += 26; 
    
    caesar_cipher(text, shift);
    
    printf("Result: %s\n", text);
    
    return 0;
}
