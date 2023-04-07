#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <math.h>
#include <vector>
#include <experimental/random>


int size_a = 9;
int size_b = 5;
int size_c = 5;
int size_d = 7; 


void matrix_multiplicaiton(vector<vector<int>> &matrix_A, vector<vector<int>> &matrix_B) {
    // matrix_A.size(); /* size of y */
    // matrix_B[0].size(); /* size of x */
    // for (int i = 0; i < rows; i++) {
    //     for (int j = 0; j < cols; j++) {
    //         cout << matrix[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    std::cout << matrix_A.size()<<' '<< matrix_B[0].size();
}


int main()
{
    int A[size_a][size_b], B[size_c][size_d], C[size_a][size_d];
    srand(time(NULL)); // Seed the random number generator

    for(int i=0;i<size_a;i++){
        std::cout<<'|';
        for(int j=0;j<size_b;j++){
            A[i][j] = rand() % 10 + 1; //std::experimental::randint(1, 9);
            std::cout<<' '<<A[i][j]<<' ';
        }
        std::cout<<'|'<<'\n';
    }
    std::cout<<'\n';
    for(int i=0;i<size_c;i++){
        std::cout<<'|';
        for(int j=0;j<size_d;j++){
            B[i][j] = rand() % 10 + 1;
            std::cout<<' '<<B[i][j]<<' ';
        }
        std::cout<<'|'<<'\n';
    }
    std::cout<<'\n';
    for(int i=0;i<size_a;i++){
        for(int j=0;j<size_d;j++){
            C[i][j] = 0;
            for(int m=0;m<size_b;m++){
                C[i][j] += A[i][m] * B[m][j];
            }
        }
    }

    for(int i=0;i<size_a;i++){
        std::cout<<'|';
        for(int j=0;j<size_d;j++){
            std::cout<<' '<<C[i][j]<<' ';
        }
        std::cout<<'|'<<'\n';
    }

    matrix_multiplicaiton(A,B);
    

}


    // for(int i=0;i<size_a;i++){
    //     if(i==1){
    //         std::cout<<'|'<<A[i][0]<<' '<<A[i][1]<<' '<<A[i][2]<<'|'<<'x'<<'|'<<B[i][0]<<' '<<B[i][1]<<' '<<B[i][2]<<'|'<<'='<<'|'<<C[i][0]<<' '<<C[i][1]<<' '<<C[i][2]<<'|'<<'\n';
    //     }
    //     else{
    //         std::cout<<'|'<<A[i][0]<<' '<<A[i][1]<<' '<<A[i][2]<<'|'<<'\t'<<'|'<<B[i][0]<<' '<<B[i][1]<<' '<<B[i][2]<<'|'<<'\t'<<'|'<<C[i][0]<<' '<<C[i][1]<<' '<<C[i][2]<<'|'<<'\n';

    //     }
    // }

//     return 0;

// }