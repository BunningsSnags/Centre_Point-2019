#include <Tracker.h>

int createMaze(int rows, int collums) {
  int maze[rows][collums];
  for(int i = 0; i < rows; i++) {
        for(int j = 0; j < collums; j++) {
          Serial.printf("%d, %d", i, j);
          Serial.print(" | ");
        }
        Serial.println();
    }
    return maze[rows][collums];
}