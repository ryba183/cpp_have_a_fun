#include <iostream>
#include <math.h>
#include <fstream>
#include <array>


void sum(const std::array<int,20> a, std::array<int,20>& b){
    b[0] = a[0];
    for(int i=1;i<20;i++){
        b[i]  = a[i] + b[i-1];
    }
}


void partialSum(const std::array<int,20> a, std::array<int,20>& sums)
{
  int sum = 0;
  for(int i=0 ; i < 20 ; i++)
  {
    sum += a[i];
    sums[i] = sum;
  }
  
}

int main(){

    std::array<int,20> c;// = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20}; 
    std::array<int,20> d;// = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; 

    for(int i=0 ; i < 20 ; i++)
    {
        c[i] = i;
    }

    sum(c,d);

    partialSum(c, d);
    std::cout << "Triangular numbers:" << std::endl;
    for(int i=0 ; i < 20 ; i++)
    {
        std::cout << "d[" << i << "] = " << d[i] << std::endl;
    }
    return 0;

}



