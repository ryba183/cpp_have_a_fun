#include <iostream>
#include <cmath>
#include <cstdlib>


void *CreatMatrix(int size){
    int **matrix = new int*[size];
    for(int i = 0; i < size; ++i){
        matrix[i] = new int[size*2+1];
    }

    for(int i=0 ; i < size ; i++)
    {
        for(int j=0 ; j < size*2+1 ; j++)
        {
            matrix[i][j]=0;
        }
    }

    matrix[0][size] = 1;

    for(int i=1 ; i < size ; i++)
    {
        for(int j=1 ; j < size*2+1 ; j++){
            matrix[i][j] = matrix[i-1][j-1] + matrix[i-1][j+1];
        }
        // matrix[i][size-i] = matrix[i-1][size];
    }
    return matrix;
}

// void calcNextRow(const int* prevRow, int* nextRow, int rowNo);


int main(){


    int size = 10;
    int **matrix = (int **)CreatMatrix(size);

    for(int i=0 ; i < size ; i++)
    {
        for(int j=0 ; j < size*2+1 ; j++)
        {
            std::cout<<matrix[i][j]<<' ';
        }
        std::cout<<'\n';
    }

    // Free dynamically allocated memory
    for(int i = 0; i < size; ++i){
        delete [] matrix[i];
    }
    delete [] matrix;


    return 0;
}