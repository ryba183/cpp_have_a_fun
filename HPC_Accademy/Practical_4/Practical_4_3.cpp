#include <iostream>
#include <math.h>
#include <fstream>
#include <array>


double det(std::array<std::array<int, 3>, 3>& b){
    double d = 0;

    d += b[0][0] * (b[1][1] * b[2][2] - b[2][1]*b[1][2]);
    d -= b[1][1] * (b[1][0] * b[2][2] - b[1][2]*b[2][0]);
    d += b[2][2] * (b[1][0] * b[2][1] - b[1][1]*b[2][0]);

    return d;  
}


double trace(std::array<std::array<int, 3>, 3>& b){
    double sum;
    for(int i=0; i<std::sqrt(sizeof(b)/sizeof(int));i++){
        sum += b[i][i];
    }
    return sum;
}

int main(){
    std::array<std::array<int, 3>, 3> a;// = {1,2,3,4,5,6,7,8,10};

    std::cout<<std::sqrt(sizeof(a)/sizeof(int))<<std::endl;

    for(int i=0 ; i < 3 ; i++)
    {
        for(int j=0 ; j < 3 ; j++)
        {
            std::cout<<"Please provide the number at position ("<<i<<","<<j<<") of the matrix."<<std::endl;
            std::cin >> a[i][j];
        }
    }

    std::cout<< a[0][0] <<' '<< a[0][1] <<' '<< a[0][2] <<'\n'<< a[1][0] <<' '<< a[1][1] <<' '<< a[1][2] <<'\n'<< a[2][0] <<' '<< a[2][1] <<' '<<a[2][2] <<std::endl; 

    double d = det(a);
    double e = trace(a);

    std::cout<<"Trace of a matrix = "<<d<<'\n'<<"Determinant of a matrix = "<<e<<std::endl;

    return 0;
}