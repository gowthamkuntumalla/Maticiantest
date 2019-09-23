/*
	Author: Gowtham Kuntumalla 
	gowthamkuntumalla@gmail.com
	Programming test : Matician
	Task: apply convolutions to matrix containing nonnegative integers similar to a grayscale image
*/

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <algorithm> //minmax
#define MIN_V 1000
#define MAX_V -1000	
using namespace std;

// int* ext_elem(unsigned char ** a, int r , int c) //extrema
// {	
// 	static int arr[2]; // (min,max)
// 	arr[0] = MIN_V;
// 	arr[1] = MAX_V;
// 	for (int i; i<r; i++)
// 	{
// 		for(int j; j<c; j++)
// 		{		
// 			if (a[i][j]<arr[0])
// 			{
// 				arr[0] = a[i][j];
// 			}
// 			if (a[i][j]>arr[1])
// 			{
// 				arr[1] = a[i][j];
// 			}		
// 		}	
// 	}
		
// 	return arr;
// }

int main (int argc, char *argv[])
{
  //assuming arguments are given correctly. i.e. greater than 4x4
  //initializations
  cout << "number of rows x columns is " << argv[1] << "x" << argv[2] << endl;
  int rows = atoi (argv[1]);
  int cols = atoi (argv[2]);
  unsigned char mat[rows][cols]; // matrix to store rand int
  srand (time (0));
  for (int i = 0; i < rows; i++)
    {
      for (int j = 0; j < cols; j++)
		{
	 	 	mat[i][j] =  (char) (rand()% 255);  // random integers
	  		cout << mat[i][j] << " ";
		}

	cout<< endl;
    }


  // CONVOLUTION 
  // const short int filter[3] = { -1, 0, 1 };
  // Dy
  time_t start_time, end_time;
  unsigned char Dy[rows-2][cols];
  time(&start_time);  
  // Border Assumption is that matrix keeps reducing in size due to filter just like a CNN reduction ins feature space. ex: in first step 5x5 becomes a 3x5 matrix
  for (int i=0; i<rows-2;i++)
  {
  	for (int j=0; j < cols; j++)
  	{	
  		Dy[i][j] = (char) (-1*(int)mat[i][j] + (int)mat[i+2][j]); // because the instructions askedfor speedup wherever possible
  	}
  }
  time(&end_time);
  double Dy_time = difftime(end_time,start_time);
  cout<< "elasped time for Dy computation is" << Dy_time<<endl;



  //Dx
  unsigned char Dx[rows-2][cols-2];
  time(&start_time);  
 
  // Border Assumption is that matrix keeps reducing in size due to filter just like a CNN reduction ins feature space. ex: in first step 3x5 becomes a 3x3 matrix
  for (int i=0; i<rows-2;i++)
  {
  	for (int j=0; j < cols-2; j++)
  	{	
  		/* NOTE:: There is a slight confusion in the line 4 of the paragraph. hence two lines for Dx*/
  		// case 1: when Dx = Dy * col filter = (mat* row filter) * col filter
  		Dx[i][j] = (char) (-1*(int)Dy[i][j] + (int)Dy[i][j+2]);

  		// case 2: when Dx = mat* col filter
  		// Dx[i][j] = (char) (-1*(int)mat[i][j] + (int)mat[i][j+2]);
  	}
  }
  time(&end_time);
  double Dx_time = difftime(end_time,start_time);
  cout<< "elasped time for Dx computation is" << Dx_time<<endl;
  cout<< "sum of elasped times of both Dy and Dx computation is " << Dy_time + Dx_time<<" sec"<<endl;

  // MIN_MAX Values
  int* extrema_Dy;
  int* extrema_Dx; 
  // extrema_Dy = ext_elem(*Dy,rows-2,cols);
  // //case1: 
  // extrema_Dx = ext_elem(*Dx,rows-2,cols-2);
  // /*case2: extrema_Dx = ext_elem(Dx,rows,cols-2);*/
  // cout<< "min value of Dy = "<<*(extrema_Dy) <<" and max value of Dy is " << *(extrema_Dy+1)<<endl;
  // cout<< "min value of Dx = "<<*(extrema_Dx) <<" and max value of Dx is " << *(extrema_Dx+1)<<endl;




int arr[2]; // (min,max)
arr[0] = MIN_V;
arr[1] = MAX_V;
  for (int i=0; i<rows-2; i++)
  {
    for(int j=0; j<cols; j++)
    {   
      if ((int)Dy[i][j]<arr[0])
      {
        arr[0] = Dy[i][j];
      }
      if ((int)Dy[i][j]>arr[1])
      {
        arr[1] = Dy[i][j];
      }   
    } 
  }

 cout<< "min value of Dy = "<<arr[0] <<" and max value of Dy is " << arr[1]<<endl;

arr[0] = MIN_V;
arr[1] = MAX_V;
  for (int i=0; i<rows-2; i++)
  {
    for(int j=0; j<cols-2; j++)
    {   
      if ((int)Dx[i][j]<arr[0])
      {
        arr[0] = Dx[i][j];
      }
      if ((int)Dx[i][j]>arr[1])
      {
        arr[1] = Dx[i][j];
      }   
    } 
  }

  cout<< "min value of Dx = "<<arr[0] <<" and max value of Dx is " << arr[1]<<endl;
  return 0;
}
