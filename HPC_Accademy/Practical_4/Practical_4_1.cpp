#include <iostream>
#include <math.h>
#include <fstream>
#include <vector>



int sum(int a, int b){
    return a + b;
}

void decrease(int& a, int b)
{
  a -= b;
}


// void setA(int x){
//     a = x;
// }

int q(double ad, double bd, double cd, double& x1, double& x2){
    if( fabs(ad) < 1e-8 )
    {
        if( fabs(bd) < 1e-8 )
        {
            if( cd != 0 )
        {
	        return 0;
        }
        else
        {
	        return std::numeric_limits<int>::max();
        }
        }
        else
        {
            x1 = -cd / bd;
        return 1;
        }
    }
    else{

        double delta = bd * bd - 4 * ad * cd;
        if(delta >= 0){
            double sd = std::sqrt(delta);
            x1 = -bd + sd / 2 * ad;
            x2 = -bd - sd / 2 * ad;
            if (x1 != x2){
                return 2;
            }
            else {
                return 1;
            }
        }
        else {
            return 0;
        }
    }
}

int qq(double a, double b, double c, double& x1, double& x2)
{
  if( fabs(a) < 1e-8 )
  {
    if( fabs(b) < 1e-8 )
    {
      if( c != 0 )
      {
	    return 0;
      }
      else
      {
	    return std::numeric_limits<int>::max();
      }
    }
    else
    {
      x1 = -c / b;
      return 1;
    }
    
  }
  else
  {
    const double det = b*b - 4*a*c;
    if( det < 0 )
    {
      return 0;
    }
    else if( det > 0 )
    {
      x1 = (-b + sqrt(det)) / (2*a);
      x2 = (-b - sqrt(det)) / (2*a);
      return 2;
    }
    else
    {
      x1 = -b / (2*a);
      return 1;
    }
  }

}

int main(){
    
    int a = 6;
    int b = 5;

    int ad = 0;
    int bd = 0;
    int cd = 3;

    double x1, x2;

    std::cout << sum(2,3) << std::endl;   
    decrease(a, b);
    std::cout << a << ' '<< b << std::endl;

    int solutions = q(ad, bd, cd, x1, x2);
    int solutions2 = qq(ad, bd, cd, x1, x2);

    std::cout<< " The quadratic equation : "<< ad<< "x^2+"<< bd << "x+" << cd << " has exactly " << solutions << " solutions, which are: "<<std::endl;
    std::cout<< x1 << ' ' << x2 <<std::endl;
    std::cout<< " The quadratic equation : "<< ad<< "x^2+"<< bd << "x+" << cd << " has exactly " << solutions2 << " solutions, which are: "<<std::endl;



    return 0;
}