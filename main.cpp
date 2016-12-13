#include <iostream>
#include "matrix.h"

/* Test File */


int main() {
  int test_case = 3;
  Matrix A;

  
  switch(test_case){ 
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

  std::cout << "Crout's Method on A" << std::endl;
  A.crouts_decomposition().printMatrix();

  std::cout << "det(A):" << A.determinant() << std::endl;
  std::cout << std::endl;

  std::cout << "Cofactor Matrix: " << std::endl;
  A.cofactor().printMatrix();
  
  std::cout << "Adjoint (C^T)" << std::endl;
  A.cofactor().transpose().printMatrix();
  
  
  std::cout << "\nInverse of A: " << std::endl;
  A.inverse().printMatrix();
  
  std::cout << "Identity Matrix from these Matrices: " << std::endl;
  A.multiply(A.inverse()).printMatrix();
  
  return 0;
}
