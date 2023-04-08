#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <math.h>
#include <chrono>
#include <vector>
#include <experimental/random>
#include <omp.h>


//Function to print nicely the TicTacToe board
template<class T>
void printVector(std::vector<std::vector<T>> const &mat) {
    for (std::vector<T> row: mat)
    {
        for (T val: row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
    std::cout << '\n'<<std::endl;
}
//Function which returns product of 2 matrixes 
template<class T>
std::vector <std::vector<T>> multipMarix(std::vector<std::vector<T>> const &A, std::vector<std::vector<T>> const &B) {
    const int rows_a = A.size();
    const int cols_a = A[0].size();
    const  int cols_b = B[0].size();

    std::vector <std::vector<T>> C(rows_a, std::vector<T>(cols_b, 0));

    for(int i=0;i<rows_a;i++){
        for(int j=0;j<cols_b;j++){
            for(int m=0;m<cols_a;m++){
                C[i][j] += A[i][m] * B[m][j];
            }
        }
    }
    return C;
}
//Function which returns product of 2 matrixes with openMP
template<class T>
std::vector <std::vector<T>> multipMarixParallel(std::vector<std::vector<T>> const &A, std::vector<std::vector<T>> const &B) {
    const int rows_a = A.size();
    const int cols_a = A[0].size();
    const  int cols_b = B[0].size();

    std::vector <std::vector<T>> C(rows_a, std::vector<T>(cols_b, 0));
    #pragma omp parallel for
    for(int i=0;i<rows_a;i++){
        for(int j=0;j<cols_b;j++){
            for(int m=0;m<cols_a;m++){
                C[i][j] += A[i][m] * B[m][j];
            }
        }
    }
    return C;
}
//Function to initialize a matrix(vector of vector) with random variables
template<class T>
std::vector <std::vector<T>> initMarix( int rows, int cols, int range) {

    std::vector<std::vector<int>> Matrix;
    for(int i=0;i<rows;i++){
        std::vector<int> v;
        for(int j=0;j<cols;j++){
            v.push_back(rand() % range + 1); //std::experimental::randint(1, 9);
        }
        Matrix.push_back(v);
     }
    return Matrix;
}


int main()
{
    //Calculate time needed to outperform matrix multiplication
    srand(time(NULL));
    auto start = std::chrono::high_resolution_clock::now();
    auto A = initMarix<int>(500,500,5);
    auto B = initMarix<int>(500,500,5);
    auto C = multipMarix<int>(A,B);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << duration.count() << std::endl;

    auto start_P = std::chrono::high_resolution_clock::now();
    auto A_P = initMarix<int>(500,500,5);
    auto B_P = initMarix<int>(500,500,5);
    auto C_P = multipMarixParallel<int>(A_P,B_P);
    auto stop_P = std::chrono::high_resolution_clock::now();
    auto duration_P = std::chrono::duration_cast<std::chrono::microseconds>(stop_P - start_P);
    std::cout << duration_P.count() << std::endl;
    // printVector(A);
    // printVector(B);
    // printVector(C);
  
  //compile:  g++ matrix_muptiplication_vectros.cpp -fopenmp
  return 0;
}