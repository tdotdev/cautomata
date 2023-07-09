#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

#include <unistd.h>

int randomBool();
void tick(bool**, bool**, int, int, int);
void initCells(bool[], int);
void printCells(bool[], char[], int, int);
int numNeigbors(bool[], int, int, int);

int main() {
  srand(time(NULL));
  const int width = 90;
  const int height = 50;
  const int length = height * width;

  //for (int i=0; i<width*height; i++)
  bool cells[length];
  bool buffer[length];
  char renderBuffer[length + height + 1];

  bool* cellsPtr = cells;
  bool* bufferPtr = buffer;

  initCells(cells, length);

  while (1) {
    //while (getchar() != '\n') {}
    printCells(cellsPtr, width, height);
    tick(&cellsPtr, &bufferPtr, length, width, height);
    usleep(1000000 / 30);
  }
}

int randomBool() {
  return (rand() % 4) == 0;
}

int numNeighbors(bool cells[], int width, int height, int index) {
    // Offsets for the 8 neighbors (up, down, left, right, and diagonals)
    int offsets[8][2] = {
      {-1, -1}, {0, -1}, {1, -1}, {-1, 0}, 
      {1, 0}, {-1, 1}, {0, 1}, {1, 1}
    };
    /* 

    */
    // Calculate the x, y position of the current element
    int x = index % width;
    int y = index / width;

    // Count the true neighbors
    int count = 0;
    for (int i = 0; i < 8; i++) {
        // Using modulo for wrapping around the grid
        int neighbor_x = (x + offsets[i][0] + width) % width;
        int neighbor_y = (y + offsets[i][1] + height) % height;
        int neighbor_index = neighbor_y * width + neighbor_x;
        if (cells[neighbor_index]) {
          count++;
        }
    }
    
    return count;
}

void tick(bool** cells, bool** buffer, int length, int width, int height) {
  int count;
  bool currentState;
  bool nextState;
  for (int i = 0; i < length; i++) {
    count = numNeighbors(*cells, width, height, i);
    currentState = (*cells)[i];
    nextState = currentState;
    if(currentState == true) {
      if (count < 2) {
        nextState = false;
      } else if (count > 3) {
        nextState = false;
      }
    } else {
      if (count == 3) {
        nextState = true;
      }
    }
    (*buffer)[i] = nextState;
  }

  bool* temp = *cells;
  *cells = *buffer;
  *buffer = temp;
}

void initCells(bool cells[], int size) {
  for (int i = 0; i < size; i++) {
    cells[i] = randomBool();
  }
}

#define BLACK "\x1B[30m"
#define YELLOW  "\x1B[33m"
#define BLUE    "\x1B[34m"
#define MAGENTA "\x1B[35m"
#define CYAN    "\x1B[36m"
#define WHITE   "\x1B[37m"
#define RED   "\x1B[31m"
#define GREEN "\x1B[32m"
#define RESET "\x1B[0m"

void printCells(bool cells[], char renderBuffer[], int width, int height) {

  //for (int i=0; i<width*height; i++)
  
  int index;
  bool cell;
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      index = (i * width) + j;
      cell = cells[index];
      if (cell==true) {
        printf("%s█%s", BLUE, RESET);
      } else {
        printf("%s█%s", BLACK, RESET);
      }
    }
    printf("\n");
  }
  printf("\n\n");
}

