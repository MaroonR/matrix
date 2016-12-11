#ifndef MATRIX_H
#define MATRIX_H

#include "assert.h"
#include <iostream>
#include <stdexcept>

#define MAX_MATRIX_SIZE 64

class Matrix {

 public:
  // Constructor
  Matrix() {
    length = 1;
    height = 1;
    data[0] = 1;
  }

  // Alt Constructor
  Matrix(int l, int h, double d[]) {
    length = l;
    height = h;
    for(int i = 0; i < l*h; i++) {
      data[i] = d[i];
    }
  }

  // Copy Constructor
 Matrix( const Matrix& other ) {
    length = other.length;
    height = other.height;
    for(int i = 0; i < (length * height); i++) {
      data[i] = other.data[i];

    }
  }
  
 // Assignment Operator
 Matrix& operator=( const Matrix& other ) {
    this->length = other.length;
    this->height = other.height;
    for(int i = 0; i < (other.length)*(other.height); i++) {
    	this->data[i] = other.data[i];
    }

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
  
 // Indexing allows for assignment and reference
 double& operator()(const int nRow, const int nCol)
 {
    if(nRow < length && nCol < height) {
      return data[((nRow-1)*length+(nCol-1))];
    }
    else {
      throw std::runtime_error("Out of range");
    }
 }
 
 
  /* Matrix Arithmetic */

 Matrix add(const Matrix A) {

    //check that A and B have identical dimensions
    assert(length == A.length);
    assert(height == A.height);
    Matrix Result;
    Result = A;
    for(int i = 0; i < A.length*A.height; i++) {
      Result.data[i] = A.data[i] + data[i];
    }

    return Result;
  }

 // Addition Operator Overload
 Matrix& operator+( const Matrix& other ) {
 	Matrix temp = *this;
    for(int i = 0; i < length*height; i++) {
    	this->data[i] = temp.data[i] + other.data[i];
    }
	
    return *this;
  }
  
 
  Matrix multiply(Matrix right) {
  	
  	//check that matrices have appropriate dimensions
  	assert(height == right.length);
  	
    // create temporary array to load into result Matrix
    int r_length = right.length;
  	int r_height = height;
  	double data_temp[length*right.height];
  	
  	double sum = 0;
  	
  	int result_count = 0;
  	
  	for(int i = 0; i < height; i++) {
  	  for(int k = 0; k < right.length; k++) {
  	    sum = 0;
  	    for (int j = 0; j < right.height; j++) {
  	      //sum += L[i * Lw + j] * R[j*Rw + k];
  	      //std::cout << this->data[i * length + j] << "*" << right.data[j*right.length + k] << "=" << this->data[i * length + j] * right.data[j*right.length + k] << std::endl;
  	      sum += this->data[i * length + j] * right.data[j*right.length + k];
  	      //std::cout << "current sum: " << sum << std::endl;
  	    } 
  	    
  	    //std::cout << "Final sum value for index: " << sum << std::endl;
  	    data_temp[result_count] = sum;
  	    result_count++;
  	  }
  	}
  	
    Matrix r = Matrix(r_length, r_height, data_temp);
    return r;
  	
  }
  
  double determinant() {
    if(length == 2) {
      return (data[0]*data[3] - data[2]*data[1]);
    }
    
    // make a copy of our data to work on
    Matrix temp = *this;
    double a;
        
    for(int i = 0; i < length; i++) {
      for(int j = 0; j < i; j++) {
        a = temp.data[(i*length) + j];
        for(int p = 0; p < j; p++) {
          a -= temp.data[(i*length) + p] * temp.data[(p*length)+j];
        }
        temp.data[(i*length) + j] = a/temp.data[(j*length) + j];
      }
      for(int j = i; j < length; j++) {
        a = temp.data[(i*length) + j];
        for (int p = 0; p < i; p++) {
          a -= temp.data[(i*length)+p] * temp.data[(p*length) + j];
        }
        temp.data[(length*i)+j] = a;
      }
    }
    
    
    double D = 1.0;
    for(int i = 0; i < length; i++)
      D *= temp.data[(i*length)+i];
    return D;
  }
  
  Matrix cofactor() {
    
    double cofactors[length*height];
    int curr_slot = 0;
    for(int i = 0; i < length; i++) {
      for(int j = 0; j < height; j++) {
        if(curr_slot % 2 == 0){
          cofactors[curr_slot] = getCofactorMatrix(i, j).determinant();
        }
        else {
          cofactors[curr_slot] = -(getCofactorMatrix(i, j).determinant());
        }
        curr_slot++;
      }
    }
    
    Matrix r = Matrix(length, height, cofactors);
    return r;
  }
  
  Matrix transpose() {
    double transpose[length*height];
    for (int i = 0; i < length; i++) {
      for(int j = 0; j < height; j++) {
        transpose[(j*length) + i] = data[(i*length) + j]; //write rows as columns and columns as rows
      }
    }
    Matrix r = Matrix(length, height, transpose);
    return r;
  }
  
  Matrix inverse() {
    Matrix inverse = this->cofactor().transpose();
    double determinant = this->determinant();
    for(int i = 0; i < length*height; i++) {
      inverse.data[i] = inverse.data[i]/determinant;
    }
    
    return inverse;
    
  }
  
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
  Matrix getCofactorMatrix(int x, int y) {
    // returns cofactor matrix for a matrix's index
    // do this by removing the elements in the current row and col
    
  
    double det_matrix[(length-1)*(height-1)];  // return this after filling with values
    int curr_slot = 0;
    for(int i = 0; i < length; i++) {
      for(int j = 0; j < height; j++) {
        if(i != x && j != y) { 
          //we're not the current row/col
          det_matrix[curr_slot] = data[(i*length)+j];
          curr_slot++;
        }
      }
    }
    
    Matrix r = Matrix(length-1, height-1, det_matrix);
    return r;
  }
  
  int length;
  int height;
  double data[MAX_MATRIX_SIZE];

};


#endif


