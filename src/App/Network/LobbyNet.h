
#include "NetID.h"
#include <vector>
#include <string>

#ifndef LOBBYNET_H
#define LOBBYNET_H

template <class T>
class LobbyNet {

    NetID<T> userID;
    NetID<T> inviteLobbyID;

public:
    // update lobby parameters
    virtual void update() = 0;

    //Functions for finding lobbies
    virtual std::vector<NetID<T>> getOpenLobbies() = 0;
    virtual void joinLobby(NetID<T> lobbyID) = 0;
    virtual void createLobby() = 0;
    virtual bool setInviteLobbyID() = 0;

    //Functions to use after joining or creating a lobby
    virtual bool isInLobby() = 0;
    virtual NetID<T> getLobbyHost() = 0;
    virtual void leaveLobby() = 0;
    virtual void setReady(bool _ready) = 0;
    virtual bool areAllReady() = 0;
    virtual void startGame() = 0;
    virtual std::string getUsername(NetID<T> _ID) = 0;

    bool isHost() {
        return isInLobby() && getLobbyHost() == userID;
    }
    bool isHost(NetID<T> _ID) {
        return isInLobby() && getLobbyHost() == _ID;
    }
};


#endif // !LOBBY_H
