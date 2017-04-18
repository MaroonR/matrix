#include <iostream>
#include "matrix.h"

/* Test File */


void test_function(int test_case) {


  Matrix A;

  
  switch(test_case){
  case 6 :
    {
      std::cout << "using 6x6 matrix..." << std::endl;
      double arr66[36] = { 1, 2, 7, 4, 1, 8,
			   2, 3, 8, 5, 9, 1,
			   0, 2, 7, 0, 2, 6,
			   4, 2, 7, 5, 9, 10,
			   0, 0, 3, 2, 7, 4,
			   1, 2, 8, 5, 2, 6 };
      A = Matrix(6,6, arr66);
      break;
    }
  case 5 :
    {
      std::cout << "using 5x5 matrix..." << std::endl;
      double arr55[25] = {1, 3, 3, 2, 5,
			  0, 5, 1, 3, 0,
			  2, 7, 2, 1, 0,
			  6, 2, 2, 0, 6,
                          9, 1, 6, 2, 5};

      A = Matrix(5,5, arr55);

      break;
    }
  case 4 :
    {
      std::cout << "using 4x4 matrix..." << std::endl;
      double arr44[16] = {1, 3, 3, 2,
			  0, 5, 1, 3,
			  2, 7, 2, 1,
			  6, 2, 2, 0 };

      A = Matrix(4,4, arr44);

      break;
    }    
  default:
    std::cout << "Using 3x3 (default)" << std::endl;
    
  
    double arr33[9] = { 3, 3, 2,
		        7, 2, 1,
		        2, 2, 0 };

    A = Matrix(3,3, arr33);
    break;
    
    break;
  }

  std::cout << "Matrix A:" << std::endl;
  A.printMatrix();

  std::cout << "Inverse of A" << std::endl;
  A.inverse().printMatrix();

  std::cout << "Identity Matrix from these Matrices: " << std::endl;
  A.multiply(A.inverse()).printMatrix();
  
}

int main() {
  /*
  std::cout << "Beginning... " << std::endl;
  for(int i = 3; i < 7; i++) {
    test_function(i);
  }
  */
  std::cout << "testing concatenation... " << std::endl;
  double arrA[4] = {1,1,1,1};
  Matrix A = Matrix(2,2,arrA);
  double arrB[4] = {2,2,2,2};
  Matrix B = Matrix(2,2, arrB);
  A.printMatrix();
  B.printMatrix();
  std::cout << "testing concatenation... " << std::endl;
  A.concatenate(B,0).printMatrix();

  return 0;

}


