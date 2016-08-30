
#include <iostream>
#include "matrix.h"

int main() {
  int arr33[9] = { 1, 4, 2,
		   1, 5, 6,
		   2, 1, 8 };

  int arr13[3] = {1,
		  3,
		  8 };

  int arr31[3] = { 4, 2, 1 };

  Matrix<9> X(3,3, arr33);
  X.printMatrix();

  //  Matrix<9> Y;
  //Y= X;
  //Y.printMatrix();

  // Matrix<int> Z = X;
  // Z = Y.add(X);
  // Z.printMatrix();

  return 0;
}
