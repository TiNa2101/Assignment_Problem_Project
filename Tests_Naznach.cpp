#include "CppUnitTest.h"
#include "..\Naznach\naznach.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestsNaznach
{
	TEST_CLASS(TestsNaznach)
	{
	public:
        MyMatrix* Matrix1 = new MyMatrix("test_matrix1.txt");
        MyMatrix* Matrix2 = new MyMatrix("test_matrix2.txt");
        MyMatrix* Matrix3 = new MyMatrix("test_matrix3.txt");

        /*Matrix1:       -> After Step1:     -> After Step2:
                  15 10 9               6 1 0               6 0 0
                  9 15 10               0 6 1               0 5 1
                  10 12 8               2 4 0               2 3 0
        */

        /*Matrix2:         -> After Step1:         -> After Step2:
                  3 9 2 3 7               1 7 0 1 5               0 7 0 0 5
                  6 1 5 6 6               5 0 4 5 5               4 0 4 4 5
                  9 4 7 10 3              6 1 4 7 0               5 1 4 6 0
                  2 5 4 2 1               1 4 3 1 0               0 4 3 0 0
                  9 6 2 4 5               7 4 0 2 3               6 4 0 1 3
        */

        /*Matrix3:       -> After Step1:       -> After Step2:       -> After Step21:
                  1 4 6 3                0 3 5 2              0 3 2 2                0 2 1 1
                  9 7 10 9               2 0 3 2              2 0 0 2                3 0 0 2
                  4 5 11 7               0 1 7 3              0 1 4 3                0 0 3 2
                  8 7 8 5                3 2 3 0              3 2 0 0                4 2 0 0
        */

		TEST_METHOD(Test_MinInRow) {
          int min_rows_matrix1[3] = {9, 9, 8};
          for (int i = 0; i < Matrix1->rowcnt; i++) {
            Assert::IsTrue(Matrix1->MinInRow(Matrix1->matrix_1, i) == min_rows_matrix1[i]);
          }

          int min_rows_matrix2[5] = {2, 1, 3, 1, 2};
          for (int i = 0; i < Matrix2->rowcnt; i++) {
            Assert::IsTrue(Matrix2->MinInRow(Matrix2->matrix_1, i) == min_rows_matrix2[i]);
          }

          int min_rows_matrix3[4] = {1, 7, 4, 5};
          for (int i = 0; i < Matrix3->rowcnt; i++) {
            Assert::IsTrue(Matrix3->MinInRow(Matrix3->matrix_1, i) == min_rows_matrix3[i]);
          }
		}

        TEST_METHOD(Test_MinInCol) {
          int min_cols_matrix1[3] = {9, 10, 8};
          for (int i = 0; i < Matrix1->colcnt; i++) {
            Assert::IsTrue(Matrix1->MinInCol(Matrix1->matrix_1, i) == min_cols_matrix1[i]);
          }

          int min_cols_matrix2[5] = {2, 1, 2, 2, 1};
          for (int i = 0; i < Matrix2->colcnt; i++) {
            Assert::IsTrue(Matrix2->MinInCol(Matrix2->matrix_1, i) == min_cols_matrix2[i]);
          }

          int min_cols_matrix3[4] = {1, 4, 6, 3};
          for (int i = 0; i < Matrix3->colcnt; i++) {
            Assert::IsTrue(Matrix3->MinInCol(Matrix3->matrix_1, i) == min_cols_matrix3[i]);
          }
        }

		TEST_METHOD(Test_isInArray) {
          // True
          int test_array1[3] = {9, 10, 15};
          for (int i = 0; i < Matrix1->rowcnt; i++) {
            Assert::IsTrue(Matrix1->isInArray(Matrix1->matrix_1[0],
                                              Matrix1->colcnt,
                                              test_array1[i]) == 1);
          }

          // False
          int test_array2[5] = {1, 8, 5, 0, 2};
          for (int i = 0; i < Matrix2->rowcnt; i++) {
            Assert::IsTrue(Matrix2->isInArray(Matrix2->matrix_1[2],
                                              Matrix2->colcnt,
                                              test_array2[i]) == 0);
          }
        }

		TEST_METHOD(Test_Step1) {
          int after_Step1_1[3][3] = {{6, 1, 0},
                                     {0, 6, 1},
                                     {2, 4, 0}};
          Matrix1->Step1(Matrix1->matrix_1);

          for (int i = 0; i < Matrix1->rowcnt; i++) {
            for (int j = 0; j < Matrix1->colcnt; j++) {
              Assert::IsTrue(Matrix1->matrix_2[i][j] == after_Step1_1[i][j]);
            }
          }

          int after_Step1_2[5][5] = {{1, 7, 0, 1, 5},
                                     {5, 0, 4, 5, 5},
                                     {6, 1, 4, 7, 0},
                                     {1, 4, 3, 1, 0},
                                     {7, 4, 0, 2, 3}};
          Matrix2->Step1(Matrix2->matrix_1);

          for (int i = 0; i < Matrix2->rowcnt; i++) {
            for (int j = 0; j < Matrix2->colcnt; j++) {
              Assert::IsTrue(Matrix2->matrix_2[i][j] == after_Step1_2[i][j]);
            }
          }

          int after_Step1_3[4][4] = {{0, 3, 5, 2},
                                     {2, 0, 3, 2},
                                     {0, 1, 7, 3},
                                     {3, 2, 3, 0}};
          Matrix3->Step1(Matrix3->matrix_1);

          for (int i = 0; i < Matrix3->rowcnt; i++) {
            for (int j = 0; j < Matrix3->colcnt; j++) {
              Assert::IsTrue(Matrix3->matrix_2[i][j] == after_Step1_3[i][j]);
            }
          }
        }

        TEST_METHOD(Test_Step2) {
          int after_Step2_1[3][3] = {{6, 0, 0},
                                     {0, 5, 1},
                                     {2, 3, 0}};
          Matrix1->Step2(Matrix1->matrix_2);

          for (int i = 0; i < Matrix1->rowcnt; i++) {
            for (int j = 0; j < Matrix1->colcnt; j++) {
              Assert::IsTrue(Matrix1->matrix_2[i][j] == after_Step2_1[i][j]);
            }
          }

          int after_Step2_2[5][5] = {{0, 7, 0, 0, 5},
                                     {4, 0, 4, 4, 5},
                                     {5, 1, 4, 6, 0},
                                     {0, 4, 3, 0, 0},
                                     {6, 4, 0, 1, 3}};
          Matrix2->Step2(Matrix2->matrix_2);

          for (int i = 0; i < Matrix2->rowcnt; i++) {
            for (int j = 0; j < Matrix2->colcnt; j++) {
              Assert::IsTrue(Matrix2->matrix_2[i][j] == after_Step2_2[i][j]);
            }
          }

          int after_Step2_3[4][4] = {{0, 3, 2, 2},
                                     {2, 0, 0, 2},
                                     {0, 1, 4, 3},
                                     {3, 2, 0, 0}};
          Matrix3->Step2(Matrix3->matrix_2);

          for (int i = 0; i < Matrix3->rowcnt; i++) {
            for (int j = 0; j < Matrix3->colcnt; j++) {
              Assert::IsTrue(Matrix3->matrix_2[i][j] == after_Step2_3[i][j]);
            }
          }
        }

        TEST_METHOD(Test_Step21) {
            int after_Step21_3[4][4] = {{0, 2, 1, 1},
                                        {3, 0, 0, 2},
                                        {0, 0, 3, 2},
                                        {4, 2, 0, 0}};
          int isOpt = 0;
          do {
            isOpt = Matrix3->Opimum();
            if (!isOpt) Matrix3->Step21();
          } while (isOpt == 0);

          for (int i = 0; i < Matrix3->rowcnt; i++) {
            for (int j = 0; j < Matrix3->colcnt; j++) {
              if (Matrix3->matrix_2[i][j] < 0) {
                Assert::IsTrue(0 == after_Step21_3[i][j]);
              } else
                Assert::IsTrue(Matrix3->matrix_2[i][j] == after_Step21_3[i][j]);
            }
          }
        }

	};
}
