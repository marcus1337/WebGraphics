#include "EnPassant.h"

bool EnPassant::isPawnTwoStepped() {
    return twoSteppedPawn;
}

void EnPassant::setPawnTwoStepped(bool value) {
    twoSteppedPawn = value;
}

void EnPassant::setTwoSteppedPawnFile(int file) {
    pawnFile = file;
}

int EnPassant::getTwoSteppedPawnFile() {
    return pawnFile;
}

