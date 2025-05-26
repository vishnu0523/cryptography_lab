#include <stdio.h>
#include <string.h>

// Example mapping: you should adjust this based on known patterns
char substitute(char ch) {
    switch (ch) {
        case '5': return 'T';
        case '3': return 'H';
        case '+': return 'E';
        case '0': return ' ';
        case '6': return 'O';
        case '*': return 'A';
        case ';': return 'N';
        case '8': return 'S';
        case ')': return 'I';
        case '4': return 'L';
        case '2': return 'D';
        case '1': return 'R';
        case '9': return 'M';
        case '.': return 'Y';
        case '-': return 'C';
        case ':': return 'U';
        case '(': return 'B';
        case '?': return 'G';
        case ']': return 'F';
        default: return ch; // leave unchanged
    }
}

int main() {
    char cipher[] = "53+++305))6*;4826)41.)4+);806*;48+860))85;;]8*;:*8+83 (88)5*1;46(;88*96*7;8)**(;485);5*12:*(;4956*2(5*-4)818* ;4069285);)6+8)4++;1(+9;48081;8:8+1;48+85;4)485+528806*81 (19;48;(88;4(+?34;48)4;161;:188;?;";
    char decrypted[1000];
    int i;

    for (i = 0; cipher[i] != '\0'; i++) {
        decrypted[i] = substitute(cipher[i]);
    }
    decrypted[i] = '\0';

    printf("Decrypted message:\n%s\n", decrypted);
    return 0;
}
