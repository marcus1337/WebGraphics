#include <stdint.h>
#include "Board/Board.h"
#include "Board/Point.h"
#include "Board/Move.h"

#ifndef HISTORY_H
#define HISTORY_H

class History {

    std::vector<Move> moves;

public:

    void add(Move move);
    Move getLastMove();

};

#endif