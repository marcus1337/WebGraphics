
#ifndef NETID_H
#define NETID_H

template <class T>
class NetID {

    T ID;

public:

    NetID() : ID() {}
    NetID(T _ID) : ID(_ID) {}
    T getID() {
        return ID;
    }

    bool operator==(const NetID& otherID) {
        return ID == otherID.ID;
    }
};

#endif