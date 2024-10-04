/*
    Dion Lin
    3/25/24
    COP3223
    A7: 2D Arrays 
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// this function will load in all of the bombs up to 30 randomly
void load_bomb(int width, int height, int board[width][height]){
  srand(time(0)); 
  int bombs = 0; 
  while (bombs < 30) {
        int x = rand() % width;
        int y = rand() % height;
        if (board[x][y] != -1){
          board[x][y] = -1;
          }
        bombs++; 
  }
}
// this function gives the user hints by incrementing by 1 all of the cells around the bomb
void set_hints(int width, int height, int board[width][height]){
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if(board[x][y] == 0){
              int count_bomb = 0; 
              // top left
              if (x - 1 >= 0 && y - 1 >= 0 && board[x-1][y-1] == -1)
                count_bomb++; 
              // top
              if (x - 1 >= 0 && board[x-1][y] == -1)
                count_bomb++; 
              // top right
              if (x - 1 >= 0 && y + 1 <= height && board[x - 1][y+1] == -1)
                count_bomb++; 
              // left 
              if (y - 1 >= 0 && board[x][y-1] == -1)
                count_bomb++; 
              // right
              if (y + 1 <= height && board[x][y+1] == -1)
                count_bomb++;
              // bottom left 
              if (x + 1 <= width && y - 1 >= 0 && board[x+1][y-1] == -1)
                  count_bomb++;
              // bottom 
              if (x + 1 <= width && board[x+1][y] == -1)
                  count_bomb++;
              // bottom right
              if (x + 1 <= width && y + 1 <= height && board[x+1][y+1] == -1)
                  count_bomb++;


              board[x][y] = count_bomb;


            }
    }
  }
}
// this function opens a file and writes the minesweeper into the file and applies the bomb 
// and the non-bombs
void save_file(int width, int height, int board[width][height]){
    char file_name[100];
    printf("What is the name of the file you would like to save to?\n");
    scanf("%s", file_name);
    
    FILE *file = fopen(file_name, "w");
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
              if (board[x][y] == -1) {
                fprintf(file, "X");
            } else if (board[x][y] == 0) {
                fprintf(file, "-");
            } else {
                fprintf(file, "%d", board[x][y]);
            }
        }
        fprintf(file, "\n");
    }
    fclose(file);
}
// this main function prints out the user questions and then creates the array with empty cells
int main(){
  int width, height;
  printf("What is the width of your board?\n");
  scanf("%d", &width);
  printf("What is the height of the board?\n");
  scanf("%d", &height);

  int board[width][height];
  for (int y = 0; y < height; y++) {
      for (int x = 0; x < width; x++) {
          board[x][y] = 0;
      }
  }
// runs all three functions
  load_bomb(width, height, board);

  set_hints(width, height, board); 

  save_file(width, height, board);
  return 0;
}
      
// less than 0 and greater equal than height/width
// -1 = x, 0 = - 
// check if current is bomb and then check 8 surrounding boxes ()