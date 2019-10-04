#include <Tracker.h>

int Tracker::createMaze(int rows, int collums) {
  int maze[rows][collums];
  for(int i = 0; i < rows; i++) {
        for(int j = 0; j < collums; j++) {
          Serial.printf("%d,%d", i, j);
          if(j < 10 && i < 10) {
              Serial.print("   |  ");
          }
          else if(i < 10 || j < 10) {
            Serial.print("  |  ");
          }
          else {
              Serial.print(" |  ");
          }
        }
        Serial.println();
    }
    return maze[rows][collums];
}

// int start = maze[round((mSize/2))][round((mSize/2))];