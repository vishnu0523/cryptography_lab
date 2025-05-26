#include <stdio.h>
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++)
        if ((a * x) % m == 1)
            return x;
    return -1;
}
int inverseMatrix(int m[2][2], int inv[2][2]) {
    int det = m[0][0]*m[1][1] - m[0][1]*m[1][0];
    det = (det % 26 + 26) % 26;

    int detInv = modInverse(det, 26);
    if (detInv == -1) return 0;

    inv[0][0] = ( m[1][1] * detInv) % 26;
    inv[0][1] = (-m[0][1] * detInv + 26) % 26;
    inv[1][0] = (-m[1][0] * detInv + 26) % 26;
    inv[1][1] = ( m[0][0] * detInv) % 26;

    return 1;
}
void multiplyMatrix(int a[2][2], int b[2][2], int res[2][2]) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            res[i][j] = (a[i][0]*b[0][j] + a[i][1]*b[1][j]) % 26;
        }
    }
}

void printMatrix(int mat[2][2]) {
    for (int i = 0; i < 2; i++)
        printf("| %2d %2d |\n", mat[i][0], mat[i][1]);
}

int main() {
    // Plaintext pairs: "he" = [7 4], "lp" = [11 15]
    int P[2][2] = {{7, 11}, {4, 15}}; // columns = plaintext pairs

    // Ciphertext pairs: "FN" = [5 13], "TV" = [19 21]
    int C[2][2] = {{5, 19}, {13, 21}};

    int P_inv[2][2], Key[2][2];

    if (!inverseMatrix(P, P_inv)) {
        printf("Plaintext matrix not invertible under mod 26.\n");
        return 1;
    }

    multiplyMatrix(C, P_inv, Key);

    printf("Recovered Key Matrix (mod 26):\n");
    printMatrix(Key);

    return 0;
}
