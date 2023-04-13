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

//Function to print nicely the TicTacToe board
template<class T>
void printVector(std::vector<std::vector<T>> const &mat) {
    for (std::vector<T> row: mat)
    {
        std::cout << std::setfill( '-' ) << std::setw(mat.size()*6+1) 
              << '-' << '\n';
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

//Function to print vector
template<class T>
void printVec(std::vector<T> const &vec) {
    for (T val: vec) {
        std::cout << val <<", ";
    }
    std::cout << '\n';
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

//Function to initialize a vector with random values 
template<class T>
std::vector<T> initVec(int rows, int cols) {

    std::vector<int> v;
        for(int i=1;i<cols*rows+1;i++){
            v.push_back(i); 
        }
    return v;
}

//Function to initialize a vector with given value 
template<class T>
std::vector<T> initVec_value(int rows, int value) {

    std::vector<int> v;
        for(int i=0;i<rows;i++){
            v.push_back(value); 
        }
    return v;
}

//Function to find cell in the board
std::tuple<int, int> find_matrix_position(int position, int n) {
    int pos_x = (position-1)/n;
    int pos_y = (position-1)%n;
    return std::make_tuple(pos_x, pos_y);
}

//Function which check if the 'player_sign' is along the whole row
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

//Function which check if the 'player_sign' is along the whole column
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

//Function which check if the 'player_sign' is along the whole diagonal axis (3x3)
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

//Function which check if the 'player_sign' is along the whole diagonal axis (nxn)
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

//Function which check if player won the game
template<class T>
bool Check_winning_game(std::vector<std::vector<T>> const &mat, std::string player_sign) {
    if(Horiz_won(mat,player_sign) || Vert_won(mat,player_sign) || Diag_won(mat,player_sign)){
        return true;
    }
    else{
        return false;
    }

}

//Function which initialzed the board for a game 
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

//Function which perform the 'move' of each player
template<class T>
int UserMove(std::vector<T> &U_poss, std::vector<T> &A_num, int range){
    int user_move=-1;
    do {
        user_move = rand() % range + 1;
        if (std::count(U_poss.begin(), U_poss.end(), user_move) != 0 || 
            std::find(A_num.begin(), A_num.end(), user_move) == A_num.end()) {
            // std::cout << "Invalid input. Please specify a valid position:\n";
            user_move = -1;
        }   
    } while (user_move == -1);
    return user_move;
}

int main()
{
    //Statistics
    int number_of_games=100000;
    // int won_by_X=0;
    // int won_by_O=0;
    // int won_by_none=0;
    int start=0;
    std::vector<int> won_by_X;
    std::vector<int> won_by_O;
    std::vector<int> won_by_none;
    std::vector<int> won_by;
    won_by = initVec_value<int>(number_of_games, 0);
    

        
    // while(start<number_of_games)
    #pragma omp parallel for
    for(int s=0;s<number_of_games;s++){
        srand(time(NULL)+s);

        //Board initialize parameters
        int rows = 4;
        int cols = 4;
        int user_move_X;
        int user_move_O;
        int range = rows * cols;
        std::vector<int> Used_positions;
        std::vector<int> Allowed_numbers;
        std::vector<std::vector<std::string>> Matrix;
        int X, Y;
        bool Game_won_X, Game_won_O, Game_won_h, Game_won_v; 
        
        Used_positions.push_back(0);
        Matrix = initBoard<std::string>(rows, cols);
        Allowed_numbers=initVec<int>(rows, cols);


        for(int k=0;k<rows*cols;k++){
            user_move_X = UserMove(Used_positions, Allowed_numbers, range);
            // std::cout<<user_move_X<<"X"<<'\n';
            std::tie(X,Y) = find_matrix_position(user_move_X,rows);
            Matrix[X][Y] = "X";
            Game_won_X = Check_winning_game(Matrix, "X");
            Used_positions.push_back(user_move_X);

            if(Game_won_X){
                // std::cout<<"You ('X') won the game"<<'\n'<<"Game over"<<'\n';
                won_by[s] = 1;
                // start++;
                break;
            }

            int counter_X = 0;
            int counter_O = 0;
            for (const auto& inner : Matrix) {
                counter_X += std::count(inner.begin(), inner.end(), "X");
                counter_O += std::count(inner.begin(), inner.end(), "O");
            }
            // printVector(Matrix);
            // std::cout<<range/2+1<<"mozliwe, X="<<counter_X<<", O="<<counter_O<<'\n';
            if(counter_X>=static_cast<double>(range)/2){ // || counter_O>=range/2){
                // start++;
                won_by[s] = 0;
                // std::cout<<"Error"<<'\n'<<"Game over"<<'\n';
                break;
            }
            
            user_move_O = UserMove(Used_positions, Allowed_numbers, range);
            // std::cout<<user_move_O<<"Zero"<<'\n';
            std::tie(X,Y) = find_matrix_position(user_move_O,rows);
            Matrix[X][Y] = "O";
            Game_won_O = Check_winning_game(Matrix, "O");
            Used_positions.push_back(user_move_O);

            if(Game_won_O){
                // std::cout<<"You ('O') won the game"<<'\n'<<"Game over"<<'\n';
                won_by[s] = 2;
                // start++;
                break;
            }
        }
        Matrix = initBoard<std::string>(rows, cols);
        Used_positions.erase(Used_positions.begin(), Used_positions.end());  
        std::cout<<static_cast<double>(s)/number_of_games*100<<"%"<<'\n';
    }
    auto Won_by_X = std::count(won_by.begin(), won_by.end(), 1);
    auto Won_by_O = std::count(won_by.begin(), won_by.end(), 2);
    auto Won_by_none = std::count(won_by.begin(), won_by.end(), 0);
    std::cout<<" % won by 'X' = "<<static_cast<double>(Won_by_X)/number_of_games*100<<"%"<<'\n';
    std::cout<<" % won by 'O' = "<<static_cast<double>(Won_by_O)/number_of_games*100<<"%"<<'\n';
    std::cout<<" % won by none = "<<static_cast<double>(Won_by_none)/number_of_games*100<<"%"<<'\n';
    
    
    return 0;
}
