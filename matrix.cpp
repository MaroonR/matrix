#include "matrix.h"

Matrix::Matrix() {
  length = 1;
  height = 1;
  data[0] = 1;
}

Matrix::Matrix(int l, int h, double d[]) {
  length = l;
  height = h;
  for(int i = 0; i < l*h; i++) {
    data[i] = d[i];
  }
}

Matrix::Matrix(const Matrix& other) {
  this->length = other.length;
  this->height = other.height;
  std::memcpy(this->data, other.data, length*height*sizeof(double));
}

Matrix& Matrix::operator=( const Matrix& other ) {
  this->length = other.length;
  this->height = other.height;
  std::memcpy(this->data, other.data, length*height*sizeof(double));
  return *this;
}

// Default Print Function
void Matrix::printMatrix() {
  std::cout << "| ";
  for(int i = 0; i < (length*height); i++) {
    std::cout << roundf(data[i]*100)/100.0 << " ";
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
double& Matrix::operator()(const int nRow, const int nCol)
{
  if(nRow < length && nCol < height) {
    return data[((nRow-1)*length+(nCol-1))];
  }
  else {
    throw std::runtime_error("Out of range");
  }
}
 
 
  /* Matrix Arithmetic */

Matrix Matrix::add(const Matrix A) {
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
Matrix& Matrix::operator+( const Matrix& other ) {
  Matrix temp = *this;
  for(int i = 0; i < length*height; i++) {
    this->data[i] = temp.data[i] + other.data[i];
  }

  return *this;
}
  
 
Matrix Matrix::multiply(Matrix right) {
	
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
        sum += this->data[i * length + j] * right.data[j*right.length + k];
      } 
      data_temp[result_count] = sum;
      result_count++;
    }
  }
  	
  Matrix r = Matrix(r_length, r_height, data_temp);
  return r;
  	
}

Matrix Matrix::crouts_decomposition() {
  // A = LU
  // L is a lower triangular matrix
  // U is an upper triangular with 1's in the diagonal

  Matrix U = *this;
  Matrix L = *this;

  double sum = 0;
    
  // diagonals in U are 1
  for(int i = 0; i < length*height; i++) {
    if(i%(length+1) == 0) U.data[i] = 1;
    else U.data[i] = 0;
    L.data[i] = 0;
  }

  for (int j = 0; j < length; j++) {
    for(int i = j; i < length; i++) {
      sum = 0;
      for (int k = 0; k < j; k++) {
	sum += (L.data[(i*length) + k] * U.data[(k*length) + j]);
      }
      L.data[(i*length) + j] = data[(i*length) + j] - sum;
    }

    for (int i = j; i < length; i++) {
      sum = 0;
      for(int k = 0; k < j; k++) {
	sum += (L.data[(j*length) + k] * U.data[(k*length) + i]);
      }
      if (L.data[(j*length) + j] == 0) {
	std::cout << "det(L) close to 0!" << std::endl;
      }
      U.data[(j*length) + i] = (data[(length*j) + i] - sum)/L.data[(j*length) + j];
      }
  }

  return L;    
}
  
double Matrix::determinant() {
  // This function expects either a 2x2 matrix or a
  // diagonalized matrix (i.e., an L or a U matrix)
  if(length == 2) {
    return (data[0]*data[3] - data[2]*data[1]);
  }
  else {
    Matrix r = *this;
    //std::cout << "new matrix: " << std::endl;
    r = r.crouts_decomposition();
    //r.printMatrix();
    double det = 1;
    for(int i = 0; i < length; i++) {
      //std::cout << "current multiplicand: " << r.data[(i*length) + i] << std::endl;
      //std::cout << i << "," << i << std::endl;
      det *= r.data[(i*length) + i];
    }
    return det;
  }
}
  
Matrix Matrix::cofactor() {
    
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

  
  
Matrix Matrix::transpose() {
  double transpose[length*height];
  for (int i = 0; i < length; i++) {
    for(int j = 0; j < height; j++) {
      transpose[(j*length) + i] = data[(i*length) + j]; //write rows as columns and columns as rows
    }
  }
  Matrix r = Matrix(length, height, transpose);
  return r;
}
  
Matrix Matrix::inverse() {
  // Check that determinant is not zero
  assert(this->determinant() != 0);
  Matrix inverse = this->cofactor().transpose();
  double determinant = this->determinant();
  for(int i = 0; i < length*height; i++) {
    inverse.data[i] = inverse.data[i]/determinant;
  }
    
  return inverse;
    
}
  
int Matrix::getLength() { return length; }
void Matrix::setLength(int nl) { length = nl; }
int Matrix::getHeight() { return height; }
void Matrix::setHeight(int nh) { height = nh; }


 
Matrix Matrix::getCofactorMatrix(int x, int y) {
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
  //    std::cout << "currect cofactor matrix (det(c) =  " << r.determinant() << std::endl;
  //r.printMatrix();
    
  return r;
}

bool Matrix::swaprows() {
  // check if 0 is in diagonal, modify matrix if needed
  bool swaps = false;
  int swap_row_beg_idx = -1;
  int curr_row_beg_idx = -1;
  for(int i = 0; i < length; i++) {
    if(data[(i*length) + i] == 0) {
      //found 0 in diagonal, need to swap rows
      std::cout << "Found a 0 in row " << i << std::endl;
      curr_row_beg_idx = length*i;
      for(int j = 0; j < height; j++) {
	//check other rows for 0 in same column
	//also check that swapping the current row wouldn't put a 0 in the diagonal again
	if(data[(i%length)+(height*j)] != 0) {
	  //std::cout << "There's not a zero for our column in row " << (height*j) << std::endl;
	  //no zero in that column confirmed
	  //need to check if row element that corresponds to new row's value in the diagonal is a zero
	  swap_row_beg_idx = length*j;
	  if(data[curr_row_beg_idx + j] != 0) {
	    //std::cout << "Element at position (" << i << "," << j << ") is not 0, this row is a match!" << std::endl;
	    //swap rows :)
	    for(int swap_idx = 0; swap_idx < length; swap_idx++) {
	      std::swap(data[swap_row_beg_idx + swap_idx], data[curr_row_beg_idx + swap_idx]);
	    }
	    swaps = !swaps;
	  }
	}
      }
    }
  }
  std::cout << "Is this right?" << std::endl;
  this->printMatrix();
  return swaps;
}
	 
	    
	    
    
