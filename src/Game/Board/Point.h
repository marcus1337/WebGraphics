
#ifndef POINT_H
#define POINT_H

struct Point {
    int file, rank;

    Point operator+(const Point& first) {
        return Point{ file + first.file, rank + first.rank };
    }
};

#endif
