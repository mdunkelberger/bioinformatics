#include <iostream>
#include <string>
#include <fstream>

void score(int rows, int columns, int array[rows*columns], std::string dna1, std::string dna2);
void print_arr(int rows, int columns, int array[rows*columns]);

int main() {
  std::ifstream file;
  file.open("example.txt");

  std::string line1;
  std::getline(file, line1);
  std::string line2;
  std::getline(file, line2);

  int rows = line1.length() + 1;
  int columns = line2.length() + 1;

  int dp_table[rows*columns];

  score(rows, columns, dp_table, line1, line2);

  print_arr(rows, columns, dp_table);
}

void  score(int rows, int columns, int array[rows*columns], std::string dna1, std::string dna2) {

  //initialize values of first row and column
  for (int i = 0; i < rows; ++i) {
    array[i*columns] = i * -2;
  }
  for (int j = 1; j < columns; ++j) {
    array[j] = j* -2;
  }

  //dp algorithm
  for (int i = 1; i < rows; ++i) {
    for (int j = 1; j < columns; ++j) {
      //determine if characters are a match
      int diag = -1;
      if (dna1[i - 1] == dna2[j - 1]) {
        diag = 2;
      }

      //determine whether to take vertical, horizontal, or diagonal value
      if (((array[(i - 1)*columns + j - 1] + diag) > (array[(i-1)*columns + j] - 2)) && ((array[(i - 1)*columns + j - 1] + diag) > (array[i*columns + j-1] - 2))) {
        array[i*columns + j] = array[(i - 1)*columns + j - 1] + diag;
      }
      else if (array[(i - 1)*columns + j] - 2 > array[i*columns + j - 1] - 2) {
        array[i*columns + j] = array[(i - 1)*columns + j] - 2;
      }
      else {
        array[i*columns + j] = array[i*columns + j - 1] - 2;
      }
    }
  }
}

void print_arr(int rows, int columns, int array[rows*columns]) {
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < columns; ++j) {
      printf("%4d", array[i*columns + j]);
    }
    std::cout << std::endl;
  }
}
