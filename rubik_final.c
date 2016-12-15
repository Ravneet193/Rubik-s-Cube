#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define bool int
#define true 1
#define false 0
int cubeTemp[6][3][3];
int counter = 0;
void originalCube(int cube[6][3][3])
{
	int i,j,k;
	for(i=0;i<6;i++)
	{
		for(j=0;j<3;j++)
		{
			for(k=0;k<3;k++)
			{cube[i][j][k]=i;}
		}
	}
}
void rCube(int cube[6][3][3])
{
	int i,j,k;
	for(i=0;i<6;i++)
	{
		for(j=0;j<3;j++)
		{
			for(k=0;k<3;k++)
			{cube[i][j][k]=cubeTemp[i][j][k];}
		}
	}
}
void display(int cube[6][3][3])
{
	int i,j,k;
	for(i=0; i<6; i++)
	{
		printf("Face: %d -> ",i);
		for(j=0; j<3; j++)
		{
			for(k=0; k<3; k++)
			{
				printf(" %d ",cube[i][j][k]);
			}
		}
	printf("\n");
	}
	printf("\n");
}

bool isSolved(int cube[6][3][3])
{
	int i,j,k;
 	for(i=0; i < 6; i++)
	{
		for(j=0; j<3; j++)
		{
			for(k=0; k<3; k++)
			{
				if(cube[i][j][k] != i)
				{
					return false;
				}
			}
		}
	}
	return true;
}

void rotateClockwise(int face, int cube[6][3][3])
{ 
	int temp,i;
 	temp = cube[face][0][0];
 	cube[face][0][0] = cube[face][2][0];
 	cube[face][2][0] = cube[face][2][2];
 	cube[face][2][2] = cube[face][0][2];
 	cube[face][0][2] = temp;
 
 	temp = cube[face][0][1];
 	cube[face][0][1] = cube[face][1][0];
 	cube[face][1][0] = cube[face][2][1];
 	cube[face][2][1] = cube[face][1][2];
 	cube[face][1][2] = temp;
 	
 	switch (face)
 	{
	case 0:
		for(i = 0; i<3; i++)
		{ //rotating along the top layer
		 temp = cube[1][0][i];
		 cube[1][0][i] = cube[2][0][i];
		 cube[2][0][i] = cube[4][0][i];
		 cube[4][0][i] = cube[3][0][i];
	 	cube[3][0][i] = temp;
		}
		break;
	case 1:
		for(i=0; i<3; i++)
		{
		 temp = cube[0][2][i];
		 cube[0][2][i] = cube[3][2-i][2];
		 cube[3][2-i][2] = cube[5][0][2-i];
		 cube[5][0][2-i] = cube[2][i][0];
		 cube[2][i][0] = temp;
		}
		break;
	case 2:
		for(i=0; i<3; i++) 
		{
		 temp = cube[0][2-i][2];
		 cube[0][2-i][2] = cube[1][2-i][2];
		 cube[1][2-i][2] = cube[5][2-i][2];
		 cube[5][2-i][2] = cube[4][i][0];
		 cube[4][i][0] = temp;
		}
		break;
	case 3:
		for(i=0; i<3; i++) {
		 temp = cube[0][i][0];
		 cube[0][i][0] = cube[4][2-i][2];
		 cube[4][2-i][2] = cube[5][i][0];
		 cube[5][i][0] = cube[1][i][0];
		 cube[1][i][0] = temp;
		}
		break;
	case 4:
		for(i=0; i<3; i++) {
		 temp = cube[0][0][i];
		 cube[0][0][i] = cube[2][i][2];
		 cube[2][i][2] = cube[5][2][2-i];
		 cube[5][2][2-i] = cube[3][2-i][0];
		 cube[3][2-i][0] = temp;
		}
		break;
	case 5:
		for(i = 0; i<3; i++) { //rotate bottom layer
		 temp = cube[1][2][i];
 		 cube[1][2][i] = cube[3][2][i];
 		 cube[3][2][i] = cube[4][2][i];
		 cube[4][2][i] = cube[2][2][i];
		 cube[2][2][i] = temp;
		}
		break;
	}
 
}
void rotateCounterClockwise(int face, int cube[6][3][3])
{ 
	int temp,i;
 
 	temp = cube[face][0][0];
 	cube[face][0][0] = cube[face][0][2];
 	cube[face][0][2] = cube[face][2][2];
 	cube[face][2][2] = cube[face][2][0];
 	cube[face][2][0] = temp;
 
 	temp = cube[face][0][1];
 	cube[face][0][1] = cube[face][1][2];
 	cube[face][1][2] = cube[face][2][1];
 	cube[face][2][1] = cube[face][1][0];
 	cube[face][1][0] = temp;
 
 	switch (face)
 	{
		case 0:
			for(i = 0; i<3; i++)
			 { //rotating along the top layer
			 temp = cube[1][0][i];
			 cube[1][0][i] = cube[3][0][i];
			 cube[3][0][i] = cube[4][0][i];
			 cube[4][0][i] = cube[2][0][i];
			 cube[2][0][i] = temp;
			 }
			break;
		case 1:
			 for(i=0; i<3; i++)
			 {
			 temp = cube[0][2][i];
			 cube[0][2][i] = cube[2][i][0];
			 cube[2][i][0] = cube[5][0][2-i];
			 cube[5][0][2-i] = cube[3][2-i][2];
			 cube[3][2-i][2] = temp;
			 }
			break;
		case 2:
			for(i=0; i<3; i++)
			 {
			 temp = cube[0][2-i][2];
			 cube[0][2-i][2] = cube[4][i][0];
			 cube[4][i][0] = cube[5][2-i][2];
			 cube[5][2-i][2] = cube[1][2-i][2];
			 cube[1][2-i][2] = temp;
			 }
			break;
		case 3:
			 for(i=0; i<3; i++)
			 {
			 temp = cube[0][i][0];
			 cube[0][i][0] = cube[1][i][0];
			 cube[1][i][0] = cube[5][i][0];
			 cube[5][i][0] = cube[4][2-i][2];
			 cube[4][2-i][2] = temp;
			 }
			break;
		case 4:
			for(i=0; i<3; i++)
			 {
			 temp = cube[0][0][i];
			 cube[0][0][i] = cube[3][2-i][0];
			 cube[3][2-i][0] = cube[5][2][2-i];
			 cube[5][2][2-i] = cube[2][i][2];
			 cube[2][i][2] = temp;
			 }
			break;
		case 5:
			 for(i = 0; i<3; i++)
			 { //rotate bottom layer
			 temp = cube[1][2][i];
			 cube[1][2][i] = cube[2][2][i];
			 cube[2][2][i] = cube[4][2][i];
			 cube[4][2][i] = cube[3][2][i];
			 cube[3][2][i] = temp;
			 }
			break;
		 }
}
void rotateHalf(int face, int cube[6][3][3])
{
 	rotateClockwise(face, cube);
 	rotateClockwise(face, cube);
}
void randomiseCube(int moves)
{
 	int face, type,i;
	for(i=0; i<moves; i++) 
 	{face = (rand() % 6);
 	type = (rand() % 3);
 	if(type == 0)
 	rotateClockwise(face, cubeTemp);
 	if(type == 1)
 	rotateCounterClockwise(face, cubeTemp);
 	if(type == 2)
 	rotateHalf(face, cubeTemp);
 	}
 	display(cubeTemp); // Display cube after randomise for reference
}
bool transform (int rStore [], int face[6], int inc, int moves)
{
	int num = inc + 1;
	if(num < moves)
	{
		if(rStore[num] < 2) // Cycle through types of rStore
		{ // 0 - Clockwise; 1 - Counter; 2 -Half;
			rStore[num]++;
		}
		else if(rStore[num] == 2) // After cycled through rStores...
		{ // Change which face is being rotated
			rStore[num] = 0;
			if (face[num] < 5)
			{
				face[num]++;
			}
			else if(face[num] == 5) // After all faces rotated in every direction...
			{ // Change what happens on the num move
				face[num] = 0;
				// transform num move level up
				if(!transform(rStore, face, num, moves))
				{
					return false;
				}
			}
		}
	}
	else { return false; } // If move limit is exceeded
return true;
}

void solve(int moves)
{
	bool solved = false;
	int test [6][3][3];
	// Set test to equal cubeTemp's randomised state
	rCube(test);
	if(isSolved(test))
	{		
		solved = true;
		printf("Solved :) \n");
		display(test);
	}
	int x,m;
	int rStore[moves];
	for(x = 0; x < moves; x++)
		rStore[x] = 0;
	int face[moves];
	for(x = 0; x < moves; x++)
		face[x] = 0;
	//int counter = 0; // Counts number of tries at the puzzle
	int inc = -1;
	while(!solved)
	{
	// Iterate through all possible combinations of moves
		if(!transform (rStore, face, inc, moves))
		{
			printf("This cube was more than %d",moves);
			printf(" moves away from completion and was not solved\n");
			exit (1);
		}
	// Do the rStores
	for(m = 0; m < moves; m++)
	{
		if(rStore[m] == 0) 
		{
			printf("clockwise  %d\n ",face[m]);
			rotateClockwise(face[m], test); 
		}
		else if(rStore[m] == 1)
		{
			printf("anticlockwise %d\n ",face[m]);
			rotateCounterClockwise(face[m], test);
		}
		else // if (rStore[m] == 2)
		{
			printf("half %d\n ",face[m]);
;			rotateHalf(face[m], test);
		}
	}
	printf("\n");
	if(isSolved(test)) // Test for solved
	{
		solved = true;
		printf("Solved :) \n");
		printf("Found answer on try number: %d\n",counter);
		display(test);
	}
	else // if the solution not found on this try
	{
	//display(test); // show cube for each failed attempt
	rCube(test); // Put cube back to its randomised state
	}
	counter++; // Count number of cycles performed
	}
}

int main()
{
	clock_t begin, end;
	double time_spent;

	begin = clock();
	int i,j,k;
	for(i=0;i<6;i++)
	{
		for(j=0;j<3;j++)
		{
			for(k=0;k<3;k++)
			{cubeTemp[i][j][k]=i;}
		}
	}
	int moves;
	scanf("%d",&moves);
	randomiseCube(moves);
	printf("Searching for answer...\n");
	solve(moves);
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("%d\n",counter);
	printf("\n Time Taken %f\n",time_spent);
return 0;
}
