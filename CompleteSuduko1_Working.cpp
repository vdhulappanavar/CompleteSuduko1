// CompleteSuduko1.cpp : Defines the entry point for the console application.
//


//*************************************************************************************************
//***********Pre-Proccessor Directives************************************************************
#include "stdafx.h"
#include<stdio.h>
#include<conio.h>
#include<Windows.h>
//***********Pre-Proccessor Directives************************************************************
//*************************************************************************************************


//***************************************************************************************************************
//*******************************Constants***********************************************************************
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
//*******************************Constants***********************************************************************
//***************************************************************************************************************


//***************************************************************************************************************
//**************USER DEFINED FUNCTIONS***************************************************************************
void intilize_sudoko();
int backtrack(int oldrow , int oldcol, int *newrow , int *newcol);
void BacktrackFor1stGird();
void InitilizeOutputMatrix();
void FindSolution();
void printgridIndex();
void placeNumber(int row , int col);
int getno(int i,int j);
int checkNumber(int sno, int row ,int col);
int CheckRow(int sno , int row, int col);
int CheckCol(int sno , int row, int col);
int checkOriginal(int row,int col);
int CheckBox(int sno , int row, int col);
void printInputMatrix();
void printOutputMatrix();
void BacktrackFor1stGird();
void GotoXY(int x, int y);
void gotoxy(int x, int y);
void print1stPage();
void printSingleGrid(int x , int y);
void printGrid();
void Intilize1stValue();
void ReadAtXY();
void Delay();
void InitilizeInputMatrix();
//**************USER DEFINED FUNCTIONS**************************************************************************
//***************************************************************************************************************

//***************************************************************************************************************
int IndexCount=0;
int FirstGridRow=0 , FirstGirdCol=0;
int InputMatrix[9][9];
int OutputMatrix[9][9];

int BoxIndex[9][2]={ {2,2} , {2,5} , {2,8} , {5,2} , {5,5} , {5,8} , {8,2} , {8,5}, {8,8} };
int xref=3, yref=3;
//***************************************************************************************************************


//***************************************************************************************************************
//******************STRUCTURES***********************************************************************************
struct pos
{
	int row;
	int col;

} orgSudo[9],gridIndex[60];


struct pos1
{
	int X;
	int Y;
}b;
//******************STRUCTURES***********************************************************************************
//***************************************************************************************************************


int _tmain(int argc, _TCHAR* argv[])
{
	intilize_sudoko();
	print1stPage();
	fflush(stdin);
	system("cls");
	printGrid();
	GotoXY(3,3);
	ReadAtXY();	
	return 0;
}

void intilize_sudoko()
{
	int i, j;
	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
		{
			InputMatrix[i][j]=0;
			OutputMatrix[i][j]=0;
		}
	}
}


void Intilize1stValue()
{
	int i,j, flag=0;
	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
		{
			if(OutputMatrix[i][j]==0)
			{
				FirstGridRow=i;
				FirstGirdCol=j;
				flag=1;
				break;
			}
			if(flag==1)
				break;
		}
	}
}

void BacktrackFor1stGird()
{
	int i, value;
	value=OutputMatrix[FirstGridRow][FirstGirdCol];
	for(i=1;i<9;i++)
	{
	
	   if((i != value) && (checkNumber(i, FirstGridRow  ,FirstGirdCol)))
	   {
		   OutputMatrix[FirstGridRow][FirstGirdCol]=i;
	   }
	}
}

void InitilizeOutputMatrix()
{
	int i,j;
	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
		{
			OutputMatrix[i][j]=InputMatrix[i][j];
		}
	}
}



void FindSolution()
{  
	int i,j;
	for(i=0;i<9;i++)
	{
	  for(j=0;j<9;j++)
	  {
         if(OutputMatrix[i][j]==0) 
		 {
			 placeNumber(i,j);
		 }
      }
	}
}

void placeNumber(int row , int col)
{ 
	int i=row,j=col;
  	int newrow, newcolumn;
	int value;
	if (row > 9 || col > 9 || row < 0 || col < 0)
		return;
	value=getno(i,j);
	if(value!=-1)
		 OutputMatrix[i][j]=value;
	else 
	{
		OutputMatrix[i][j] = 0;
		int retVal = backtrack(i,j, &newrow, &newcolumn);
		if (retVal == -1)
		{
			return;
		}
        placeNumber(newrow , newcolumn);
		placeNumber(i,j);
	}

}

int getno(int i,int j)
{
	int sno=OutputMatrix[i][j]+1;
	if(checkOriginal(i,j))
	{
		return OutputMatrix[i][j];
	}

	while(!checkNumber(sno , i , j) && sno <= 9)
	{
		sno++;
	}
	if(sno==10)
		return -1;
	return sno;
}

int checkNumber(int sno, int row ,int col)
{
	if(CheckRow(sno , row , col))
	{
		if(CheckCol(sno ,row, col))
		{
			if(CheckBox( sno , row, col))
			{
				return true;
			}
		}
	}
	return false;
}

int CheckRow(int sno , int row, int col)
{
	int i;
	for(i=0;i<9;i++)
	{
		if(sno==OutputMatrix[row][i] && col != i)
			return false;
	}
	return true;
}

int CheckCol(int sno , int row, int col)
{
	int i;
	for(i=0;i<9;i++)
		if(sno==OutputMatrix[i][col] && row != i)
			return false;
	return true;
}

int CheckBox(int sno , int row, int col)
{
	int i,j, boxrow , boxcol;
	for(i=0;i<9;i++)
	{
		if(row <= BoxIndex[i][0] && col <= BoxIndex[i][1])
		{
			boxrow=BoxIndex[i][0]-2;
			boxcol=BoxIndex[i][1]-2;
			break;
		}
	}

	for(i=0;i<3;i++)
	{
        for(j=0;j<3;j++)
		{
			if(i+boxrow!=row && j+boxcol!=col && OutputMatrix[i+boxrow][j+boxcol]==sno)
				return false;
		}
	}
	return true;
}
int checkOriginal(int row,int col)
{
	int i;
	for(i=0;i<IndexCount;i++)
	{
		if(row==gridIndex[i].row && col==gridIndex[i].col)
			return true;
	}
	return false;
}

int backtrack(int oldrow , int oldcol, int *newrow , int *newcol)
{
	*newrow=oldrow;
	*newcol=oldcol;
	if(*newrow==0 && *newcol==0)
		return -1;
	if(oldcol< 9 && oldcol>0)
		*newcol=oldcol-1;
	else if(oldcol==0 && *newrow > 0)
	{
		*newrow=oldrow-1;
		*newcol=8;
	}

	if(*newrow < 0 || *newcol < 0)
	{
		*newrow = 0;
		*newcol = 0;
		return -1;
	}
	if(checkOriginal(*newrow, *newcol))
		return backtrack(*newrow, *newcol , newrow, newcol);
	else
		return 1;
}

void printInputMatrix()
{
	int i,j;
	printf("Input Matrix \n");
	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
		{
			printf("%3d", InputMatrix[i][j]);
		}
		printf("\n");
	}
}
void printOutputMatrix()
{
	int i,j;
	printf("Output Matrix \n");
	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
		{
			printf("%3d", OutputMatrix[i][j]);
		}
		printf("\n");
	}
}

void printgridIndex()
{
	int i,j;
	printf("grid index \n");
	for(i=0;i<IndexCount;i++)
	{
			printf("%3d  %3d", gridIndex[i].row , gridIndex[i].col);
	}
}

void gotoxy(int x, int y)
{

    COORD coord;

    coord.X = x;

    coord.Y = y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

}
void GotoXY(int x, int y)
{
    HANDLE a;
    COORD b;
    fflush(stdout);
    b.X = x;
    b.Y = y;
    a = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(a,b);
}

void print1stPage()
{
	GotoXY(25,10);
	printf("********************************\n");
	GotoXY(28,11);
	printf("WELCOME TO THE SUDUKO GAME");
	GotoXY(25,12);
	printf("********************************\n");
	 getch();
	 fflush(stdout);

}

void printSingleGrid(int x, int y)
{
	GotoXY(x,y);
	printf("%c%c%c%c",218,196,196,191);
	GotoXY(x,y+1);
	printf("%c  %c",179,179);
	GotoXY(x,y+2);
	printf("%c%c%c%c",192,196,196,217);
}

void printGrid()
{
	int i,j,x=2 , y=2;
	char ch;
	for(i=0;i<9;i=i++)
	{
		for(j=0;j<9;j++)
		{
			printSingleGrid(x,y);
			x=x+3;
		}
		x=2;
		y=y+2;
	}
}

void ReadAtXY()
{
	char key;
	int ch;
	int val,i=0;
	int xpos=3,ypos=3;
	do
	{
		key=getch();
		if(key==127)
		{
			printf("AAA");
			GotoXY(xpos,ypos);
			printf(" ");
		}
		if(key==RIGHT && xpos<27 && xpos>=3)
		{
			xpos=xpos+3; GotoXY(xpos,ypos);
		}
		if(key==LEFT && xpos>3 && xpos<=27)
		{
			xpos=xpos-3; GotoXY(xpos,ypos);
		}
		if(key==UP&& ypos>3 && ypos<=19)
		{
			ypos=ypos-2; GotoXY(xpos,ypos);
		}
		if(key==DOWN && ypos>=3 && ypos<19)
		{
			ypos=ypos+2; GotoXY(xpos,ypos);
		}
		if (key == 's') //Submit to solve
		{
			InitilizeOutputMatrix();	

			Intilize1stValue();
			FindSolution();
			GotoXY(3, 32);
			printgridIndex();
			GotoXY(3, 37);
			printInputMatrix();
			GotoXY(3, 77);
			printOutputMatrix();
			getch();
			break;
		}
		if (key == 27) //ESC
		{
			break;
		}
				
		if(key>'0' && key<='9')
		{
			val = key - 48;
			InputMatrix[(ypos/2)-1][(xpos/3)-1]=val;
			gridIndex[IndexCount].row=(ypos/2)-1;
			gridIndex[IndexCount].col=(xpos/3)-1;
			IndexCount++;
			printf("%d",val);
			getch();
			
		}
		
	}
	while(1);
}



void Delay()
{
    long double i;
    for(i=0; i<=(10000000); i++);
}

void InitilizeInputMatrix()
{
	int i,j;
	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
		{
			InputMatrix[i][j]=0;
		}
	}
}
