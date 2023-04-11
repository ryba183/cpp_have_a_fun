#include <iostream>

int main(void){
    int a = -5;
    int b = -2;

    std::cout << ( a / b ) * b + a % b << " == " << a << std::endl;

    return 0;
}