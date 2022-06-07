// Copyright 2022 "Assignment problem" Titova Nina
#include <fstream>
#include <iostream>
#include <string>
#include <ctime>
#include <climits>

class MyMatrix {
 public:
  int rowcnt;
  int colcnt;

  int** matrix_1;
  int** matrix_2;

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

MyMatrix::MyMatrix(std::string filename) {
  int* mass = new int[256];
  std::string buf;

  StrokiBezM1 = new int[rowcnt];
  StolbSM3 = new int[colcnt];
  StrokiSM1 = new int[rowcnt];
  StrokiNeOtm = new int[rowcnt];

  matrix_1 = new int*[100];
  for (int i = 0; i < 100; i++) {
    matrix_1[i] = new int[100];
  }  // èçíà÷àëüíàÿ ìàòðèöà

  int cnt_space = 0;
  int cnt_symb = 0;
  int cnt_line = 0;

  std::ifstream fmat(filename);

  if (!fmat.is_open()) {
    std::cout << "FAIL FILE" << std::endl;
  } else {
    while (!fmat.eof()) {
      fmat >> mass[cnt_symb];
      cnt_symb++;
    }

    fmat.seekg(0, std::ios::beg);

    while (!fmat.eof()) {
      getline(fmat, buf);
      cnt_line++;
    }

    fmat.seekg(0, std::ios::beg);

    rowcnt = cnt_line;
    colcnt = cnt_symb / rowcnt;

    int l = 0;

    for (int i = 0; i < rowcnt; i++) {
      for (int j = 0; j < colcnt; j++) {
        matrix_1[i][j] = mass[l];
        l++;
      }
    }

    std::cout << "ORIGINAL MATRIX:" << std::endl;
    PrintMatrix(matrix_1);
  }
  std::cout << std::endl;

  fmat.close();
  delete[] mass;
}

MyMatrix::~MyMatrix() {
  delete[] StrokiBezM1;
  delete[] StrokiNeOtm;
  delete[] StrokiSM1;
  delete[] StolbSM3;

  for (int i = 0; i < 100; i++) delete[] matrix_1[i];
  delete[] matrix_1;

  for (int i = 0; i < rowcnt; i++) delete[] matrix_2[i];
  delete[] matrix_2;
}

void MyMatrix::PrintMatrix(int** matrix) {
  for (int i = 0; i < rowcnt; i++) {
    for (int j = 0; j < colcnt; j++) {
      std::cout << matrix[i][j] << "\t";
    }
    std::cout << std::endl;
  }
}

void MyMatrix::PrintOptimum() {
  for (int i = 0; i < rowcnt; i++) {
    for (int j = 0; j < colcnt; j++) {
      if (matrix_2[i][j] == -1) {
        std::cout << "Worker [" << i + 1 << "] -> job [" << j + 1 << "] ("
                  << matrix_1[i][j] << ")" << std::endl;
      }
    }
  }
}

int MyMatrix::isInArray(int* arr, int arrSZ, int element) {
  for (int i = 0; i < arrSZ; i++) {
    if (element == arr[i]) return 1;
  }
  return 0;
}

int MyMatrix::MinInCol(int** matrix, int col) {
  int min = INT_MAX;

  for (int i = 0; i < rowcnt; i++) {
    if (matrix[i][col] < min) {
      min = matrix[i][col];
    }
  }
  return min;
}

int MyMatrix::MinInRow(int** matrix, int row) {
  int min = INT_MAX;

  for (int i = 0; i < colcnt; i++) {
    if (matrix[row][i] < min) {
      min = matrix[row][i];
    }
  }
  return min;
}

void MyMatrix::Step1(int** matrix) {
  std::cout << "STEP 1" << std::endl;

  matrix_2 = new int*[rowcnt];
  for (int i = 0; i < rowcnt; i++) {
    matrix_2[i] = new int[colcnt];
  }

  for (int i = 0; i < rowcnt; i++) {
    for (int j = 0; j < colcnt; j++) {
      matrix_2[i][j] = matrix[i][j];
    }
  }
  std::cout << std::endl;

  int min = INT_MAX;

  for (int row = 0; row < rowcnt; row++) {
    min = MinInRow(matrix_2, row);
    std::cout << "MIN IN ROW " << row << " = " << min << std::endl;
    for (int col = 0; col < colcnt; col++) {
      matrix_2[row][col] -= min;
    }
  }

  std::cout << std::endl;
  std::cout << "\"- IN ROW\" MATRIX:" << std::endl;
  PrintMatrix(matrix_2);
}

void MyMatrix::Step2(int** matrix) {
  std::cout << std::endl;
  std::cout << "STEP 2" << std::endl;
  std::cout << std::endl;

  int min = INT_MAX;

  for (int col = 0; col < colcnt; col++) {
    min = MinInCol(matrix_2, col);
    std::cout << "MIN IN COL " << col << " = " << min << std::endl;
    for (int row = 0; row < rowcnt; row++) {
      matrix[row][col] -= min;
    }
  }

  std::cout << std::endl;
  std::cout << "\"- IN COL\" MATRIX:" << std::endl;
  PrintMatrix(matrix);
}

int MyMatrix::Opimum() {

  std::cout << std::endl;
  std::cout << "STEP 3" << std::endl;
  std::cout << std::endl;

  int counter_of_zeros = 0;

  for (int i = 0; i < rowcnt; i++) {
    for (int j = 0; j < colcnt; j++) {
      if (matrix_2[i][j] == 0) {
        counter_of_zeros++;
      }
    }
  }

  std::cout << "number of zeros - " << counter_of_zeros << std::endl;

  int counterIter = counter_of_zeros;

  do {
    for (int i = 0; i < rowcnt; i++) {
      for (int j = 0; j < colcnt; j++) {
        if (matrix_2[i][j] == 0) {
          int countRow0 = 0;
          int countRow1 = 0;
          int countCol0 = 0;
          int countCol1 = 0;

          for (int jj = 0; jj < colcnt; jj++) {
            if (matrix_2[i][jj] == 0) {
              countRow0++;
            }
            if (matrix_2[i][jj] == -1) {
              countRow1++;
            }
          }

          for (int ii = 0; ii < rowcnt; ii++) {
            if (matrix_2[ii][j] == 0) {
              countCol0++;
            }
            if (matrix_2[ii][j] == -1) {
              countCol1++;
            }
          }

          if ((countRow0 == 1) || (countCol0 == 1)) {
            matrix_2[i][j] = -1;
          }

          if ((countRow1 == 1) || (countCol1 == 1)) {
            matrix_2[i][j] = -3;
          }
        }
      }
    }

    counter_of_zeros = 0;

    for (int i = 0; i < rowcnt; i++) {
      for (int j = 0; j < colcnt; j++) {
        if (matrix_2[i][j] == 0) {
          counter_of_zeros++;
        }
        std::cout << matrix_2[i][j] << "\t";
      }
      std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << "number of zeros - " << counter_of_zeros << std::endl;

    int flag1 = 0;
    if (counterIter == counter_of_zeros) {

      for (int i = 0; i < rowcnt; i++) {
        for (int j = 0; j < colcnt; j++) {
          if ((matrix_2[i][j] == 0) && (flag1 == 0)) {
            matrix_2[i][j] = -1;
            flag1 = 1;
          }
        }
      }
    } else {
      counterIter = counter_of_zeros;
    }

  } while (counter_of_zeros != 0);

  std::cout << "MATRIX:" << std::endl;
  PrintMatrix(matrix_2);
  std::cout << std::endl;

  KolvoStrokBezM1 = 0;

  for (int i = 0; i < rowcnt; i++) {
    int KolvoM1 = 0;
    for (int j = 0; j < colcnt; j++) {
      if (matrix_2[i][j] == -1) {
        KolvoM1++;
      }
    }
    if (KolvoM1 == 0) {
      StrokiBezM1[KolvoStrokBezM1++] = i;
    }
  }

  int ret = 0;

  if (KolvoStrokBezM1 == 0) {
    std::cout << "OPTIMAL SOLUTION:" << std::endl;
    PrintOptimum();
    ret = 1;
  } else {
    std::cout << "OPTIMAL SOLUTION NOT FOUND!" << std::endl;
    // PrintOptimum();
  }

  return ret;
}

void MyMatrix::Step21() {
  std::cout << std::endl;
  std::cout << "STEP 2.1" << std::endl;
  std::cout << std::endl;

  KolvoStolbSM3 = 0;

  for (int i = 0; i < KolvoStrokBezM1; i++) {
    int tempRow = StrokiBezM1[i];
    for (int j = 0; j < colcnt; j++) {
      if (matrix_2[tempRow][j] == -3) {
        StolbSM3[KolvoStolbSM3++] = j;
      }
    }
  }

  KolvoStrokSM1 = 0;

  for (int j = 0; j < KolvoStolbSM3; j++) {
    int tempCol = StolbSM3[j];
    for (int i = 0; i < rowcnt; i++) {
      if (matrix_2[i][tempCol] == -1) {
        StrokiSM1[KolvoStrokSM1++] = i;
      }
    }
  }

  KolvoStrokNeOtm = 0;

  for (int j = 0; j < rowcnt; j++) {
    int RowIsChecked = 0;

    for (int i = 0; i < KolvoStrokBezM1; i++)
      if (j == StrokiBezM1[i]) RowIsChecked = 1;
    for (int i = 0; i < KolvoStrokSM1; i++)
      if (j == StrokiSM1[i]) RowIsChecked = 1;

    if (RowIsChecked == 0) {
      StrokiNeOtm[KolvoStrokNeOtm++] = j;
    }
  }

  int MinNeVych = INT_MAX;
  for (int i = 0; i < rowcnt; i++) {
    if (isInArray(StrokiNeOtm, KolvoStrokNeOtm, i) ==
        0) {
      for (int j = 0; j < colcnt; j++) {
        if (isInArray(StolbSM3, KolvoStolbSM3, j) ==
            0) {
          if (matrix_2[i][j] < MinNeVych) {
            MinNeVych = matrix_2[i][j];
          }
        }
      }
    }
  }

  for (int i = 0; i < rowcnt; i++) {
    if (isInArray(StrokiNeOtm, KolvoStrokNeOtm, i) ==
        0) {
      for (int j = 0; j < colcnt; j++) {
        if (isInArray(StolbSM3, KolvoStolbSM3, j) ==
            0) {
          matrix_2[i][j] -= MinNeVych;
        }
      }
    } else {
      for (int j = 0; j < colcnt; j++) {
        if (isInArray(StolbSM3, KolvoStolbSM3, j) ==
            1) {
          if (matrix_2[i][j] < 0)
            matrix_2[i][j] = MinNeVych;
          else
            matrix_2[i][j] += MinNeVych;
        }
      }
    }
  }

  std::cout << "MATRIX:" << std::endl;
  for (int i = 0; i < rowcnt; i++) {
    for (int j = 0; j < colcnt; j++) {
      if (matrix_2[i][j] < 0) matrix_2[i][j] = 0;
      std::cout << matrix_2[i][j] << "\t";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

void MyMatrix::Run() {
  Step1(matrix_1);
  Step2(matrix_2);
  int isOpt = 0;
  do {
    isOpt = Opimum();
    if (!isOpt) Step21();
  } while (isOpt == 0);
}

int main() {
  clock_t start, end;
  start = clock();

  MyMatrix *M = new MyMatrix("matrix.txt");
  M->Run();

  end = clock();
  double seconds = (double)(end - start) / CLOCKS_PER_SEC;
  std::cout << "Time = " << seconds << " sec" << std::endl;

  return 0;
}
