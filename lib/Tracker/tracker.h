#ifndef TRACKER_H_
#define TRACKER_H_
#include <Common.h>
#include <Tile.h>

class Tracker {
public:
    int createMaze(int rows, int collums);
    int tileMove();

    // The three exploration functions
    void explore();
    void record();
    void pathFind(int location);


    // placeTile(Tile obj);
private:
    // int start;
};

#endif