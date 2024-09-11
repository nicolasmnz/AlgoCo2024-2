#include <iostream>
#include <vector>

using namespace std;

// Función para transponer la matriz B
void transpose(vector< vector<int> > &B, vector< vector<int> > &B_T, int d) {
    for (int i = 0; i < d; i++) {
        for (int j = 0; j < d; j++) {
            B_T[j][i] = B[i][j];
        }
    }
}

// Función de multiplicación optimizada utilizando la traspuesta de B
void multiplyOptimized(vector< vector<int> > &A, vector< vector<int> > &B, vector< vector<int> > &C, int d) {
    vector< vector<int> > B_T(d, vector<int>(d));
    transpose(B, B_T, d);
    
    for (int i = 0; i < d; i++) {
        for (int j = 0; j < d; j++) {
            for (int k = 0; k < d; k++) {
                C[i][j] += A[i][k] * B_T[j][k];
            }
        }
    }
}