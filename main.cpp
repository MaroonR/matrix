#include <iostream>
#include "matrix.h"

/* Test File */

int main() {
  double arr33[9] = { 1, 2, 3,
		                  0, 4, 5,
		                  1, 0, 6 };

  Matrix Z(3,3, arr33);

  std::cout << "Matrix A:" << std::endl;
  Z.printMatrix();
  
  std::cout << "Matrix A * A" << std::endl;
  Z.multiply(Z).printMatrix();
  
  std::cout << "Cofactor Matrix: " << std::endl;
  Z.cofactor().printMatrix();
  
  std::cout << "Adjoint (C^T)" << std::endl;
  Z.cofactor().transpose().printMatrix();
  
  std::cout << "det(A):" << Z.determinant() << std::endl;
  
  std::cout << "\nInverse of A: " << std::endl;
  Z.inverse().printMatrix();
  
  std::cout << "Identity Matrix from these Matrices: " << std::endl;
  Z.multiply(Z.inverse()).printMatrix();

  
  return 0;
}
