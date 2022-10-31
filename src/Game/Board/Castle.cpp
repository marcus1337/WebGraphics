#include "Castle.h"

bool Castle::isKingMoved() {
    return kingMoved;
}
bool Castle::isQueenSideRookMoved() {
    return queenSideRookMoved;
}
bool Castle::isKingSideRookMoved() {
    return kingSideRookMoved;
}
void Castle::setKingMoved() {
    kingMoved = true;
}
void Castle::setKingSideRookMoved() {
    kingSideRookMoved = true;
}
void Castle::setQueenSideRookMoved() {
    queenSideRookMoved = true;
}