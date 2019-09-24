/*
	Author: Gowtham Kuntumalla 
	gowthamkuntumalla@gmail.com
	Programming test : Matician
	Task: apply convolutions to matrix containing nonnegative integers similar to a grayscale image
*/

#include <iostream>
#include <vector>
#include <chrono>
#include <ctime>
#include <cstdlib> //rand
#define MIN_V 1000
#define MAX_V -1000

using namespace std;
using namespace std::chrono;

void ext_elem(const vector < vector < int > > & a, size_t r, size_t c, int & min, int & max) //extrema
{
  int sm, lg;
  sm = MIN_V;
  lg = MAX_V;
  for (size_t i = 0; i < r; i++) {
    for (size_t j = 0; j < c; j++) {
      if (a[i][j] < sm) {
        sm = a[i][j];
      } else {
        if (a[i][j] > lg) {
          lg = a[i][j];
        }
      }
    }
  }
  min = sm;
  max = lg;
  return;
}

int main(int argc, char * argv[]) {
  //init assuming arguments are given correctly. i.e. greater than 3x3
  cout << "number of rows x columns is " << argv[1] << "x" << argv[2] << endl;
  size_t rows = atoi(argv[1]);
  size_t cols = atoi(argv[2]);
  unsigned char mat[rows][cols]; 
  srand(time(0));
  for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < cols; j++) {
      mat[i][j] = rand() % 255;
    }
  }

  /* CONVOLUTION */

  /* Dy */
  vector < vector < int > > Dy(rows - 2, vector < int > (cols));
  auto start_Dy = high_resolution_clock::now();
  // Border Assumption is that matrix keeps reducing in size due to filter just like a CNN reduction ins feature space. ex: in first step 5x5 becomes a 3x5 matrix
  for (size_t i = 0; i < rows - 2; i++) {
    for (size_t j = 0; j < cols; j++) {
      Dy[i][j] = -1 * (size_t) mat[i][j] + (size_t) mat[i + 2][j]; // because the instructions askedfor speedup wherever possible
    }
  }
  auto end_Dy = high_resolution_clock::now();
  auto duration_Dy = duration_cast < microseconds > (end_Dy - start_Dy);
  cout << "elasped time for Dy computation is " << duration_Dy.count() << " microseconds" << endl;

  /* Dx */
  vector < vector < int > > Dx(rows - 2, vector < int > (cols - 2));
  auto start_Dx = high_resolution_clock::now();
  // Border Assumption is that matrix keeps reducing in size due to filter just like a CNN reduction ins feature space. ex: in this step 3x5 becomes a 3x3 matrix
  for (int i = 0; i < rows - 2; i++) {
    for (int j = 0; j < cols - 2; j++) {
      /* NOTE:: There is a slight confusion in the line 4 of the PS. Should filter be individually applied on original matrix? hence two lines for Dx*/
      /* case 1: when Dx = Dy * col filter = (mat* row filter) * col filter */
      Dx[i][j] = -1 * (size_t) Dy[i][j] + (size_t) Dy[i][j + 2];
      /* case 2: when Dx = mat* col filter
      Dx[i][j] = -1*(size_t)mat[i][j] + (size_t)mat[i][j+2];*/
    }
  }
  auto end_Dx = high_resolution_clock::now();
  auto duration_Dx = duration_cast < microseconds > (end_Dx - start_Dx);
  cout << "elasped time for Dx computation = " << duration_Dx.count() << " microseconds" << endl;
  cout << "sum of elasped times of both Dy and Dx computation = " << duration_Dy.count() + duration_Dx.count() << " microseconds" << endl;

  /* MIN_MAX Values */
  int min_Dy = 0, max_Dy = 0;
  int min_Dx = 0, max_Dx = 0;
  ext_elem(Dy, rows - 2, cols, min_Dy, max_Dy);
  //case1: 
  ext_elem(Dx, rows - 2, cols - 2, min_Dx, max_Dx);
  //case2: extrema_Dx = ext_elem(Dx,rows,cols-2,min_Dx,max_Dx);
  cout << "min value of Dy = " << min_Dy << " and max value of Dy = " << max_Dy << endl;
  cout << "min value of Dx = " << min_Dx << " and max value of Dx = " << max_Dx << endl;
  return 0;
}