// Copyright 2021 "Assignment problem" Titova Nina
#ifndef INCLUDE_NAZNACH_H_
#define INCLUDE_NAZNACH_H_
#include <fstream>
#include <iostream>
#include <string>

class MyMatrix {
 public:
  int rowcnt;  // кол-во рабочих
  int colcnt;  // кол-во работ

  int** matrix_1;  // Основная матрица
  int** matrix_2;  // Рабочая матрица

  int* StrokiBezM1;
  int KolvoStrokBezM1;

  int* StolbSM3;
  int KolvoStolbSM3;

  int* StrokiSM1;
  int KolvoStrokSM1;

  int* StrokiNeOtm;
  int KolvoStrokNeOtm;

  MyMatrix(std::string filename);

  ~MyMatrix();

  void PrintMatrix(int** matrix);
  void PrintOptimum();

  int isInArray(int* arr, int arrSZ, int element);

  int MinInCol(int** matrix, int col);
  int MinInRow(int** matrix, int row);

  void Step1(int** matrix);
  void Step2(int** matrix);
  void Step21();

  int Opimum();

  void Run();
};

#endif  // INCLUDE_NAZNACH_H_
