#include "file_operation.h"
#include "matrix_operation.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

int main(int argc, const char * argv[])
{
  int option = 0;
  try
  {
    zakozhurnikova::rightArguments(argc, argv);
  }
  catch (const std::invalid_argument& e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
  size_t rows = 0;
  size_t cols = 0;
  std::ifstream input;
  std::ofstream output;
  try
  {
    input.open(argv[2]);
    output.open(argv[3]);
  }
  catch (const std::exception& e)
  {
    std::cerr << "Can not open file\n";
    return 2;
  }
  input >> rows >> cols;
  if (!input)
  {
    std::cerr << "Can not read a number\n";
    return 2;
  }
  if (rows == 0 && cols == 0)
  {
    output << "0 0";
    return 0;
  }
  const size_t s = rows * cols;
  int *matrix = nullptr;
  int *original = nullptr;
  int **matrixPtr = &matrix;
  int **originalPtr = &original;
  if (option == 1)
  {
    int matrix[s];
    int original[s];
    for (size_t i = 0; i < s; i++)
    {
      matrix[i] = 0;
      original[i] = 0;
    }
    *matrixPtr = static_cast<int *>(matrix);
    *originalPtr = static_cast<int *>(original);
  }
  else
  {
    try
    {
      *matrixPtr = new int [rows * cols]{0};
      *originalPtr = new int [rows * cols]{0};
    }
    catch (const std::exception &e)
    {
      delete[] *matrixPtr;
      delete[] *originalPtr;
      matrixPtr = nullptr;
      originalPtr = nullptr;
      std::cerr << e.what() << '\n';
      return 1;
    }
  }
  zakozhurnikova::fillMatrix(matrix, rows, cols);
  for (size_t i = 0; i < rows; i++)
  {
    for (size_t j = 0; j < cols; j++)
    {
      input >> original[i * cols + j];
      if (!input)
      {
        std::cerr << "Incorrect input!\n";
        delete[] matrix;
        delete[] original;
        matrixPtr = nullptr;
        originalPtr = nullptr;
        return 1;
      }
    }
  }
  zakozhurnikova::substractMatrix(original, matrix, rows, cols);
  zakozhurnikova::writeToFile(output, original, rows, cols);
  delete[] matrix;
  delete[] original;
  matrixPtr = nullptr;
  originalPtr = nullptr;
  return 0;
}
