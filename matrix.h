
#ifndef MATRIX_H
#define MATRIX_H


/* TO DO :
write copy constructor


*/
#include "assert.h"
#include <iostream>


template <size_t S=0, class T=double>
class Matrix {

 public:
  // Constructor
  Matrix<S, T>() {
    length = 1;
    height = 1;
    data = 1;
  }

  // Alt Constructor
  Matrix<S, T>(int l, int h, int d[]) {
    assert(l*h == S);
    length = l;
    height = h;
    for(int i = 0; i < l*h; i++) {
      data[i] = d[i];
    }
  }

  // Copy Constructor
 Matrix<S, T>( const Matrix<S, T>& other ) {
    std::cout << "copied";
    length = other.length;
    height = other.height;
    for(int i = 0; i < (length * height); i++) {
      data[i] = other.data[i];

    }
  }

  // Assignment Operator
 Matrix<S, T>& operator=( const Matrix<S, T>& other ) {
    std::cout << "this is overloaded";
    std::copy( length, other.length );
    std::copy( height, other.height );
    std::copy( data, other.data );

    return *this;
  }

  // Default Print Function
  void printMatrix() {
    std::cout << "| ";
    for(int i = 0; i < (length*height); i++) {
      std::cout << data[i] << " ";

      if(((i + 1)% length) == 0) {
	std::cout << "|";

	if((i+1) != (length*height))
	  std::cout<< std::endl << "| ";

	else
	  std::cout << std::endl << std::endl;
      }
    }
  }

  // Retrieve individual elements:
  T getElement(int x, int y) {
    if(x < length && y < height) return data[((x-1)*length+(y-1))];
    else
      {
	std::cout << "invalid selection" << std::endl;
	return -1;
      }
  }

  /* Matrix Arithmetic */
 /*
 Matrix<S, T> add(Matrix<S, T> A) {

    //check that A and B have identical dimensions
    assert(length == A.length);
    assert(height == A.height);

    Matrix<T> Result;
    Result = A;
    for(int i = 0; i < A.length*A.height; i++) {
      Result.data[i] = A.data[i] + data[i];
    }

    return Result;
  }

 */

  int getLength() {
    return length;
  }
  void setLength(int nl) {
    length = nl;
  }
  int getHeight() {
    return height;
  }
  void setHeight(int nh) {
    height = nh;
  }





 private:
  T data[S];
  int length;
  int height;

};

// class template specialization:
// template <>
// class Matrix <int> {
// int data [255] ;

// };

#endif

