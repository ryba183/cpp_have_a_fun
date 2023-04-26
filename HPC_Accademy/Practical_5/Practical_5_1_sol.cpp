#include <iostream>

// Based on the contents of the previous row, calculates
// the next row of Pascal's triangle, rowNo, which contains 'rowNo' numbers.
void calcNextRow(const int* prevRow, int* nextRow, int rowNo)
{
  // First element in the row
  nextRow[0] = 1;

  // If rowNo == 1, this loop will not perform any iterations.
  for(int i=1 ; i < rowNo-1 ; i++)
  {
    nextRow[i] = prevRow[i] + prevRow[i-1];
  }
  
  // Last element in the row
  nextRow[rowNo-1] = 1;
}


int main(void)
{
  int N;
  std::cout << "Enter number of rows required " << std::endl;
  std::cin >> N;
  
  int* row1 = new int[N];
  int* row2 = new int[N];
  
  // At i == 1, calcNextRow does not require any data
  // from prevRow, hence we do not initialise row1.

  for(int i=1 ; i < N+1 ; i++)
  {
    calcNextRow(row1, row2, i);
    for(int j=0 ; j < i ; j++)
    {
      std::cout << row2[j] << " ";
    }
    std::cout << std::endl;

    int* tmp = row1;
    row1 = row2;
    row2 = tmp;
  }

  delete[] row1;
  delete[] row2;

  return 0;
}