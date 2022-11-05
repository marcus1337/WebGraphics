
#ifndef POINT_H
#define POINT_H

struct Point {
    int file, rank;

    Point();
    Point(int _file, int _rank);

    Point operator+(const Point& first) {
        return Point{ file + first.file, rank + first.rank };
    }
    Point operator-(const Point& first) {
        return Point{ file - first.file, rank - first.rank };
    }

    bool operator==(Point const& rhs) const { return file == rhs.file && rank == rhs.rank; }

    void closeDistance(Point to);
    bool isInsideBoard();

};

#endif
