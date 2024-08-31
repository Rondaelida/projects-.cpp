#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

TEST(Matrix, True) {
  S21Matrix matrix_a(3, 3);
  S21Matrix matrix_b(3, 3);
  matrix_a(1, 1) = 222;
  matrix_b(1, 1) = 222;
  matrix_a(0, 0) = -222;
  matrix_b(0, 0) = -222;
  EXPECT_TRUE(matrix_a == matrix_b);
}

TEST(Matrix2, True) {
  S21Matrix matrix_a(3, 3);
  matrix_a(1, 1) = 222;
  matrix_a(0, 0) = -222;
  S21Matrix matrix_b = S21Matrix(std::move(matrix_a));
  EXPECT_EQ(matrix_a.getRows(), 0);
  EXPECT_EQ(matrix_a.getCols(), 0);
  EXPECT_EQ(matrix_b.getRows(), 3);
  EXPECT_EQ(matrix_b.getCols(), 3);
  EXPECT_EQ(matrix_b(1, 1), 222);
  EXPECT_EQ(matrix_b(0, 0), -222);
}

TEST(Determinant, True) {
  S21Matrix matrix_a(3, 3);
  matrix_a(0, 0) = 2.0;
  matrix_a(0, 1) = 5.0;
  matrix_a(0, 2) = 7.0;
  matrix_a(1, 0) = 6.0;
  matrix_a(1, 1) = 3.0;
  matrix_a(1, 2) = 4.0;
  matrix_a(2, 0) = 5.0;
  matrix_a(2, 1) = -2.0;
  matrix_a(2, 2) = -3.0;
  EXPECT_EQ(matrix_a.Determinant(), -1.0);
}

TEST(Determinant1, True) {
  S21Matrix matrix_a(1, 1);
  matrix_a(0, 0) = 2;
  EXPECT_EQ(matrix_a.Determinant(), 2);
}

TEST(Calc_complements, True) {
  S21Matrix matrix_a(3, 3);
  matrix_a(0, 0) = 1;
  matrix_a(0, 1) = 2;
  matrix_a(0, 2) = 3;
  matrix_a(1, 0) = 0;
  matrix_a(1, 1) = 4;
  matrix_a(1, 2) = 2;
  matrix_a(2, 0) = 5;
  matrix_a(2, 1) = 2;
  matrix_a(2, 2) = 1;
  S21Matrix matrix_b = matrix_a.CalcComplements();
  S21Matrix matrix_c(3, 3);
  matrix_c(0, 0) = 0;
  matrix_c(0, 1) = 10;
  matrix_c(0, 2) = -20;
  matrix_c(1, 0) = 4;
  matrix_c(1, 1) = -14;
  matrix_c(1, 2) = 8;
  matrix_c(2, 0) = -8;
  matrix_c(2, 1) = -2;
  matrix_c(2, 2) = 4;
  EXPECT_TRUE(matrix_b == matrix_c);
}

TEST(InverseMatrix1, True) {
  S21Matrix matrix_a(3, 3);
  matrix_a(0, 0) = 2;
  matrix_a(0, 1) = 5;
  matrix_a(0, 2) = 7;
  matrix_a(1, 0) = 6;
  matrix_a(1, 1) = 3;
  matrix_a(1, 2) = 4;
  matrix_a(2, 0) = 5;
  matrix_a(2, 1) = -2;
  matrix_a(2, 2) = -3;
  S21Matrix matrix_b = matrix_a.InverseMatrix();
  S21Matrix matrix_c(3, 3);
  matrix_c(0, 0) = 1;
  matrix_c(0, 1) = -1;
  matrix_c(0, 2) = 1;
  matrix_c(1, 0) = -38;
  matrix_c(1, 1) = 41;
  matrix_c(1, 2) = -34;
  matrix_c(2, 0) = 27;
  matrix_c(2, 1) = -29;
  matrix_c(2, 2) = 24;
  EXPECT_TRUE(matrix_b == matrix_c);
}

TEST(InverseMatrix2, True) {
  S21Matrix tmp(1, 1);
  tmp(0, 0) = 2;
  S21Matrix tmp2 = tmp.InverseMatrix();
  EXPECT_EQ(tmp2(0, 0), 0.5);
}

TEST(EqMatrix, True) {
  S21Matrix matrix_a(3, 3);
  S21Matrix matrix_b(3, 3);
  EXPECT_TRUE(matrix_a == matrix_b);
}

TEST(EqMatrix, False) {
  S21Matrix matrix_a(3, 3);
  S21Matrix matrix_b(2, 2);
  EXPECT_FALSE(matrix_a == matrix_b);
  S21Matrix matrix_a2(3, 3);
  S21Matrix matrix_b2(2, 3);
  EXPECT_FALSE(matrix_a2 == matrix_b2);
  S21Matrix matrix_a3(3, 3);
  S21Matrix matrix_b3(3, 2);
  EXPECT_FALSE(matrix_a3 == matrix_b3);
}

TEST(EqMatrix2, False) {
  S21Matrix matrix_a(3, 3);
  S21Matrix matrix_b(3, 3);
  matrix_b(0, 0) = 0.01;
  EXPECT_FALSE(matrix_a == matrix_b);
}

TEST(SumMatrix, True) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix result(2, 2);
  matrix_a(0, 0) = 3.14;
  matrix_a(0, 1) = 0.56;
  matrix_a(1, 0) = -69.3;
  matrix_a(1, 1) = 0;
  matrix_b(0, 0) = -78.14;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -0.3;
  matrix_b(1, 1) = 2;
  result(0, 0) = -75;
  result(0, 1) = 0.56;
  result(1, 0) = -69.6;
  result(1, 1) = 2;
  matrix_a.SumMatrix(matrix_b);
  EXPECT_TRUE(matrix_a == result);
}

TEST(SubMatrix, True) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix result(2, 2);
  matrix_a(0, 0) = 3;
  matrix_a(0, 1) = 2;
  matrix_a(1, 0) = -6;
  matrix_a(1, 1) = 0;
  matrix_b(0, 0) = -7;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -3;
  matrix_b(1, 1) = 2;
  result(0, 0) = 10;
  result(0, 1) = 2;
  result(1, 0) = -3;
  result(1, 1) = -2;
  matrix_a.SubMatrix(matrix_b);
  EXPECT_TRUE(matrix_a == result);
}

TEST(MulNumber, True) {
  S21Matrix matrix_a(2, 2);
  S21Matrix result(2, 2);
  matrix_a(0, 0) = -78.14;
  matrix_a(0, 1) = 0;
  matrix_a(1, 0) = -0.3;
  matrix_a(1, 1) = 2;
  result(0, 0) = -781.4;
  result(0, 1) = 0;
  result(1, 0) = -3;
  result(1, 1) = 20;
  matrix_a.MulNumber(10);
  EXPECT_TRUE(matrix_a == result);
}

TEST(MulMatrix, True) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix result(2, 2);
  matrix_a(0, 0) = 3;
  matrix_a(0, 1) = 2;
  matrix_a(1, 0) = -6.6;
  matrix_a(1, 1) = 0;
  matrix_b(0, 0) = -7;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -3.5;
  matrix_b(1, 1) = 2;
  result(0, 0) = -28;
  result(0, 1) = 4;
  result(1, 0) = 46.2;
  result(1, 1) = 0;
  matrix_a.MulMatrix(matrix_b);
  EXPECT_TRUE(matrix_a == result);
}

TEST(OperatorGetElement1, True) {
  S21Matrix matrix_a(2, 2);
  matrix_a(0, 0) = 3;
  matrix_a(0, 1) = 2;
  matrix_a(1, 0) = -6.6;
  matrix_a(1, 1) = 0;
  EXPECT_EQ(matrix_a(0, 1), 2);
}

TEST(OperatorGetElement2, False) {
  S21Matrix matrix_a(2, 2);
  matrix_a(0, 0) = 3;
  matrix_a(0, 1) = 2;
  matrix_a(1, 0) = -6.6;
  matrix_a(1, 1) = 0;
  EXPECT_NE(matrix_a(0, 1), 10);
}

TEST(OperatorPlus, True) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix result(2, 2);
  matrix_a(0, 0) = 3.14;
  matrix_a(0, 1) = 0.56;
  matrix_a(1, 0) = -69.3;
  matrix_a(1, 1) = 0;
  matrix_b(0, 0) = -78.14;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -0.3;
  matrix_b(1, 1) = 2;
  result(0, 0) = -75;
  result(0, 1) = 0.56;
  result(1, 0) = -69.6;
  result(1, 1) = 2;
  EXPECT_TRUE((matrix_a + matrix_b) == result);
}

TEST(OperatorMinus, True) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix result(2, 2);
  matrix_a(0, 0) = 3;
  matrix_a(0, 1) = 2;
  matrix_a(1, 0) = -6;
  matrix_a(1, 1) = 0;
  matrix_b(0, 0) = -7;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -3;
  matrix_b(1, 1) = 2;
  result(0, 0) = 10;
  result(0, 1) = 2;
  result(1, 0) = -3;
  result(1, 1) = -2;
  EXPECT_TRUE((matrix_a - matrix_b) == result);
}

TEST(OperatorMulMatrix1, True) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix result(2, 2);
  matrix_a(0, 0) = 3;
  matrix_a(0, 1) = 2;
  matrix_a(1, 0) = -6.6;
  matrix_a(1, 1) = 0;
  matrix_b(0, 0) = -7;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -3.5;
  matrix_b(1, 1) = 2;
  result(0, 0) = -28;
  result(0, 1) = 4;
  result(1, 0) = 46.2;
  result(1, 1) = 0;
  EXPECT_TRUE((matrix_a * matrix_b) == result);
}

TEST(OperatorMulNumber1, True) {
  S21Matrix matrix_a(2, 2);
  S21Matrix result(2, 2);
  matrix_a(0, 0) = -78.14;
  matrix_a(0, 1) = 0;
  matrix_a(1, 0) = -0.3;
  matrix_a(1, 1) = 2;
  result(0, 0) = -781.4;
  result(0, 1) = 0;
  result(1, 0) = -3;
  result(1, 1) = 20;
  EXPECT_TRUE((matrix_a * 10) == result);
}

TEST(OperatorEqMatrix, True) {
  S21Matrix matrix_b(1, 3);
  S21Matrix matrix_a = matrix_b;
  EXPECT_TRUE(matrix_a == matrix_b);
}

TEST(OperatorSumMatrix, True) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix result(2, 2);
  matrix_a(0, 0) = 3.14;
  matrix_a(0, 1) = 0.56;
  matrix_a(1, 0) = -69.3;
  matrix_a(1, 1) = 0;
  matrix_b(0, 0) = -78.14;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -0.3;
  matrix_b(1, 1) = 2;
  result(0, 0) = -75;
  result(0, 1) = 0.56;
  result(1, 0) = -69.6;
  result(1, 1) = 2;
  EXPECT_TRUE((matrix_a += matrix_b) == result);
}

TEST(OperatorSubMatrix, True) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix result(2, 2);
  matrix_a(0, 0) = 3;
  matrix_a(0, 1) = 2;
  matrix_a(1, 0) = -6;
  matrix_a(1, 1) = 0;
  matrix_b(0, 0) = -7;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -3;
  matrix_b(1, 1) = 2;
  result(0, 0) = 10;
  result(0, 1) = 2;
  result(1, 0) = -3;
  result(1, 1) = -2;
  EXPECT_TRUE((matrix_a -= matrix_b) == result);
}

TEST(OperatorMulNumber2, True) {
  S21Matrix matrix_a(2, 2);
  S21Matrix result(2, 2);
  matrix_a(0, 0) = -78.14;
  matrix_a(0, 1) = 0;
  matrix_a(1, 0) = -0.3;
  matrix_a(1, 1) = 2;
  result(0, 0) = -781.4;
  result(0, 1) = 0;
  result(1, 0) = -3;
  result(1, 1) = 20;
  EXPECT_TRUE((matrix_a *= 10) == result);
}

TEST(OperatorMulMatrix2, True) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix result(2, 2);
  matrix_a(0, 0) = 3;
  matrix_a(0, 1) = 2;
  matrix_a(1, 0) = -6.6;
  matrix_a(1, 1) = 0;
  matrix_b(0, 0) = -7;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -3.5;
  matrix_b(1, 1) = 2;
  result(0, 0) = -28;
  result(0, 1) = 4;
  result(1, 0) = 46.2;
  result(1, 1) = 0;
  EXPECT_TRUE((matrix_a *= matrix_b) == result);
}

TEST(Transpose, True) {
  S21Matrix matrix_a(4, 3);
  S21Matrix result(3, 4);
  matrix_a(0, 0) = 7;
  matrix_a(0, 1) = -98;
  matrix_a(0, 2) = 0.5;
  matrix_a(1, 0) = 0;
  matrix_a(1, 1) = 5.4;
  matrix_a(1, 2) = 32;
  matrix_a(2, 0) = 3.12;
  matrix_a(2, 1) = 2323;
  matrix_a(2, 2) = 23;
  matrix_a(3, 0) = -78;
  matrix_a(3, 1) = 476.4;
  matrix_a(3, 2) = 21;
  result(0, 0) = 7;
  result(0, 1) = 0;
  result(0, 2) = 3.12;
  result(0, 3) = -78;
  result(1, 0) = -98;
  result(1, 1) = 5.4;
  result(1, 2) = 2323;
  result(1, 3) = 476.4;
  result(2, 0) = 0.5;
  result(2, 1) = 32;
  result(2, 2) = 23;
  result(2, 3) = 21;
  S21Matrix res = matrix_a.Transpose();
  EXPECT_TRUE(res == result);
}

TEST(GetColsRows, True) {
  S21Matrix matrix_a(3, 3);
  matrix_a(0, 0) = 2;
  matrix_a(0, 1) = 5;
  matrix_a(0, 2) = 7;
  matrix_a(1, 0) = 6;
  matrix_a(1, 1) = 3;
  matrix_a(1, 2) = 4;
  matrix_a(2, 0) = 5;
  matrix_a(2, 1) = -2;
  matrix_a(2, 2) = -3;
  EXPECT_EQ(matrix_a.getRows(), 3);
  EXPECT_EQ(matrix_a.getCols(), 3);
  EXPECT_THROW(matrix_a.setCols(-1), std::length_error);
  EXPECT_THROW(matrix_a.setRows(-1), std::length_error);
}

TEST(SetColsRows, True) {
  S21Matrix matrix_a(3, 3);
  S21Matrix result(3, 2);
  matrix_a(0, 0) = 2;
  matrix_a(0, 1) = 5;
  matrix_a(0, 2) = 7;
  matrix_a(1, 0) = 6;
  matrix_a(1, 1) = 3;
  matrix_a(1, 2) = 4;
  matrix_a(2, 0) = 5;
  matrix_a(2, 1) = -2;
  matrix_a(2, 2) = -3;
  result(0, 0) = 2;
  result(0, 1) = 5;
  result(1, 0) = 6;
  result(1, 1) = 3;
  result(2, 0) = 5;
  result(2, 1) = -2;
  matrix_a.setCols(2);
  EXPECT_TRUE(matrix_a == result);
  S21Matrix matrix_b(3, 3);
  S21Matrix result_b(2, 3);
  matrix_b(0, 0) = 2;
  matrix_b(0, 1) = 5;
  matrix_b(0, 2) = 7;
  matrix_b(1, 0) = 6;
  matrix_b(1, 1) = 3;
  matrix_b(1, 2) = 4;
  matrix_b(2, 0) = 5;
  matrix_b(2, 1) = -2;
  matrix_b(2, 2) = -3;
  result_b(0, 0) = 2;
  result_b(0, 1) = 5;
  result_b(0, 2) = 7;
  result_b(1, 0) = 6;
  result_b(1, 1) = 3;
  result_b(1, 2) = 4;
  matrix_b.setRows(2);
  EXPECT_TRUE(matrix_b == result_b);
}

TEST(OperatorAssignment, Throw) {
  S21Matrix tmp(2, 2);
  EXPECT_THROW(tmp = tmp, std::invalid_argument);
}

TEST(CreateInvalidSize, Throw) {
  EXPECT_THROW(S21Matrix tmp(1, -1), std::invalid_argument);
  EXPECT_THROW(S21Matrix tmp(-1, 1), std::invalid_argument);
}

TEST(OperatorSum, Throw) {
  S21Matrix tmp(2, 3);
  S21Matrix tmp1(4, 5);
  EXPECT_THROW(tmp + tmp1, std::length_error);
  S21Matrix tmp2(2, 3);
  S21Matrix tmp3(2, 4);
  EXPECT_THROW(tmp2 + tmp3, std::length_error);
  S21Matrix tmp4(2, 3);
  S21Matrix tmp5(3, 3);
  EXPECT_THROW(tmp4 + tmp5, std::length_error);
}

TEST(OperatorSub, Throw) {
  S21Matrix tmp(2, 3);
  S21Matrix tmp1(4, 5);
  EXPECT_THROW(tmp - tmp1, std::length_error);
  S21Matrix tmp2(2, 3);
  S21Matrix tmp3(2, 4);
  EXPECT_THROW(tmp2 - tmp3, std::length_error);
  S21Matrix tmp4(2, 3);
  S21Matrix tmp5(3, 3);
  EXPECT_THROW(tmp4 - tmp5, std::length_error);
}

TEST(OperatorMul, Throw) {
  S21Matrix tmp(2, 3);
  S21Matrix tmp1(4, 5);
  EXPECT_THROW(tmp - tmp1, std::length_error);
}

TEST(OperatorIndex, Throw) {
  S21Matrix tmp(2, 3);
  EXPECT_THROW(tmp(4, 5), std::out_of_range);
  EXPECT_THROW(tmp(1, 5), std::out_of_range);
  EXPECT_THROW(tmp(4, 1), std::out_of_range);
  EXPECT_THROW(tmp(1, -5), std::out_of_range);
  EXPECT_THROW(tmp(-4, 1), std::out_of_range);
}

TEST(MulMatrix, Throw) {
  S21Matrix tmp(2, 3);
  S21Matrix tmp1(4, 5);
  EXPECT_THROW(tmp.MulMatrix(tmp1), std::length_error);
}

TEST(CalcComplements, Throw) {
  S21Matrix tmp(2, 3);
  EXPECT_THROW(tmp.CalcComplements(), std::length_error);
}

TEST(Determinant, Throw) {
  S21Matrix tmp(2, 3);
  EXPECT_THROW(tmp.Determinant(), std::length_error);
  EXPECT_THROW(tmp.InverseMatrix(), std::length_error);
}

TEST(InverseMatrix, Throw) {
  S21Matrix tmp(2, 2);
  tmp(0, 0) = 1;
  tmp(0, 1) = 1;
  tmp(1, 0) = 2;
  tmp(1, 1) = 2;
  EXPECT_THROW(tmp.InverseMatrix(), std::length_error);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}