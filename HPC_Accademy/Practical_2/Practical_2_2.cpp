#include <iostream>
#include <math.h>
#include <fstream>


int main(){
    int a;

    do{
        std::cout << " Please enter the maximum square (bigger than 0): ";
        std::cin >> a ;
    }while(a < 1e-8);


    // for (int i = 0; i <a+1; i++){
    //     std::cout << i << " * " << i << " = " << i * i << std::endl;
    // }

    std::ofstream data("squares.dat");

    for(int i=0 ; i <= a+1 ; i++ )
    {
        data << i << " " << i*i << std::endl;
    }
  
    data.close();

    return 0;
}