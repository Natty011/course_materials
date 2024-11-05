#include <stdio.h>

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

int main()
{

    return 0;
}

