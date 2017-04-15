#include "matrix.h"


Matrix::Matrix() {
  width = 1;
  height = 1;
  data[0] = 1;
}

Matrix::Matrix(int h, int w, double d[]) {
  width = w;
  height = h;
  for(int i = 0; i < w*h; i++) {
    data[i] = d[i];
  }
}

Matrix::Matrix(const Matrix& other) {
  this->width = other.width;
  this->height = other.height;
  std::memcpy(this->data, other.data, width*height*sizeof(double));
}

Matrix& Matrix::operator=( const Matrix& other ) {
  this->width = other.width;
  this->height = other.height;
  std::memcpy(this->data, other.data, width*height*sizeof(double));
  return *this;
}

// Default Print Function -- all print statements need to be removed.
void Matrix::printMatrix() {
  std::cout << "| ";
  double curr_val;
  for(int i = 0; i < (width*height); i++) {
    curr_val = roundf(data[i]*100)/100.0;
    if(curr_val == 0) {
      std::cout << abs(curr_val) << " ";
    }
    else std::cout << curr_val << " ";
    if(((i + 1)% width) == 0) {
      std::cout << "|";
      if((i+1) != (width*height))
	std::cout<< std::endl << "| ";
      else
	std::cout << std::endl << std::endl;
    }
  }
}

// Indexing allows for assignment and reference
double& Matrix::operator()(const int nRow, const int nCol)
{
  if(nRow < width && nCol < height) {
    return data[((nRow-1)*width+(nCol-1))];
  }
  else {
    throw std::runtime_error("Out of range");
  }
}

/* Matrix Arithmetic */

Matrix Matrix::add(const Matrix A) {
  //check that A and B have identical dimensions
  assert(width == A.width);
  assert(height == A.height);
  Matrix Result = A;
  for(int i = 0; i < A.width*A.height; i++) {
    Result.data[i] = A.data[i] + data[i];
  }
  return Result;
}
// Addition Operator Overload
Matrix& Matrix::operator+( const Matrix& other ) {
  Matrix temp = *this;
  for(int i = 0; i < width*height; i++) {
    this->data[i] = temp.data[i] + other.data[i];
  }
  return *this;
}



Matrix Matrix::subtract(const Matrix A) {
  //check that A and B have identical dimensions
  assert(width == A.width);
  assert(height == A.height);
  Matrix Result = A;
  for(int i = 0; i < A.width * A.height; i++) {
    Result.data[i] = data[i] - A.data[i];
  }
  return Result;
}



Matrix& Matrix::operator-( const Matrix& other ) {
  Matrix temp = *this;
  for(int i = 0; i < width*height; i++) {
    this->data[i] = temp.data[i] + other.data[i];
  }
  return *this;
}

Matrix Matrix::multiply(Matrix right) {
  //check that matrices have appropriate dimensions
  if(width != right.height){
    std::cout << "Error found in multiply operation:" << std::endl;
    std::cout << "Left Matrix found with width: "  << width << std::endl;
    std::cout << "Right Matrix found with height: " << height << std::endl;
    std::cout << "Left Matrix:" <<std::endl;
    printMatrix();
    std::cout << "Right Matrix:" << std::endl;
    right.printMatrix();
  }
  
  assert(width==right.height);
  
  // create temporary array to load into result Matrix
  double data_temp[width*right.height];
  double sum = 0;
  int result_count = 0;
  for(int i = 0; i < height; i++) {
    for(int k = 0; k < right.width; k++) {
      sum = 0;
      for (int j = 0; j < right.height; j++) {
        //sum += L[i * Lw + j] * R[j*Rw + k];
        sum += this->data[i * width + j] * right.data[j*right.width + k];
      }
      data_temp[result_count] = sum;
      result_count++;
    }
  }
  Matrix r = Matrix(height, right.width, data_temp);
  return r;
}

Matrix& Matrix::operator*( const Matrix& other ) {
  double sum = 0;
  int result_count = 0;
  
  for(int i = 0; i < height; i++) {
    for(int k = 0; k < other.width; k++) {
      sum = 0;
      for(int j = 0; j < other.height; j++) {
	sum += this->data[i*width + j] * other.data[j*other.width + k];
      }
      this->data[result_count] = sum;
      result_count++;
    }
  }
  return *this;
}

Matrix Matrix::divide(Matrix right) {
  // element division
  //check that matrices have appropriate dimensions
  assert(height == right.height);
  assert(width == right.width);
  // create temporary array to load into resultant Matrix
  double data_temp[width*right.height];
  for(int i = 0; i < height * right.width; i++) {
    if(right.data[i] == 0){
      data_temp[i] = 0;
    }
    else data_temp[i] = data[i]/right.data[i];
  }
  Matrix r = Matrix(right.height, width, data_temp);
  return r;
}


Matrix Matrix::transpose() {
  double transpose[width*height];
  if(width == height){
    for(int i = 0; i < width; i++) {
      for(int j = 0; j < height; j++) {
	transpose[(j*width) + i] = data[(i*width) + j]; //write rows as columns and columns as rows
      }
    }

    Matrix r = Matrix(width, height, transpose); // i.e, 2x1 -> 1x2
    return r;
  }/*
  else {
    //follow cycles while constructing transposition
    
    double cycle[width];
    for(int i = 0; i < width*height; i++) {
      //
      */ 
}



Matrix Matrix::inverse() {
  int pivot_row;
  double temp;
  int pivots[width];
  Matrix I = *this;
  
  for (int d = 0; d < width; d++) {
    //find pivot row, or row with the biggest value in the current column
    temp = 0;
    for(int i = d; i < width; i++) {
      if(abs(I.data[i*width+d]) >= temp)
	{
	  temp = abs(I.data[i*width+d]);
	  pivot_row = i;
	}
    }
    // Singular matrices are non-invertible
    if (I.data[(pivot_row*width)+d] == 0.0) {
      std::cerr << "Singular matrix detected!!!" << std::endl;
      return I;
    }
    // pivot
    if (pivot_row != d) {
      for (int j = 0; j < width; j++) {
	temp = I.data[(d*width)+j];
	I.data[(d*width)+j] = I.data[(pivot_row*width)+j];
	I.data[(pivot_row*width)+j] = temp;
      }
    }
    
    pivots[d] = pivot_row;
    temp = 1.0/I.data[(d*width)+d];
    I.data[(d*width)+d] = 1.0;
    //row reduction
    for(int j = 0; j < width; j++) {
      I.data[(d*width)+j] = I.data[(d*width)+j]*temp;
    }
    //elimination
    for (int i = 0; i < width; i++) {
      if(i != d) {
	temp = I.data[(i*width)+d];
	I.data[(i*width)+d] = 0.0;
	for (int j = 0; j < width; j++) {
	  I.data[(i*width)+j] = I.data[(i*width)+j] - I.data[(d*width)+j] * temp;
	}
      }
    }
  }
  
  //undo pivot row swaps
  for (int d = width-1; d >= 0; d--) {
    if(pivots[d] != d)
      {
	for (int i = 0; i < width; i++)
	  {
	    temp = I.data[(i*width) + d];
	    I.data[(i*width)+d] = I.data[(i*width)+pivots[d]];
	    I.data[(i*width)+pivots[d]] = temp; 
	  }	
      } 
  } 
  return I;  
}

Matrix Matrix::concatenate(const Matrix right, int axis) {
  // concatenate matrices together
  // matrices must have same shape, except in the dimension corresponding
  // to the axis (first axis by default)
  //if(axis == 0) assert(width == right.width);
  //if(axis == 1) assert(height == right.height);

  // Create data structure to hold all the new data, must be
  // of size left.size + right.size
  
  int new_size = (height*width) + (right.width * right.height);
  std::cout << height << width << right.width << right.height << std::endl;
  double data_temp[new_size];

  std::cout << "newsize: " << new_size << std::endl;
  
  int new_height = height;
  int new_width = width;

  int temp = 0;

  if(axis == 0){
    /* This concatenation is far faster than appending to other axis in the
       one-array matrix implementation  */
    assert(width == right.width);
    std::copy(this->data, this->data+(width*height), data_temp);
    std::copy(right.data, right.data+(right.width*right.height), data_temp+(width*height));
    new_height = height + right.height;
  }
  if(axis == 1) {
    for(int i = 0; i < height; i++) {
      std::cout << "adding from left matrix: "<< data[i] << std::endl;
      data_temp[i] = data[i];
      for(int k = 0; k < width; k++) {
	data_temp[k] = data[k];
	//move i to end of row:
	if(i%width == 1 || (width == 1)) {
	  // move j to end of right's row
	  for(int j = 0; j < right.width; j++) {
	    std::cout << "adding from right matrix: "<< right.data[temp] << std::endl;
	    data_temp[j+i+1] = right.data[j];
	  }
	}
      }
    }
    new_width = new_width + right.width;
  }
    
  Matrix r = Matrix(new_height, new_width, data_temp);
  return r;
 
}


int Matrix::getWidth() { return width; }
void Matrix::setWidth(int nl) { width = nl; }
int Matrix::getHeight() { return height; }
void Matrix::setHeight(int nh) { height = nh; }
