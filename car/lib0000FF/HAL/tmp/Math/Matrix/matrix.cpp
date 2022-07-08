#include "matrix.hpp"

#include "cmath"
#include "stdio.h"

Matrix::Matrix() {
  isEmpty = true;
  this->shape = Shape(0, 0);
}

Matrix::Matrix(uint8_t row, float initValue) {
  vector<vector<float>> tmp(row, vector<float>(row, initValue));
  this->data = tmp;
  this->shape = Shape(row, row);
  isEmpty = false;
}

Matrix::Matrix(Shape shape, float initValue) {
  vector<vector<float>> tmp(shape[0], vector<float>(shape[1], initValue));
  this->data = tmp;
  this->shape = shape;
  isEmpty = false;
}

Matrix::Matrix(const Matrix &mat) {
  this->data = mat.data;
  this->shape = mat.shape;
  this->isEmpty = mat.isEmpty;
}

Matrix Matrix::operator+(const Matrix &mat) const {
  if (this->shape != mat.shape) {
    printf(
      "[%s] Line %d: Cannot add two matrix that have incompatible "
      "shapes\n.",
      __FILE__, __LINE__);
    return Matrix();
  }
  Shape shape = this->shape;
  Matrix result(shape);
  for (uint8_t i = 0; i < shape[0]; i++) {
    for (uint8_t j = 0; j < shape[1]; j++) {
      result.data[i][j] = this->data[i][j] + mat.data[i][j];
    }
  }
  return result;
}

Matrix Matrix::operator-(const Matrix &mat) const {
  if (this->shape != mat.shape) {
    printf(
      "[%s] Line %d: Cannot reduce two matrix that have incompatible "
      "shapes\n.",
      __FILE__, __LINE__);
    return Matrix();
  }

  Shape shape = this->shape;
  Matrix result(shape);
  for (uint8_t i = 0; i < shape[0]; i++) {
    for (uint8_t j = 0; j < shape[1]; j++) {
      result.data[i][j] = this->data[i][j] - mat.data[i][j];
    }
  }
  return result;
}

Matrix Matrix::operator*(const Matrix &mat) const {
  if (this->shape[1] != mat.shape[0]) {
    printf(
      "[%s] Line %d: Cannot multiply two matrix that have incompatible "
      "shape\n.",
      __FILE__, __LINE__);
    return Matrix();
  }

  Matrix result(Shape(this->shape[0], mat.shape[1]));
  for (uint8_t i = 0; i < this->shape[0]; i++) {
    for (uint8_t j = 0; j < mat.shape[1]; j++) {
      for (uint8_t k = 0; k < this->shape[1]; k++) {
        result.data[i][j] += this->data[i][k] * mat.data[k][j];
      }
    }
  }
  return result;
}

Matrix Matrix::operator*(const float scalar) const {
  Matrix result(shape);
  for (uint8_t i = 0; i < shape[0]; i++) {
    for (uint8_t j = 0; j < shape[1]; j++) {
      result.data[i][j] = this->data[i][j] * scalar;
    }
  }
  return result;
}

Matrix Matrix::operator/(const Matrix &mat) const {
  if (!this->shape.isSquare() || !mat.shape.isSquare() || feq(mat.det(), 0.0f))
    return Matrix();
  return (*this) * mat.reverse();
}

Matrix Matrix::operator/(const float scalar) const {
  if (feq(scalar, 0.0f)) return Matrix();
  return (*this * (1 / scalar));
}

bool Matrix::operator==(const Matrix &mat) const {
  if (shape != mat.shape) return false;
  for (uint8_t i = 0; i < shape[0]; i++) {
    for (uint8_t j = 0; j < shape[1]; j++) {
      if (!feq(this->data[i][j], mat.data[i][j])) return false;
    }
  }
  return true;
}

vector<float> &Matrix::operator[](uint8_t index) { return this->data[index]; }

Matrix &Matrix::operator=(const vector<vector<float>> vector2d) {
  Shape tmp(vector2d.size(), vector2d[0].size());
  this->shape = tmp;
  this->data = vector2d;
  return (*this);
}

Shape Matrix::getShape() const {
  Shape result(2, 0);
  if (isEmpty)
    return result;
  else {
    result[0] = this->data.size();
    result[1] = this->data[0].size();
    return result;
  }
}

void Matrix::reshape(const Shape &shape) {
  this->data.resize(shape[0]);
  for (uint8_t i = 0; i < shape[1]; i++) {
    this->data[i].resize(shape[1]);
  }
  this->shape = shape;
}

Matrix Matrix::reverse() const {
  if (!shape.isSquare()) {
    printf(
      "[%s] Line %d: A matrix which is not square does not have "
      "reverse\n.",
      __FILE__, __LINE__);
    return Matrix();
  }
  Matrix result(this->shape);
  if (shape[0] == 1){
    result[0][0] = 1/this->data[0][0];
  }
  else if (shape[0] == 2) {
    result[0][0] = this->data[1][1];
    result[1][1] = this->data[0][0];
    result[1][0] = -this->data[1][0];
    result[0][1] = -this->data[0][1];
    result = result / this->det();
  }
  else {
    // Augmented matrix
    Matrix tmp(Shape(this->shape[0],2*this->shape[0]));
    for(uint8_t i = 0;i < shape[0];i++){
      for(uint8_t j = 0;j < 2*shape[0];j++){
        if(j < shape[0])tmp[i][j] = this->data[i][j];
        else if(j == i + shape[1])tmp[i][j] = 1.0f;
        else tmp[i][j] = 0.0f;
      }
    }

    for (uint8_t j = 0; j < shape[1]; j++) {
      uint8_t index = j;
      while (index != tmp.shape[0] && feq(tmp[index][j], 0)) {
        index++;
      }
      if (index != j) {
        vector<float> vtmp = tmp[j];
        tmp[j] = tmp[index];
        tmp[index] = vtmp;
      }
      for (uint8_t i = j + 1; i < shape[0]; i++) {
        if (feq(tmp[i][j], 0)) continue;
        float q = tmp[i][j] / tmp[j][j];
        for (uint8_t k = 0; k < 2*shape[1]; k++) tmp[i][k] -= tmp[j][k] * q;
      }
    }

    for(uint8_t j = shape[1]-1;j != 255;j--){
      for(uint8_t i = 0;i < j;i++){
        if(feq(tmp[i][j],0))continue;
        float q = tmp[i][j] / tmp[j][j];
        for(uint8_t k = shape[1];k < 2*shape[1];k++)tmp[i][k] -= tmp[j][k] * q;
      }
    }
    
    for(uint8_t i = 0;i < shape[0];i++){
      result[i] = vector<float>(tmp[i].begin()+shape[0],tmp[i].end());
      for(uint8_t j = 0;j <shape[1];j++)result[i][j] /= tmp[i][i];
    }
  }
  return result;
}

Matrix Matrix::transpose() const {
  Matrix result(this->shape.transpose());
  for (uint8_t i = 0; i < shape[1]; i++) {
    for (uint8_t j = 0; j < shape[0]; j++) {
      result.data[i][j] = this->data[j][i];
    }
  }
  return result;
}

float Matrix::det() const {
  if (!shape.isSquare()) {
    printf(
      "[%s] Line %d: A matrix which is not square does not have "
      "determinant\n.",
      __FILE__, __LINE__);
    return 0.0f;
  }

  if (shape[0] == 1)
    return this->data[0][0];
  else if (shape[0] == 2)
    return this->data[0][0] * this->data[1][1] -
           this->data[1][0] * this->data[0][1];
  else if (shape[0] == 3)
    return this->data[0][0] * this->data[1][1] * this->data[2][2] +
           this->data[0][1] * this->data[1][2] * this->data[2][0] +
           this->data[1][0] * this->data[2][1] * this->data[0][2] -
           this->data[0][2] * this->data[1][1] * this->data[2][0] -
           this->data[0][1] * this->data[1][0] * this->data[2][2] -
           this->data[0][0] * this->data[1][2] * this->data[2][1];
  else {  // LU Decomposition
    float result = 1.0f;
    Matrix U = (*this);
    for (uint8_t j = 0; j < shape[1]; j++) {
      uint8_t index = j;
      while (index != U.shape[0] && feq(U[index][j], 0)) {
        index++;
      }
      if (index == U.shape[0])return 0.0f;
      else if (index != j) {
        vector<float> tmp = U[j];
        U[j] = U[index];
        U[index] = tmp;
        result *= -1;
      }
      for (uint8_t i = j + 1; i < shape[0]; i++) {
        if (feq(U[i][j], 0))continue;
        float q = U[i][j] / U[j][j];
        for (uint8_t k = 0; k < shape[1]; k++)U[i][k] -= U[j][k] * q;
      }
    }
    //print(U);
    for (uint8_t i = 0; i < shape[0]; i++)result *= U[i][i];
    return result;
  }
}

float Matrix::trace() const {
  float result = 0.0f;
  for (uint8_t i = 0; i < shape[0] && i < shape[1]; i++)
    result += this->data[i][i];
  return result;
}

Matrix Matrix::zeros(uint8_t row) { return Matrix(row, 0.0f); }

Matrix Matrix::zeros(uint8_t row, uint8_t column) {
  return Matrix(Shape(row, column), 0.0f);
}

Matrix Matrix::ones(uint8_t row) { return Matrix(row, 1.0f); }

Matrix Matrix::ones(uint8_t row, uint8_t column) {
  return Matrix(Shape(row, column), 1.0f);
}

Matrix Matrix::eye(uint8_t row) {
  Matrix mat(row, 0.0f);
  for (uint8_t i = 0; i < row; i++) mat.data[i][i] = 1.0f;
  return mat;
}

Matrix Matrix::eye(uint8_t row, uint8_t column) {
  Matrix mat(Shape(row,column), 0.0f);
  for (uint8_t i = 0; i < row && i < column; i++) mat.data[i][i] = 1.0f;
  return mat;
}

bool Matrix::feq(const float num1, const float num2, const float precision) {
  if (fabsf(num1 - num2) < precision)
    return true;
  else
    return false;
}

Shape::Shape(uint8_t row, uint8_t column) {
  this->resize(2);
  (*this)[0] = row;
  (*this)[1] = column;
}

bool Shape::operator==(const Shape shape) const {
  if (shape[0] == (*this)[0] && shape[1] == (*this)[1])
    return true;
  else
    return false;
}

bool Shape::isSquare() const {
  if ((*this)[0] != (*this)[1])
    return false;
  else
    return true;
}

Shape Shape::transpose() const { return Shape((*this)[1], (*this)[0]); }

void Matrix::print(const Matrix &mat) {
  Shape shape = mat.shape;
  for (int i = 0; i < shape[0]; i++) {
    for (int j = 0; j < shape[1]; j++) {
      if (j == 0) printf("[");
      printf(" %f ", mat.data[i][j]);
      if (j == shape[1] - 1)
        printf("]\n");
      else
        printf(",");
    }
  }
  printf("\n");
}
