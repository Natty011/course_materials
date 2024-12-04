/***************************************
* Author : Natty
* Reviewer : Idan
* Date : 28 / 11 / 2024
* Last update: 30 / 11 / 2024
*****************************************/

#include <stdio.h> /* printf, puts, __WORDSIZE */
#include "bit_array.h" /*  */



/***************************function declaration**************************/

static void TestBitArrSetAll(void);
static void TestBitArrResetAll(void);
static void TestBitArrSetOn(void);
static void TestBitArrSetOff(void);
static void TestBitArrSetBit(void);
static void TestBitArrGetVal(void);
static void TestBitArrFlipBit(void);
static void TestBitArrMirror(void);
static void TestBitArrRotateLeft(void);
static void TestBitArrRotateRight(void);
static void TestBitArrToString(void);
static void TestBitArrCountOn(void);
static void TestBitArrCountOff(void);

/***************************End of function declaration******************/

int main ()
{

	puts("=====================================================");
    puts("'TestBitArrSetAll()'");
    TestBitArrSetAll();
    puts("=====================================================");
  
    puts("'TestBitArrResetAll()'");
    TestBitArrResetAll();
    puts("=====================================================");
  
    puts("'TestBitArrSetOn()'");
    TestBitArrSetOn();
    puts("=====================================================");
  
    puts("'TestBitArrSetOff()'");
    TestBitArrSetOff();
    puts("=====================================================");
  
    puts("'TestBitArrSetBit()'");
    TestBitArrSetBit();
    puts("=====================================================");
  
    puts("'TestBitArrGetVal()'");
    TestBitArrGetVal();
    puts("=====================================================");
    
    puts("'TestBitArrFlipBit()'");
    TestBitArrFlipBit();
    puts("=====================================================");
    
    puts("'TestBitArrMirror()'");
    TestBitArrMirror();
    puts("=====================================================");
    
    puts("'TestBitArrRotateLeft()'");
    TestBitArrRotateLeft();
    puts("=====================================================");
    
    puts("'TestBitArrRotateRight()'");
    TestBitArrRotateRight();
    puts("=====================================================");
     
    puts("'TestBitArrToString()'");
    TestBitArrToString();
    puts("=====================================================");
     
    puts("'TestBitArrCountOn()'");
    TestBitArrCountOn();
    puts("=====================================================");
    
    puts("'TestBitArrCountOff()'");
    TestBitArrCountOff();
    puts("=====================================================");
    
return 0;
}

   
/********************  TestBitArrSetAll  *************************/

static void TestBitArrSetAll(void)
{
 	bit_arr_t bit_array = 3;
 	printf("bit_array = 3 \n");
 	puts("Expected result: 0xffffffffffffffff ");      
	printf(" BitArrSetAll = %#lx \n", BitArrSetAll(bit_array));
}
/********************  TestBitArrResetAll  *************************/
static void TestBitArrResetAll(void)
{
 	bit_arr_t bit_array = 3;
 	printf("bit_array = 3 \n");
 	puts("Expected result: 0 ");      
    printf(" BitArrResetAll = %#lx \n", BitArrResetAll(bit_array));
    
} 
/********************  TestBitArrSetOn  *************************/
static void TestBitArrSetOn(void)
{
 	bit_arr_t bit_array = 3;
 	printf("bit_array = 3 \n");
 	puts("Expected result: 0x7 ");      
    printf(" BitArrSetOn = %#lx \n", BitArrSetOn(bit_array, 2));
    
}  
/********************  TestBitArrSetOff  *************************/    
static void TestBitArrSetOff(void)
{
 	bit_arr_t bit_array = 3;
 	printf("bit_array = 3 \n");
 	puts("Expected result: 0x1 ");      
	printf(" BitArrSetOff = %#lx \n", BitArrSetOff(bit_array, 1));
    
} 

/********************  TestBitArrSetBit  *************************/    
static void TestBitArrSetBit(void)
{
 	bit_arr_t bit_array = 3;
 	
 	printf("bit_array = 3, index = 2, bool_val = 1 \n");
 	puts("Expected result: 0x7 ");  
 	printf(" BitArrSetBit = %#lx \n", BitArrSetBit(bit_array, 2,  1));
 	
 	printf("bit_array = 3, index = 1, bool_val = 0 \n");
 	puts("Expected result: 0x1 ");      
	printf(" BitArrSetBit = %#lx \n", BitArrSetBit(bit_array, 1,  0));
    
} 

/********************  TestBitArrGetVal  *************************/    
static void TestBitArrGetVal(void)
{
 	bit_arr_t bit_array = 3;
 	
 	
 	printf("bit_array = 3, index = 3\n");
 	puts("Expected result: 0 ");  
 	printf(" BitArrGetVal = %d \n", BitArrGetVal(bit_array, 3));
 	
 	printf("bit_array = 3, index = 2\n");
 	puts("Expected result: 0 ");  
 	printf(" BitArrGetVal = %d \n", BitArrGetVal(bit_array, 2));
 	
 	printf("bit_array = 3, index = 1 \n");
 	puts("Expected result: 1 ");      
	printf(" BitArrGetVal = %d \n", BitArrGetVal(bit_array, 1));
	
	printf("bit_array = 3, index = 0 \n");
 	puts("Expected result: 1 ");      
	printf(" BitArrGetVal = %d \n", BitArrGetVal(bit_array, 0));

} 

/********************  TestBitArrFlipBit  *************************/    
static void TestBitArrFlipBit(void)
{
 	bit_arr_t bit_array = 3;
 	
 	printf("bit_array = 3, index = 3\n");
 	puts("Expected result: 0xb ");  
	printf(" BitArrFlipBit = %#lx \n", BitArrFlipBit(bit_array, 3));
 	
 	printf("bit_array = 3, index = 2\n");
 	puts("Expected result: 0x7 ");  
	printf(" BitArrFlipBit = %#lx \n", BitArrFlipBit(bit_array, 2));
 	
 	printf("bit_array = 3, index = 1 \n");
 	puts("Expected result: 0x1 ");  
	printf(" BitArrFlipBit = %#lx \n", BitArrFlipBit(bit_array, 1));
	
	printf("bit_array = 3, index = 0 \n");
 	puts("Expected result: 0x2 ");  
	printf(" BitArrFlipBit = %#lx \n", BitArrFlipBit(bit_array, 0));

} 
/********************  TestBitArrMirror  *************************/    
static void TestBitArrMirror(void)
{
 	
 	printf("bit_array = 3 \n");
 	puts("Expected result: 0xc000000000000000 ");  
	printf(" BitArrMirror = %#lx \n", BitArrMirror(3));
	
	printf("bit_array = 128 \n");
 	puts("Expected result: 0x100000000000000 ");  
	printf(" BitArrMirror = %#lx \n", BitArrMirror(128));
	
	printf("bit_array = 255 \n");
 	puts("Expected result: 0xff00000000000000 ");  
	printf(" BitArrMirror = %#lx \n", BitArrMirror(255));
	
	printf("bit_array = 0x8073 \n");
 	puts("Expected result: 0xce01000000000000 ");  
	printf(" BitArrMirror = %#lx \n", BitArrMirror(0x8073));
	
	printf("bit_array = 0x6969696969696969 \n");
 	puts("Expected result: 0x9696969696969600 ");  
	printf(" BitArrMirror = %#lx \n", BitArrMirror(0x6969696969696969));

}


/********************  TestBitArrMirror  *************************/   
static void TestBitArrRotateLeft(void)
{
 
    printf("bit_array = 0x80, shifts_num = 1 \n");
 	puts("Expected result: 0x100 ");  
	printf(" BitArrRotateLeft = %#lx \n", BitArrRotateLeft(0x80, 1));
	
	printf("bit_array = 0xff, shifts_num = 8 \n");
 	puts("Expected result: 0xff00 ");  
	printf(" BitArrRotateLeft = %#lx \n", BitArrRotateLeft(0xff , 8));

    printf("bit_array = 0x80, shifts_num = 64 \n");
 	puts("Expected result: 0x80 ");  
	printf(" BitArrRotateLeft = %#lx \n", BitArrRotateLeft(0x80, 64));
	
	printf("bit_array = 0xff, shifts_num = 64 \n");
 	puts("Expected result: 0xff ");  
	printf(" BitArrRotateLeft = %#lx \n", BitArrRotateLeft(0xff , 64));

}

/********************  TestBitArrRotateRight  *************************/   
static void TestBitArrRotateRight(void)
{

	printf("bit_array = 0x80, shifts_num = 1 \n");
 	puts("Expected result: 0x40 ");  
	printf(" BitArrRotateRight = %#lx \n", BitArrRotateRight(0x80, 1));
	
	printf("bit_array = 0x80, shifts_num = 8 \n");
 	puts("Expected result: 0xff00000000000000 ");  
	printf(" BitArrRotateRight = %#lx \n", BitArrRotateRight(0xff , 8));
	
	printf("bit_array = 0x80, shifts_num = 64 \n");
 	puts("Expected result: 0x80 ");  
	printf(" BitArrRotateRight = %#lx \n", BitArrRotateRight(0x80, 64));
	
	printf("bit_array = 0xff, shifts_num = 64 \n");
 	puts("Expected result: 0xff ");  
	printf(" BitArrRotateRight = %#lx \n", BitArrRotateRight(0xff , 64));
	
	printf("bit_array = 0xff1, shifts_num = 1 \n");
 	puts("Expected result: 0x80000000000007f8 ");  
	printf(" BitArrRotateRight = %#lx \n", BitArrRotateRight(0xff1 , 1));
	
	printf("bit_array = 0xff1, shifts_num = 64 \n");
 	puts("Expected result: 0xff1 ");  
	printf(" BitArrRotateRight = %#lx \n", BitArrRotateRight(0xff1 , 64));

}
/********************  TestBitArrToString  *************************/  
 
static void TestBitArrToString(void)
{
	
	char dest[__WORDSIZE+1] = { 0 };
	
	printf("bit_array = 0x80 \n");
	printf(" BitArrToString = %s \n", BitArrToString(0x80, dest));
	
	printf("bit_array = 0x1 \n");
	printf(" BitArrToString = %s \n", BitArrToString(BitArrMirror(0x1), dest));
}

/********************  TestBitArrCountOn  *************************/   
static void TestBitArrCountOn(void)
{
	printf("bit_array = 0x80 \n");
	puts("Expected result: 1 ");  
	printf(" BitArrCountOn = %ld \n", BitArrCountOn(0x80));
	
	printf("bit_array = 0xff ... ff <-> -1  \n");
	puts("Expected result: 64 ");  
	printf(" BitArrCountOn = %ld \n", BitArrCountOn(-1));

}

/********************  TestBitArrCountoff  *************************/   
static void TestBitArrCountOff(void)
{
	printf("bit_array = 0x80 \n");
	puts("Expected result: 63 ");  
	printf(" BitArrCountOff = %ld \n", BitArrCountOff(0x80));
	
	printf("bit_array = 0xff ... ff <-> -1  \n");
	puts("Expected result: 0 ");  
	printf(" BitArrCountOff = %ld \n", BitArrCountOff(-1));

}

