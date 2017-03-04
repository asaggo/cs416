/***********************************************************************
* Program:
*    Lesson 08, Tic-Tac-Toe
* Summary: 
*    This program reads, displays, and writes a Tic-Tac-Toe board
************************************************************************/

#include <iostream>
#include <fstream>
#include <cassert>
using namespace std;


#define PLAYER1 'X'
#define PLAYER2 'O'
#define EMPTY '.'
#define SIZE 3

bool read(         char board[][SIZE], const char* fileName, ifstream& fin);
bool write(  const char board[][SIZE], const char* fileName);
void display(const char board[][SIZE]);
bool didWin( const char board[][SIZE], char turn);

/**********************************************************************
 * Keeps the data and calles the read/display/write functions
 ***********************************************************************/
int main()
{
   char board[SIZE][SIZE];

   // read the board
   char fileName[256];
   cout << "Enter source filename: ";
   cin  >> fileName;

   ifstream fin(fileName);
   if (fin.fail()){
      cout << "fin fail";
      return false;
   }
   if (!read(board, fileName, fin))
   {
      cout << "ERROR: Unable to open file \"" << fileName << "\"\n";
      return 1;
   }
   // display the board
   cout << "Level 1:\n";
   display(board);
   cout << "\n";


   if (!read(board, fileName, fin))
   {
      cout << "ERROR: Unable to open file \"" << fileName << "\"\n";
      return 1;
   }
   cout << "Level 2:\n";
   display(board);
   cout << "\n";


   if (!read(board, fileName, fin))
   {
      cout << "ERROR: Unable to open file \"" << fileName << "\"\n";
      return 1;
   }
   cout << "Level 3:\n";
   display(board);
   cout << "\n";

   fin.close();
   
   // write the board to a file
   cout << "Enter destination filename: ";
   cin  >> fileName;
   if (!write(board, fileName))
   {
      cout << "ERROR: Unable to open file \"" << fileName << "\"\n";
      return 1;
   }

   
   return 0;
}

/**************************************************************
 * READ
 * Read the board from the specified filename
 *************************************************************/
bool read(char board[][SIZE], const char* fileName, ifstream& fin)
{
   assert(*fileName);

   // open the file
//   ifstream fin(fileName);
//   if (fin.fail())
//      return false;

   // read 9 symbols, hopefully they are . X O
   for (int r = 0; r < SIZE; r++)
      for (int c = 0; c < SIZE; c++)
      {
         fin >> board[r][c];
         assert(!fin.fail());
         assert(board[r][c] == PLAYER1 ||
                board[r][c] == PLAYER2 ||
                board[r][c] == EMPTY);
      }

   
   // close the file
//   fin.close();
   return true;
}

/**********************************************************
 * WRITE
 * Write to fileName the board data
 *********************************************************/
bool write(const char board[][SIZE], const char* fileName)
{
   assert(fileName[0] != '\0');

   // open the file
   ofstream fout(fileName);
   if (fout.fail())
      return false;

   // write my 9 symbols
   for (int r = 0; r < SIZE; r++)
      for (int c = 0; c < SIZE; c++)
         fout << board[r][c] << (c == 2 ? '\n' : ' ');

   // close it!
   fout.close();
   cout << "File written\n";
   return true;
}

/*******************************************************
 * DISPLAY
 * Display the contents the the screen
 *****************************************************/
void display(const char board[][SIZE])
{
   // loop through each row
   for (int r = 0; r < SIZE; r++)
   {
      // only the first row is not preceeded with the --+-- magic
      if (r != 0)
         cout << "---+---+---\n";

      // now, on each row, do the column stuff
      for (int c = 0; c < SIZE; c++)
      {
         // display a space for the dot
         if (board[r][c] == '.')
            cout << "   ";
         else
            cout << " " << board[r][c] << " ";

         // end with a | or a newline
         cout << (c == 2 ? '\n' : '|');
      }
   }

   // display who won
   if (didWin(board, PLAYER1))
      cout << PLAYER1 << " won!\n";
   if (didWin(board, PLAYER2))
      cout << PLAYER2 << " won!\n";
   
   return;
}

/********************************************
 * DID WIN
 * Did a given player (determined by the "turn"
 * variable) win the game?
 *******************************************/
bool didWin(const char board[][SIZE], char turn)
{
   int count = 0;
   //checking if the horizontal line is success
   for (int row = 0; row < SIZE; row++){
      count = 0;
      
      for (int col = 0; col < SIZE; col++){
         if (board[row][col] == turn)
            count++;
      }
      if (count == SIZE){
         cout << "turn " << turn << " has won!\n";
         return true;
      }
   }


   //checking if the vertical line is success
   for (int col = 0; col < SIZE; col++){
      count = 0;
      
      for (int row = 0; row < SIZE; row++){
         if (board[row][col] == turn)
            count++;
      }
      if (count == SIZE){
         cout << "turn " << turn << " has won!\n";
         return true;
      }
   }

   //checking if the diagonal line is success (from left to right)
   count = 0;
   for (int row = 0; row < SIZE; row++){
      for (int col = 0; col < SIZE; col++){
         if (row == col){
            if (board[row][col] == turn)
               count++;
         }
      }
   }

   if (count == SIZE){
      cout << "turn " << turn << " has won!\n";
      return true;
   }


   //checking if the diagonal line is success (from right to left diagonal)
   count = 0;
   for (int i = 0; i < SIZE; i++){
      for (int j = SIZE - 1; j >= 0; j--){
         if (board[i][j] == turn)
            count++;
      }
   }
   if (count == SIZE){
      cout << "turn " << turn << " has won!\n";
      return true;
   }

   
   //if you got nothing
   return false;
}
