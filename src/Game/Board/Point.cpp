#include "Point.h"


void Point::closeDistance(Point to) {
    if (file < to.file)
        file++;
    else if (file > to.file)
        file--;
    if (rank < to.rank)
        rank++;
    else if (rank > to.rank)
        rank--;
}

bool Point::isInsideBoard() {
    return file >= 0 && file <= 7 && rank >= 0 && rank <= 7;
}

Point::Point() : file(0), rank(0) {

}
Point::Point(int _file, int _rank) : file(_file) , rank(_rank) {

}

std::string Point::toString() {
    return "{" + std::to_string(file) + "," + std::to_string(rank) + "}";
}
