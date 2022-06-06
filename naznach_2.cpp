// Copyright 2021 "Assignment problem" Titova Nina
#include <fstream>
#include <iostream>
#include <cstring>
#include <limits>

class MyMatrix {
 public:
  int N;  // длина строк
  int K;  // кол-во вариантов на каждую позицию
  int minLetter;
  int maxLetter;
  char* strShifr;
  char* strRight;

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

  char* resultStr;

  MyMatrix(std::string filename);

  ~MyMatrix();

  void PrintMatrix(int** matrix);
  void PrintOptimum();

  int isInArray(int* arr, int arrSZ, int element);

  int MinInCol(int** matrix, int col);
  int MinInRow(int** matrix, int row);
  int MaxInRow(int** matrix, int row);

  void Step0(int** matrix);
  void Step1(int** matrix);
  void Step2(int** matrix);
  void Step21();

  int Opimum();

  void Run();
};

MyMatrix::MyMatrix(std::string filename) {
  std::ifstream fmat(filename);

  if (!fmat.is_open()) {
    //std::cout << "FAIL FILE" << std::endl;
  } else {
    fmat >> N;
    fmat >> K;
    strShifr = new char[N];
    strRight = new char[N];
    for (int i = 0; i < N; i++) {
      fmat >> strShifr[i];
    }
    for (int i = 0; i < N; i++) {
      fmat >> strRight[i];
    }
    std::cout << N << " " << K << " " << std::endl;

    for (int i = 0; i < N; i++) {
      std::cout << strShifr[i];
    }
    std::cout << std::endl;

    for (int i = 0; i < N; i++) {
      std::cout << strRight[i];
    }
    std::cout << std::endl;

    minLetter = 'z' + 1;
    maxLetter = 'A' - 1;

    for (int i = 0; i < N; i++) {
      if (strShifr[i] < minLetter) minLetter = strShifr[i];
      if (strRight[i] < minLetter) minLetter = strRight[i];

      if (strShifr[i] > maxLetter) maxLetter = strShifr[i];
      if (strRight[i] > maxLetter) maxLetter = strRight[i];
    }

    std::cout << "minLetter = " << minLetter << std::endl;
    std::cout << "maxLetter = " << maxLetter << std::endl;

    matrix_1 = new int*[125];
    for (int i = 0; i < 125; i++) {
      matrix_1[i] = new int[125];
    }  // изначальная матрица

    for (int i = minLetter; i <= maxLetter; i++) {
      for (int j = minLetter; j <= maxLetter; j++) {
        char symbi = i;
        char symbj = j;
        int isi = 0;
        int isj = 0;
        for (int sym = 0; sym < N; sym++) {
          if (symbi == strRight[sym]) isi = 1;
          if (symbj == strRight[sym]) isj = 1;
        }
        if (isi == 1 && isj == 1) {
          matrix_1[i][j] = NULL;
        }
      }
    }

    for (int i = 0; i < N; i++) {
      matrix_1[strShifr[i]][strRight[i]] += 1;
    }

    StrokiBezM1 = new int[K + 1];
    StolbSM3 = new int[K + 1];
    StrokiSM1 = new int[K + 1];
    StrokiNeOtm = new int[K + 1];

    std::cout << "ORIGINAL MATRIX:" << std::endl;
    PrintMatrix(matrix_1);
  }
  std::cout << std::endl;

  fmat.close();
}

MyMatrix::~MyMatrix() {
  delete[] StrokiBezM1;
  delete[] StrokiNeOtm;
  delete[] StrokiSM1;
  delete[] StolbSM3;
  delete[] strShifr;
  delete[] strRight;
  delete[] resultStr;

  for (int i = 0; i < 125; i++) delete[] matrix_1[i];
  delete[] matrix_1;

  for (int i = 0; i < 125; i++) delete[] matrix_2[i];
  delete[] matrix_2;
}

void MyMatrix::PrintMatrix(int** matrix) {
  for (int i = minLetter; i <= maxLetter; i++) {
    int flag = 0;
    for (int j = minLetter; j <= maxLetter; j++) {
      char symbi = i;
      char symbj = j;
      int isi = 0;
      int isj = 0;
      for (int sym = 0; sym < N; sym++) {
        if (symbi == strRight[sym]) isi = 1;
        if (symbj == strRight[sym]) isj = 1;
      }
      if (isi == 1 && isj == 1) {
        std::cout << matrix_1[i][j] << "\t";
        flag = 1;
      }
    }
    if (flag == 1) {
      std::cout << std::endl;
    }
  }
}

void MyMatrix::PrintOptimum() {
  int resultSum = 0;
  resultStr = new char[K];
  int temp = 0;
  for (int i = minLetter; i <= maxLetter; i++) {
    for (int j = minLetter; j <= maxLetter; j++) {
      char symbi = i;
      char symbj = j;
      int isi = 0;
      int isj = 0;
      for (int sym = 0; sym < N; sym++) {
        if (symbi == strRight[sym]) isi = 1;
        if (symbj == strRight[sym]) isj = 1;
      }
      if (isi == 1 && isj == 1) {
        if (matrix_2[i][j] == -1) {
          resultSum += matrix_1[i][j];
          resultStr[temp++] = j;
        }
      }
    }
  }
  std::cout << resultSum << std::endl;
  for (int i = 0; i < K; i++) {
    std::cout << resultStr[i];
  }
}

int MyMatrix::isInArray(int* arr, int arrSZ, int element) {
  for (int i = 0; i < arrSZ; i++) {
    if (element == arr[i]) return 1;
  }
  return 0;
}

int MyMatrix::MinInCol(int** matrix, int col) {
  //int min = INT_MAX;
  int min = 2147483647;

  for (int i = minLetter; i <= maxLetter; i++) {
    char symbi = i;
    int isi = 0;
    for (int sym = 0; sym < N; sym++) {
      if (symbi == strRight[sym]) isi = 1;
    }
    if (isi == 1) {
      if (matrix[i][col] < min) {
        min = matrix[i][col];
      }
    }
  }
  return min;
}

int MyMatrix::MinInRow(int** matrix, int row) {
  //int min = INT_MAX;
  int min = 2147483647;

  for (int i = minLetter; i <= maxLetter; i++) {
    char symbi = i;
    int isi = 0;
    for (int sym = 0; sym < N; sym++) {
      if (symbi == strRight[sym]) isi = 1;
    }
    if (isi == 1) {
      if (matrix[row][i] < min) {
        min = matrix[row][i];
      }
    }
  }
  return min;
}

int MyMatrix::MaxInRow(int** matrix, int row) {
  //int max = INT_MIN;
  int max = -2147483647;

  for (int i = minLetter; i <= maxLetter; i++) {
    char symbi = i;
    int isi = 0;
    for (int sym = 0; sym < N; sym++) {
      if (symbi == strRight[sym]) isi = 1;
    }
    if (isi == 1) {
      if (matrix[row][i] > max) {
        max = matrix[row][i];
      }
    }
  }
  return max;
}

void MyMatrix::Step0(int** matrix) {
  std::cout << "STEP 0" << std::endl;

  matrix_2 = new int*[125];
  for (int i = 0; i < 125; i++) {
    matrix_2[i] = new int[125];
  }  // изменяющаяся матрица

  for (int i = minLetter; i <= maxLetter; i++) {
    for (int j = minLetter; j <= maxLetter; j++) {
      matrix_2[i][j] = matrix[i][j];
    }
  }
  std::cout << std::endl;

  //int max = INT_MIN;
  int max = -2147483647;

  for (int row = minLetter; row <= maxLetter; row++) {
    char symbi = row;
    int isi = 0;
    for (int sym = 0; sym < N; sym++) {
      if (symbi == strRight[sym]) isi = 1;
    }
    if (isi == 1) {
      max = MaxInRow(matrix_2, row);
      std::cout << "MAX IN ROW " << row << " = " << max << std::endl;
      for (int col = minLetter; col <= maxLetter; col++) {
        char symbj = col;
        int isj = 0;
        for (int sym = 0; sym < N; sym++) {
          if (symbj == strRight[sym]) isj = 1;
        }
        if (isj == 1) {
          matrix_2[row][col] = abs(matrix_2[row][col] - max);
        }
      }
    }
  }

  std::cout << std::endl;
  std::cout << "\"- MAX IN ROW\" MATRIX:" << std::endl;
  PrintMatrix(matrix_2);
}

void MyMatrix::Step1(int** matrix) {
  std::cout << "STEP 1" << std::endl;

  //int min = INT_MAX;
  int min = 2147483647;

  for (int row = minLetter; row <= maxLetter; row++) {
    char symbi = row;
    int isi = 0;
    for (int sym = 0; sym < N; sym++) {
      if (symbi == strRight[sym]) isi = 1;
    }
    if (isi == 1) {
      min = MinInRow(matrix_2, row);
      std::cout << "MIN IN ROW " << row << " = " << min << std::endl;
      for (int col = minLetter; col <= maxLetter; col++) {
        char symbj = col;
        int isj = 0;
        for (int sym = 0; sym < N; sym++) {
          if (symbj == strRight[sym]) isj = 1;
        }
        if (isj == 1) {
          matrix_2[row][col] -= min;
        }
      }
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

  //int min = INT_MAX;
  int min = 2147483647;

  for (int col = minLetter; col <= maxLetter; col++) {
    char symbj = col;
    int isj = 0;
    for (int sym = 0; sym < N; sym++) {
      if (symbj == strRight[sym]) isj = 1;
    }
    if (isj == 1) {
      min = MinInCol(matrix_2, col);
      std::cout << "MIN IN COL " << col << " = " << min << std::endl;
      for (int row = minLetter; row <= maxLetter; row++) {
        char symbi = row;
        int isi = 0;
        for (int sym = 0; sym < N; sym++) {
          if (symbi == strRight[sym]) isi = 1;
        }
        if (isi == 1) {
          matrix[row][col] -= min;
        }
      }
    }
  }

  std::cout << std::endl;
  std::cout << "\"- IN COL\" MATRIX:" << std::endl;
  PrintMatrix(matrix);
}

int MyMatrix::Opimum() {
  // выбор оптимального решения

  std::cout << std::endl;
  std::cout << "STEP 3" << std::endl;
  std::cout << std::endl;

  int counter_of_zeros = 0;

  for (int i = minLetter; i <= maxLetter; i++) {
    for (int j = minLetter; j <= maxLetter; j++) {
      char symbi = i;
      char symbj = j;
      int isi = 0;
      int isj = 0;
      for (int sym = 0; sym < N; sym++) {
        if (symbi == strRight[sym]) isi = 1;
        if (symbj == strRight[sym]) isj = 1;
      }
      if (isi == 1 && isj == 1) {
        if (matrix_2[i][j] == 0) {
          counter_of_zeros++;
        }
      }
    }
  }

  int counterIter = counter_of_zeros;

  do {
    for (int i = minLetter; i <= maxLetter; i++) {
      for (int j = minLetter; j <= maxLetter; j++) {
        char symbi = i;
        char symbj = j;
        int isi = 0;
        int isj = 0;
        for (int sym = 0; sym < N; sym++) {
          if (symbi == strRight[sym]) isi = 1;
          if (symbj == strRight[sym]) isj = 1;
        }
        if (isi == 1 && isj == 1) {
          if (matrix_2[i][j] == 0) {
            int countRow0 = 0;
            int countRow1 = 0;
            int countCol0 = 0;
            int countCol1 = 0;

            // проходимся по строке, в которой встретили 0
            for (int jj = minLetter; jj <= maxLetter; jj++) {
              char symbjj = jj;
              int isjj = 0;
              for (int sym = 0; sym < N; sym++) {
                if (symbjj == strRight[sym]) isjj = 1;
              }
              if (isjj == 1) {
                if (matrix_2[i][jj] == 0) {
                  countRow0++;
                }
                if (matrix_2[i][jj] == -1) {
                  countRow1++;
                }
              }
            }

            // проходимся по столбцу, в котором встретили 0
            for (int ii = minLetter; ii <= maxLetter; ii++) {
              char symbii = ii;
              int isii = 0;
              for (int sym = 0; sym < N; sym++) {
                if (symbii == strRight[sym]) isii = 1;
              }
              if (isii == 1) {
                if (matrix_2[ii][j] == 0) {
                  countCol0++;
                }
                if (matrix_2[ii][j] == -1) {
                  countCol1++;
                }
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
    }

    counter_of_zeros = 0;

    for (int i = minLetter; i <= maxLetter; i++) {
      for (int j = minLetter; j <= maxLetter; j++) {
        char symbi = i;
        char symbj = j;
        int isi = 0;
        int isj = 0;
        for (int sym = 0; sym < N; sym++) {
          if (symbi == strRight[sym]) isi = 1;
          if (symbj == strRight[sym]) isj = 1;
        }
        if (isi == 1 && isj == 1) {
          if (matrix_2[i][j] == 0) {
            counter_of_zeros++;
          }
          std::cout << matrix_2[i][j] << "\t";
        }
      }
      std::cout << std::endl;
    }
    std::cout << std::endl;
     std::cout << "number of zeros - " << counter_of_zeros << std::endl;

    int flag1 = 0;
    if (counterIter == counter_of_zeros) {  // количество нулей не поменялось, значит зациклилась
      for (int i = minLetter; i <= maxLetter; i++) {
        for (int j = minLetter; j <= maxLetter; j++) {
          char symbi = i;
          char symbj = j;
          int isi = 0;
          int isj = 0;
          for (int sym = 0; sym < N; sym++) {
            if (symbi == strRight[sym]) isi = 1;
            if (symbj == strRight[sym]) isj = 1;
          }
          if (isi == 1 && isj == 1) {
            if ((matrix_2[i][j] == 0) && (flag1 == 0)) {
              matrix_2[i][j] = -1;
              flag1 = 1;
            }
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

  for (int i = minLetter; i <= maxLetter; i++) {
    char symbi = i;
    int isi = 0;
    for (int sym = 0; sym < N; sym++) {
      if (symbi == strRight[sym]) isi = 1;
    }
    if (isi == 1) {
      int KolvoM1 = 0;
      for (int j = minLetter; j <= maxLetter; j++) {
        char symbj = j;
        int isj = 0;
        for (int sym = 0; sym < N; sym++) {
          if (symbj == strRight[sym]) isj = 1;
        }
        if (isj == 1) {
          if (matrix_2[i][j] == -1) {
            KolvoM1++;
          }
        }
      }
      if (KolvoM1 == 0) {
        StrokiBezM1[KolvoStrokBezM1++] = i;
      }
    }
  }

  int ret = 0;

  if (KolvoStrokBezM1 == 0) {
    std::cout << "OPTIMAL SOLUTION:" << std::endl;
    PrintOptimum();
    ret = 1;
  } else {
    std::cout << "OPTIMAL SOLUTION NOT FOUND:" << std::endl;
    PrintOptimum();
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
    for (int j = minLetter; j <= maxLetter; j++) {
      char symbj = j;
      int isj = 0;
      for (int sym = 0; sym < N; sym++) {
        if (symbj == strRight[sym]) isj = 1;
      }
      if (isj == 1) {
        if (matrix_2[tempRow][j] == -3) {
          StolbSM3[KolvoStolbSM3++] = j;
        }
      }
    }
  }

  KolvoStrokSM1 = 0;

  for (int j = 0; j < KolvoStolbSM3; j++) {
    int tempCol = StolbSM3[j];
    for (int i = minLetter; i <= maxLetter; i++) {
      char symbi = i;
      int isi = 0;
      for (int sym = 0; sym < N; sym++) {
        if (symbi == strRight[sym]) isi = 1;
      }
      if (isi == 1) {
        if (matrix_2[i][tempCol] == -1) {
          StrokiSM1[KolvoStrokSM1++] = i;
        }
      }
    }
  }

  KolvoStrokNeOtm = 0;

  for (int j = minLetter; j <= maxLetter; j++) {
    char symbj = j;
    int isj = 0;
    for (int sym = 0; sym < N; sym++) {
      if (symbj == strRight[sym]) isj = 1;
    }
    if (isj == 1) {
      int RowIsChecked = 0;

      for (int i = 0; i < KolvoStrokBezM1; i++)
        if (j == StrokiBezM1[i]) RowIsChecked = 1;
      for (int i = 0; i < KolvoStrokSM1; i++)
        if (j == StrokiSM1[i]) RowIsChecked = 1;

      if (RowIsChecked == 0) {
        StrokiNeOtm[KolvoStrokNeOtm++] = j;
      }
    }
  }

  //int MinNeVych = INT_MAX;
  int MinNeVych = 2147483647;

  for (int i = minLetter; i <= maxLetter; i++) {
    char symbi = i;
    int isi = 0;
    for (int sym = 0; sym < N; sym++) {
      if (symbi == strRight[sym]) isi = 1;
    }
    if (isi == 1) {
      if (isInArray(StrokiNeOtm, KolvoStrokNeOtm, i) == 0) {  // Если нет в списке вычеркнутых строк
        for (int j = minLetter; j <= maxLetter; j++) {
          char symbj = j;
          int isj = 0;
          for (int sym = 0; sym < N; sym++) {
            if (symbj == strRight[sym]) isj = 1;
          }
          if (isj == 1) {
            if (isInArray(StolbSM3, KolvoStolbSM3, j) == 0) {  // Если нет в списке вычеркнутых столбцов
              if (matrix_2[i][j] < MinNeVych) {
                MinNeVych = matrix_2[i][j];
              }
            }
          }
        }
      }
    }
  }

  for (int i = minLetter; i <= maxLetter; i++) {
    char symbi = i;
    int isi = 0;
    for (int sym = 0; sym < N; sym++) {
      if (symbi == strRight[sym]) isi = 1;
    }
    if (isi == 1) {
      if (isInArray(StrokiNeOtm, KolvoStrokNeOtm, i) == 0) {  // Если нет в списке вычеркнутых строк
        for (int j = minLetter; j <= maxLetter; j++) {
          char symbj = j;
          int isj = 0;
          for (int sym = 0; sym < N; sym++) {
            if (symbj == strRight[sym]) isj = 1;
          }
          if (isj == 1) {
            if (isInArray(StolbSM3, KolvoStolbSM3, j) == 0) {  // Если нет в списке вычеркнутых столбцов
              matrix_2[i][j] -= MinNeVych;
            }
          }
        }
      } else {  // Если есть в списке вычеркнутых строк
        for (int j = minLetter; j <= maxLetter; j++) {
          char symbj = j;
          int isj = 0;
          for (int sym = 0; sym < N; sym++) {
            if (symbj == strRight[sym]) isj = 1;
          }
          if (isj == 1) {
            if (isInArray(StolbSM3, KolvoStolbSM3, j) == 1) {  // Если нет в списке вычеркнутых столбцов
              if (matrix_2[i][j] < 0)
                matrix_2[i][j] = MinNeVych;
              else
                matrix_2[i][j] += MinNeVych;
            }
          }
        }
      }
    }
  }

  std::cout << "MATRIX:" << std::endl;
  for (int i = minLetter; i <= maxLetter; i++) {
    int flag = 0;
    for (int j = minLetter; j <= maxLetter; j++) {
      char symbi = i;
      char symbj = j;
      int isi = 0;
      int isj = 0;
      for (int sym = 0; sym < N; sym++) {
        if (symbi == strRight[sym]) isi = 1;
        if (symbj == strRight[sym]) isj = 1;
      }
      if (isi == 1 && isj == 1) {
        if (matrix_2[i][j] < 0) matrix_2[i][j] = 0;
        std::cout << matrix_2[i][j] << "\t";
        flag = 1;
      }
    }
    if (flag == 1) {
      std::cout << std::endl;
    }
  }
  std::cout << std::endl;
}

void MyMatrix::Run() {
  Step0(matrix_1);
  Step1(matrix_2);
  Step2(matrix_2);
  int isOpt = 0;
  do {
    isOpt = Opimum();
    if (!isOpt) Step21();
  } while (isOpt == 0);
}

int main() {
  MyMatrix* M = new MyMatrix("input.txt");

  M->Run();

  //delete M;

  return 0;
}
