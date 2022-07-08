#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "stdint.h"
#include "vector"

using namespace std;

class Shape : public vector<uint8_t> {
public:
  Shape(uint8_t row = 0, uint8_t column = 0);
  bool operator==(const Shape shape) const;
  bool isSquare() const;
  Shape transpose() const;
};

class Matrix {
private:
  bool isEmpty;
  Shape shape;
  vector<vector<float>> data;

public:
  // Constructors
  Matrix();
  Matrix(uint8_t row, float initValue = 0.0f);
  Matrix(Shape shape, float initValue = 0.0f);
  Matrix(const Matrix &mat);
  // Operators
  Matrix operator+(const Matrix &mat) const;
  Matrix operator-(const Matrix &mat) const;
  Matrix operator*(const Matrix &mat) const;
  Matrix operator*(const float scalar) const;
  Matrix operator/(const Matrix &mat) const;
  Matrix operator/(const float scalar) const;
  bool operator==(const Matrix &mat) const;
  vector<float> &operator[](uint8_t index);
  Matrix &operator=(vector<vector<float>> vector2d);
  // Shape
  Shape getShape() const;
  void reshape(const Shape &shape);
  // Calculating
  Matrix reverse() const;
  Matrix transpose() const;
  float det() const;
  float trace() const;
  // Static functions
  static Matrix zeros(uint8_t row);
  static Matrix zeros(uint8_t row, uint8_t column);
  static Matrix ones(uint8_t row);
  static Matrix ones(uint8_t row, uint8_t column);
  static Matrix eye(uint8_t row);
  static Matrix eye(uint8_t row, uint8_t column);
  static bool feq(const float num1, const float num2,
                  const float precision = 0.000001f);
  static void print(const Matrix &mat);
};

#endif  // MATRIX_HPP
