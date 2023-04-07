#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <vector>
#include <experimental/random>
#include <omp.h>
#include <algorithm>
#include<tuple>


template<class T>
void printVector(std::vector<std::vector<T>> const &mat) {
    for (std::vector<T> row: mat)
    {
        std::cout << std::setfill( '-' ) << std::setw(mat.size()*6+1) 
              << '-' << '\n';
        // std::cout << "\t\t\t" << std::setfill( '-' ) << std::setw( name.size() + 12 ) 
            //   << '-' << std::endl;
        std::cout << '|';
        for (T val: row) {
            std::cout << std::setfill( ' ' )<<std::setw(3) << val << std::setfill( ' ' )<<std::setw(3) <<'|';
        }
        std::cout << '\n';
    }
    std::cout << std::setfill( '-' ) << std::setw(mat.size()*6+1) 
              << '-' << '\n';
    std::cout << '\n';
}

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

template<class T>
std::vector<T> initVec(int rows, int cols) {

    std::vector<int> v;
        for(int i=1;i<cols*rows+1;i++){
            v.push_back(i); 
        }
    return v;
}

std::tuple <int, int> find_matrix_position_old(int position) {
    int pos_x, pos_y;  
    switch (position) {
        case 1:
            pos_x=0;
            pos_y=0;
            break;
        case 2:
            pos_x=0;
            pos_y=1;
            break;
        case 3:
            pos_x=0;
            pos_y=2;
            break;
        case 4:
            pos_x=1;
            pos_y=0;
            break;
        case 5:
            pos_x=1;
            pos_y=1;
            break;
        case 6:
            pos_x=1;
            pos_y=2;
            break;
        case 7:
            pos_x=2;
            pos_y=0;
            break;
        case 8:
            pos_x=2;
            pos_y=1;
            break;
        case 9:
            pos_x=2;
            pos_y=2;
            break;
    }
    return std::make_tuple(pos_x, pos_y);
}

std::tuple<int, int> find_matrix_position(int position, int n) {
    int pos_x = (position-1)/n;
    int pos_y = (position-1)%n;
    return std::make_tuple(pos_x, pos_y);
}
template<class T>
bool Horiz_won(std::vector<std::vector<T>> const &mat, std::string player_sign) {
    const int rows_a = mat.size();
    const int cols_a = mat[0].size();
    int win_count=0;

    for(int i=0;i<rows_a;i++){
        win_count = 0;
        for(int j=0;j<cols_a;j++){
            if(mat[i][j]==player_sign){
                win_count ++;
            }
        }
        if(win_count==rows_a){
            return true;
        }
    }
    return false;
}

template<class T>
bool Vert_won(std::vector<std::vector<T>> const &mat, std::string player_sign) {
    const int rows_a = mat.size();
    const int cols_a = mat[0].size();
    int win_count=0;

    for(int i=0;i<rows_a;i++){
        win_count = 0;
        for(int j=0;j<cols_a;j++){
            if(mat[j][i]==player_sign){
                win_count ++;
            }
        }
        if(win_count==rows_a){
            return true;
        }
    }
    return false;
}

template<class T>
bool Diag_won_old(std::vector<std::vector<T>> const &mat, std::string player_sign) {
    const int rows_a = mat.size();
    const int cols_a = mat[0].size();
    int win_count=0;
    if(win_count==rows_a){
        return true;
    }

    if(mat[2][0]==player_sign && mat[1][1]==player_sign &&mat[0][2]==player_sign){
        return true;
    }
    else if(mat[0][0]==player_sign && mat[1][1]==player_sign &&mat[2][2]==player_sign){
        return true;
    }
    else{
        return false;
    }
}

template<class T>
bool Diag_won(std::vector<std::vector<T>> const &mat, std::string player_sign) {
    const int rows_a = mat.size();
    const int cols_a = mat[0].size();
    int win_count_u = 0;
    int win_count_d = 0;

    if (rows_a != cols_a) {
        throw std::invalid_argument("Matrix must be square");
    }

    for (int i = 0; i < rows_a; i++) {
        if (mat[i][i] == player_sign) {
            win_count_u++;
        }
        if (mat[i][cols_a - i - 1] == player_sign) {
            win_count_d++;
        }
    }
    if (win_count_u == rows_a || win_count_d == rows_a) {
        return true;
    } else {
        return false;
    }
}

template<class T>
bool Check_winning_game(std::vector<std::vector<T>> const &mat, std::string player_sign) {
    if(Horiz_won(mat,player_sign) || Vert_won(mat,player_sign) || Diag_won(mat,player_sign)){
        return true;
    }
    else{
        return false;
    }

}

template<class T>
std::vector <std::vector<T>> initBoard( int rows, int cols) {
    std::vector<std::vector<std::string>> Matrix;
    for(int i=0;i<rows;i++){
        std::vector<std::string> v;
        for(int j=0;j<cols;j++){
            v.push_back(std::to_string(i*rows+j+1));
        }
        Matrix.push_back(v);
    }
    return Matrix;
}

int main()
{
    srand(time(NULL));
    //Board initialize
    int rows = 5;
    int cols = 5;
    int user_move_X;
    int user_move_O;
    int range = rows * cols;
    std::vector<int> Used_possitions;
    std::vector<int> Allowed_numbers;
    std::vector<std::vector<std::string>> Matrix;
    int X, Y;
    bool Game_won_X, Game_won_O, Game_won_h, Game_won_v; 
    
    Used_possitions.push_back(0);
    Matrix = initBoard<std::string>(rows, cols);
    Allowed_numbers=initVec<int>(rows, cols);
    
    printVector(Matrix);

    for(int k=0;k<rows*cols;k++){

        user_move_X = -1; // Initialize to an invalid value to enter the loop
        std::cout << "Dear User, please specify the position where to put 'X':\n";
        do {
            // std::cin >> user_move_X;
            user_move_X = rand() % range + 1;
            if (std::count(Used_possitions.begin(), Used_possitions.end(), user_move_X) != 0 || 
                std::find(Allowed_numbers.begin(), Allowed_numbers.end(), user_move_X) == Allowed_numbers.end()) {
            // std::cout << "Invalid input. Please specify a valid position:\n";
            user_move_X = -1; // Reset to an invalid value
        }   
        } while (user_move_X == -1);

        std::tie(X,Y) = find_matrix_position(user_move_X,rows);
        Matrix[X][Y] = "X";
        Game_won_X = Check_winning_game(Matrix, "X");

        if(Game_won_X){
            std::cout<<"You ('X') won the game"<<'\n'<<"Game over"<<'\n';
            printVector(Matrix);
            break;
        }

        Used_possitions.push_back(user_move_X);
        if(Used_possitions.size() ==rows*cols+1){
            std::cout<<"end of the game";
            break;
        }

        user_move_O = -1; // Initialize to an invalid value to enter the loop
        std::cout << "Dear User, please specify the position where to put 'O':\n";
        do {
            // std::cin >> user_move_O;
            user_move_O = rand() % range + 1;
            if (std::count(Used_possitions.begin(), Used_possitions.end(), user_move_O) != 0 || 
                std::find(Allowed_numbers.begin(), Allowed_numbers.end(), user_move_O) == Allowed_numbers.end()) {
            // std::cout << "Invalid input. Please specify a valid position:\n";
            user_move_O = -1; // Reset to an invalid value
        }   
        } while (user_move_O == -1);

        std::tie(X,Y) = find_matrix_position(user_move_O,rows);
        Matrix[X][Y] = "O";
        Game_won_O = Check_winning_game(Matrix, "O");

        if(Game_won_O){
            std::cout<<"You ('O') won the game"<<'\n'<<"Game over"<<'\n';
            printVector(Matrix);
            break;
        }

        Used_possitions.push_back(user_move_O);


        printVector(Matrix);
    }  
  return 0;
}


        // user_move_X=0;
        // std::cout << "Dear User pleas specify the position where to put 'X' "<<'\n';
        // while(std::count(Used_possitions.begin(), Used_possitions.end(), user_move_X)!=0 || !std::count(Allowed_numbers.begin(), Allowed_numbers.end(), user_move_X)) {
        //     std::cin >> user_move_X;
        //     std::cout << "Dear User pleas specify the position once more "<<'\n';
        // }