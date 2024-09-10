#include <iostream>
#include <vector>

using namespace std;

void multiply ( vector< vector<int> > &A, vector< vector<int> > &B, vector< vector<int> > &C, int d){
    for (int i = 0; i < d; i++){
        for (int j = 0; j < d; j++){
            for (int k = 0; k < d; k++){
                C[i][j] += A[i][k]*B[k][j];
            }
        }
    }
}