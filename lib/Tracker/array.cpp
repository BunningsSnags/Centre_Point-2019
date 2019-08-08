#include <iostream>
#include <string>
#include <common.h>

int tracker[HEIGHT][WIDTH];
int a,b;

void printTracker(const in c[][HEIGHT]){
  for(int i = 0; i < WIDTH; i++){
    for(int j = 0; j < HEIGHT; j++){
      Serial.print(c[i][j]):
      Serial.print("\r")
    }
  }
}

int main (){
  for(a=0; a<HEIGHT; a++){
    for(b=0; b<WIDTH; b++){
        tracker[a][b]=0;
    }
  }
}

printTracker(tracker);