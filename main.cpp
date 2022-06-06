// Copyright 2021 "Assignment problem" Titova Nina
#include "naznach.h"

#include <fstream>
#include <iostream>
#include <string>
#include <ctime>

int main() {
    
  clock_t start, end;
  start = clock();

  std::string input_method;             // ñïîñîá ââîäà ìàòðèöû
  std::string filename;                 // èìÿ ôàéëà, â êîòîðîì ñèäèò ìàòðèöà
  int size;                             // ðàçìåð ìàòðèöû, çàïèñàííîé îò ðóêè
  int **matrix;                         // ìàòðèöà äëÿ çàïèñè îò ðóêè
  std::ofstream user_write_matrix_file; // ôàéë äëÿ çàïèñàííîé îò ðóêè ìàòðèöû
/*
  std::cout << "Is the matrix in a file, or will you enter it yourself?" << std::endl;
  std::cout << "Write: file or write:" << std::endl;
  std::cin >> input_method;

  if (input_method == "file") {
    std::cout << "Please enter the name of the file containing the matrix." << std::endl;
    std::cin >> filename;

    MyMatrix *M = new MyMatrix(filename);
    if (M->rowcnt > M->colcnt)
      std::cout << "FAIL MATRIX: The number of rows is greater than the number of columns!" << std::endl;
    else
      M->Run();
  } else {
    if (input_method == "write") {
      std::cout << "Note! The matrix must be square." << std::endl;
      std::cout << "Enter only one number: the number of elements in the matrix row:" << std::endl;
      std::cin >> size;
      matrix = new int *[size];
      for (int i = 0; i < size; i++) {
        matrix[i] = new int[size];
      }
      std::cout << "Write matrix:" << std::endl;
      for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
          std::cin >> matrix[i][j];
        }
      }
      user_write_matrix_file.open("user_matrix.txt");
      for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
          if (j == size - 1) user_write_matrix_file << matrix[i][j];
          else user_write_matrix_file << matrix[i][j] << " ";
        }
        if (i != size - 1) user_write_matrix_file << "\n"; 
      }
      user_write_matrix_file.close();

      MyMatrix *M = new MyMatrix("user_matrix.txt");
      M->Run();
    }
  }
*/
  MyMatrix *M = new MyMatrix("matrix.txt");
  
  M->Run();

  // delete M;

  end = clock();
  double seconds = (double)(end - start) / CLOCKS_PER_SEC;
  std::cout << "Time = " << seconds << " sec" << std::endl;

  return 0;
}
