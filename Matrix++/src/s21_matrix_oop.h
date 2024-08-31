#ifndef SRC_S21_MATRIX_OOP_H_
#define SRC_S21_MATRIX_OOP_H_

#include <cmath>
#include <iostream>
#include <stdexcept>  //исключения

#define EPS 1e-6

class S21Matrix {
 public:
  S21Matrix();                    // конструктор
  S21Matrix(int rows, int cols);  // конструктор с парам
  S21Matrix(const S21Matrix& other);  // конструктор копирования
  S21Matrix(S21Matrix&& other) noexcept;  // конструктор перемещения
  ~S21Matrix();                           // деструктор

  // сравнение
  bool EqMatrix(const S21Matrix& other) const;
  // сложение матриц
  void SumMatrix(const S21Matrix& other);
  // вычитание матриц
  void SubMatrix(const S21Matrix& other);
  // умножение матрицы на число
  void MulNumber(const double num);
  // умножение матрицы на матрицу
  void MulMatrix(const S21Matrix& other);
  // транспонирование матрицы
  S21Matrix Transpose() const;
  // вычисление матриц
  S21Matrix CalcComplements() const;
  // определитель матрицы
  double Determinant() const;
  // обратная матрица
  S21Matrix InverseMatrix() const;

  // доступ к приватным полям
  void setRows(int rows);
  int getRows() const;
  void setCols(int cols);
  int getCols() const;

  // перегрузка операторов и индексация
  double& operator()(int i, int j);
  double operator()(int i, int j) const;
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix operator+(const S21Matrix& other) const;
  S21Matrix operator-(const S21Matrix& other) const;
  S21Matrix operator*(const S21Matrix& other) const;
  S21Matrix operator*(const double num) const;
  bool operator==(const S21Matrix& other) const;
  S21Matrix operator+=(const S21Matrix& other);
  S21Matrix operator-=(const S21Matrix& other);
  S21Matrix operator*=(const S21Matrix& other);
  S21Matrix operator*=(const double num);

 private:
  int rows_, cols_;
  double** matrix_;

  // helpers
  void allocMemory();                       // выделение памяти
  void copyMatrix(const S21Matrix& other);  // копирование матрицы
  void clear_matrix();                      // очистка
  S21Matrix Minor(int col, int row) const;  // получение минора
};

#endif