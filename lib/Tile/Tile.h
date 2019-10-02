#ifndef TILE_H_
#define TILE_H_

struct Tile {
    bool walls[4];
    enum wallDirection{north, east, south, west};
    bool hasThermal;
    int thermal;
    bool isBlack;
    bool isSilver;
};

#endif