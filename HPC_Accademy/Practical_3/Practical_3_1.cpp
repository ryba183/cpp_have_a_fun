//ODE solver with Eulerian update formula

#include <iostream>
#include <math.h>
#include <fstream>
#include <vector>

//Function to initialize a vector with given value 
template<class T>
std::vector<T> initVec_value(int rows, int value) {

    std::vector<float> v;
        for(int i=0;i<rows;i++){
            v.push_back(value); 
        }
    return v;
}

//Function to print vector
template<class T>
void printVec(std::vector<T> const &vec) {
    for (T val: vec) {
        std::cout << val <<", ";
    }
    std::cout << '\n';
}

float f(float y){
    return std::sqrt(y);
}

int main(){
    int T,n;
    float dt, y_0;

    do{
        std::cout << " Please enter the T value: ";
        std::cin >> T ;
    }while(T < 1e-8);
    do{
        std::cout << " Please enter the dt value: ";
        std::cin >> dt ;
    }while(dt < 1e-8);
    do{
        std::cout << " Please enter the y_0 value: ";
        std::cin >> y_0 ;
    }while(y_0 < 1e-8);


    std::vector<float> y;
    y=initVec_value<float>(T/dt, 0);
    int vect_len = y.size();
    y[0] = y_0;

    std::ofstream data("ODE.dat");
    // data << 0 << " " << y[0] << std::endl;
    for(int i=1; i <=vect_len; i++){
        y[i] = y[i-1] + dt * std::sqrt(y[i-1]);
        data << dt*i << " " << y[i] << std::endl;
    }
    data.close();


    // printVec(y);
    return 0;
}