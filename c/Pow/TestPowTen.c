#include <stdio.h>
#include <math.h>

/*function declaration*/
double PowTen(int power);

/*function definition*/
/*Compute 10^power and return the result */
double PowTen(int power)
{
    int index = 1;
    double ten = 10.0;
    double result = 1.0;

    if (power <= 0)
    {
        if(power == 0)
        {
	      printf("%f\n", result);
	      return result;

        }
            
        ten = 1.0/ten;
        power= -power;
    }
    
    result = ten;
    for ( ;index < power; index++)
    {
        result = result * ten;
    }
    printf("%f\n", result);
    
    return result;
}

/*function declaration*/
void TestPowTen();

/*function definition*/
/*Test the PowTen function the massage according to correctntess */

void TestPowTen()
{
    
    int result = 0;
    result = ((pow(10,-1) == PowTen(-1)) && (pow(10,0) == PowTen(0))
              && (pow(10,1) == PowTen(1))&&(pow(10,20) == PowTen(20)));

    if (result == 1)
    {
       puts("'PowTeno()' Function works great");
    }
	else
	{
	   puts("'PowTen()' Function failed");
    }
	        
             
        
}

int main()
{
    
    TestPowTen();

 
    return 0;
}


