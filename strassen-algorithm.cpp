#include <iostream>
#include <vector>

using namespace std;

//Divide una matriz en 4 submatrices.
void split (vector< vector<int> > &A, vector< vector<int> > &B, int row, int col, int d){
    for (int i1 = 0, i2 = row; i1 < d; i1++, i2++){
        for (int j1 = 0, j2 = col; j1 < d; j1++, j2++){
            B[i1][j1] = A[i2][j2];
        }
    }
}

//Une las submatrices resultantes en una sola matriz después de la multiplicación.
void join (vector< vector<int> > &A, vector< vector<int> > &B, int row, int col, int d){
    for (int i1 = 0, i2 = row; i1 < d; i1++, i2++){
        for (int j1 = 0, j2 = col; j1 < d; j1++, j2++){
            B[i2][j2] = A[i1][j1];
        }
    }
}

//
void add (vector< vector<int> > &A, vector< vector<int> > &B, vector< vector<int> > &C, int d){
    for (int i = 0; i < d; i++){
        for (int j = 0; j < d; j++){
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

//
void subtract (vector< vector<int> > &A, vector< vector<int> > &B, vector< vector<int> > &C, int d){
    for (int i = 0; i < d; i++){
        for (int j = 0; j < d; j++){
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

void strassen (vector< vector<int> > &A, vector< vector<int> > &B, vector< vector<int> > &C, int d){
    if (d == 1) { //Caso base
        C[0][0] = A[0][0] * B[0][0];
        return;
    } else { //Padding si no es divisible por 2
        if (d % 2 != 0){
            d++;
            A.resize (d);
            B.resize (d);
            C.resize (d);

            for (int i = 0; i < d; i++){
                A[i].resize (d);
                B[i].resize (d);
                C[i].resize (d);
            }
        }
    }
    int new_d = d/2;
    vector<int> inside (new_d);

    //Inicializa las submatrices
    vector< vector<int> > A11 (new_d, inside);
    vector< vector<int> > A12 (new_d, inside);
    vector< vector<int> > A21 (new_d, inside);
    vector< vector<int> > A22 (new_d, inside);
    vector< vector<int> > B11 (new_d, inside);
    vector< vector<int> > B12 (new_d, inside);
    vector< vector<int> > B21 (new_d, inside);
    vector< vector<int> > B22 (new_d, inside);
    vector< vector<int> > C11 (new_d, inside);
    vector< vector<int> > C12 (new_d, inside);
    vector< vector<int> > C21 (new_d, inside);
    vector< vector<int> > C22 (new_d, inside);

    //Divide las matrices A y B en 4 submatrices
    split(A, A11, 0 , 0, new_d);
    split(A, A12, 0 , new_d, new_d);
    split(A, A21, new_d, 0, new_d);
    split(A, A22, new_d, new_d, new_d);
    split(B, B11, 0 , 0, new_d);
    split(B, B12, 0 , new_d, new_d);
    split(B, B21, new_d, 0, new_d);
    split(B, B22, new_d, new_d, new_d);

    //Matrices para guardar los resultados aritmeticos
    vector< vector<int> > result1 (new_d, inside);
    vector< vector<int> > result2 (new_d, inside);

    /*
            M1 = (A11 + A22)(B11 + B22)
            M2 = (A21 + A22) B11
            M3 = A11 (B12 - B22)
            M4 = A22 (B21 - B11)
            M5 = (A11 + A12) B22
            M6 = (A21 - A11) (B11 + B12)
            M7 = (A12 - A22) (B21 + B22)    
    */

    //  M1 = (A11 + A22)(B11 + B22)
    add(A11, A22, result1, new_d);
    add(B11, B22, result2, new_d);
    vector< vector<int> > M1 (new_d, inside);
    strassen(result1, result2, M1, new_d);

    // M2 = (A21 + A22) B11
    add(A21, A22, result1, new_d);
    vector< vector<int> > M2 (new_d, inside);
    strassen(result1, B11, M2, new_d);

    // M3 = A11 (B12 - B22)
    subtract(B12, B22, result2, new_d);
    vector< vector<int> > M3 (new_d, inside);
    strassen(A11, result2, M3, new_d);

    // M4 = A22 (B21 - B11)
    subtract(B21, B11, result2, new_d);
    vector< vector<int> > M4 (new_d, inside);
    strassen(A22, result2, M4, new_d);

    // M5 = (A11 + A12) B22
    add(A11, A12, result1, new_d);
    vector< vector<int> > M5 (new_d, inside);
    strassen(result1, B22, M5, new_d);

    // M6 = (A21 - A11) (B11 + B12)
    subtract(A21, A11, result1, new_d);
    add(B11, B12, result2, new_d);
    vector< vector<int> > M6 (new_d, inside);
    strassen(result1, result2, M6, new_d);

    // M7 = (A12 - A22) (B21 + B22)
    subtract(A12, A22, result1, new_d);
    add(B21, B22, result2, new_d);
    vector< vector<int> > M7 (new_d, inside);
    strassen(result1, result2, M7, new_d);

    /*
        C11 = M1 + M4 - M5 + M7
        C12 = M3 + M5
        C21 = M2 + M4
        C22 = M1 - M2 + M3 + M6
    */

    // C11 = M1 + M4 - M5 + M7
    add(M1, M4, result1, new_d);
    subtract(result1, M5, result2, new_d);
    add(result2, M7, C11, new_d);

    // C12 = M3 + M5
    add(M3, M5, C12, new_d);

    // C21 = M2 + M4
    add(M2, M4, C21, new_d);

    // C22 = M1 - M2 + M3 + M6
    subtract(M1, M2, result1, new_d);
    add(M3, M6, result2, new_d);
    add(result1, result2, C22, new_d);

    // Unir las submatrices en la matriz resultante
    join(C11, C, 0, 0, new_d);
    join(C12, C, 0, new_d, new_d);
    join(C21, C, new_d, 0, new_d);
    join(C22, C, new_d, new_d, new_d);
}

/*
    Código modificado para Strassen puro, desde la fuente
    Rangelak. (s.f.). Strassen-Matrix-Multiplication/strassen.cpp at master | rangelak/Strassen-Matrix-Multiplication. GitHub. 
    https://github.com/rangelak/Strassen-Matrix-Multiplication/blob/master/strassen.cpp
*/