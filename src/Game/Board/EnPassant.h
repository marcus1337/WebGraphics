
#ifndef EN_PASSANT_H
#define EN_PASSANT_H

class EnPassant {

    bool twoSteppedPawn = false;
    int pawnFile = -1;

public:

    bool isPawnTwoStepped();
    void setPawnTwoStepped(bool value);
    void setTwoSteppedPawnFile(int file);
    int getTwoSteppedPawnFile();
};

#endif