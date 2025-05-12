/*******seif a, b **********/


int main()
{
    foo(4.2); // call with double
    foo(5); // call with int
    foo<int>(5); // explicit call to template function with int

    return 0;
}

natty@natty:~/test$ run_gd98 intro17.cpp 
4.2 Generic foo for d
5 Specialized foo (for int param)
5 Generic foo for i


/*******seif c **********/

int main()
{
    foo(4.2); // call with double  -- generic
	// thare is no regulal function just templates functions(general + specilized)
    foo(5); // call with Specialized int ( implicit)
    foo<int>(5); // explicit call to template function with int

    return 0;
}

natty@natty:~/test$ run_gd98 intro17.cpp 
4.2 Generic foo for d
5 template Specialized foo (for int param)
5 template Specialized foo (for int param)
natty@natty:~/test$ 