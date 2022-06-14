
#include "LobbyNet.h"

#ifndef DEMOLOBBYNET_H
#define DEMOLOBBYNET_H

class DemoLobbyNet : public LobbyNet<int> {

public:

    virtual void update();

    //Functions for finding lobbies
    virtual std::vector<NetID<int>> getOpenLobbies();
    virtual void joinLobby(NetID<int> lobbyID);
    virtual void createLobby();
    virtual bool setInviteLobbyID();

    //Functions to use after joining or creating a lobby
    virtual bool isInLobby();
    virtual NetID<int> getLobbyHost();
    virtual void leaveLobby();
    virtual void setReady(bool _ready);
    virtual bool areAllReady();
    virtual void startGame();
    virtual std::string getUsername(NetID<int> _ID);

};

#endif // !DEMOLOBBYNET_H
