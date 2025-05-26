#include <stdio.h>

// Euclidean algorithm to compute gcd
int gcd(int a, int b) {
    while (b != 0) {
        int temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

// Extended Euclidean Algorithm to find modular inverse
int modInverse(int e, int phi) {
    int t = 0, newt = 1;
    int r = phi, newr = e;

    while (newr != 0) {
        int quotient = r / newr;
        int temp;

        temp = newt;
        newt = t - quotient * newt;
        t = temp;

        temp = newr;
        newr = r - quotient * newr;
        r = temp;
    }

    if (r > 1) return -1;  // No inverse exists
    if (t < 0) t += phi;

    return t;
}

int main() {
    int n = 391;           // Example: n = 17 * 23
    int e = 3;             // Public exponent
    int m = 85;            // Message block with common factor with n

    int factor = gcd(m, n);  // Should return a prime factor of n

    if (factor != 1 && factor != n) {
        printf("Found a factor of n: %d\n", factor);

        int p = factor;
        int q = n / p;

        printf("Other factor: %d\n", q);

        int phi = (p - 1) * (q - 1);
        int d = modInverse(e, phi);

        if (d != -1) {
            printf("Private key d is: %d\n", d);
        } else {
            printf("No modular inverse found.\n");
        }
    } else {
        printf("No useful common factor found.\n");
    }

    return 0;
}
