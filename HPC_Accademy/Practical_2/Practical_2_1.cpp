#include <iostream>
#include <math.h>



float delta_calc(float a, float b, float c){
    float delta;
    delta = b * b - 4.0 * a * c;
    return delta;
}




int main(){
    float a, b, c, delta;

    std::cout << " Solving a*x*x + b*x + c = 0" << '\n' << "Enter a: ";
    std::cin >> a ;
    std::cout <<"Enter b: ";
    std::cin >> b ;
    std::cout <<"Enter c: ";
    std::cin >> c ;

    if (a==0 && b==0 && c==0){
        std::cout << "  Identity equation, infinity number of solutions" <<std::endl;

    }
    else if (a==0){
        std::cout << " Solution is " << -c/b <<std::endl;
    }
    else if (b==0){
        if (c/a < 1e-8){
            std::cout << " Solution are " << sqrt(-c/a) << " and " << -sqrt(-c/a) <<std::endl;
        }
        else{
            std::cout << " There is no real solution " <<std::endl;
        }
    }
    else if(c==0){
        std::cout << " Solution are " << 0 << " and "<< -b/a <<"." <<std::endl;
    }
    else{
        delta = delta_calc(a, b, c);
        float sq_delta = sqrt(delta);
        float sq_delta_c = sqrt(-delta);
        if (delta >= 1e-8){
            std::cout << " Solution are " << (-b+sq_delta)/(2*a) << " and "<< (-b-sq_delta)/(2*a) <<"." <<std::endl;
        }
        else{
            // std::cout << " There is no real solution " <<std::endl;
            std::cout << "Two complex solutions: " << -b/(2*a) << " + " << sq_delta_c/(2*a) << "i and " << -b/(2*a) << " - " << sq_delta_c/(2*a) << "i" << std::endl;
        }
    }
    return 0;
}

/*
#include <iostream>
#include <cmath>

int main(void)
{
  double a, b, c;
  std::cout << "Enter a, b, and c for the quadratic ax^2+bx+c=0" << std::endl;
  std::cin >> a >> b >> c;

  if( fabs(a) < 1e-8 )
  {
    if( fabs(b) < 1e-8 )
    {
      if( c != 0 )
      {
	std::cout << "No solutions" << std::endl;
      }
      else
      {
	std::cout << "Trivially, all values of x solve this quadratic." << std::endl;
      }
    }
    else
    {
      std::cout << "Equation has a single solution: " << -c / b << std::endl;
    }
    
  }
  else
  {
    const double det = b*b - 4*a*c;
    if( det < 0 )
    {
      std::cout << "No real solutions" << std::endl;
    }
    else if( det > 0 )
    {
      std::cout << "Two real solutions: " << (-b + sqrt(det)) / (2*a)
		<< "and " << (-b - sqrt(det)) / (2*a) << std::endl;
    }
    else
    {
      std::cout << "One solution only: " << -b / (2*a) << std::endl;
    }
  }
  
}
*/