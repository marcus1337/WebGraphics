
#include "LobbyNet.h"

#ifndef DEMOLOBBYNET_H
#define DEMOLOBBYNET_H

class DemoLobbyNet : public LobbyNet<int> {

public:

    DemoLobbyNet();

    virtual void update();
    virtual bool setInviteLobbyID();

    //Functions for finding lobbies
    virtual std::vector<NetID<int>> getOpenLobbies();
    virtual void joinLobby(NetID<int> lobbyID);
    virtual void createLobby();

    //Functions to use after joining or creating a lobby
    virtual bool isInLobby();
    virtual NetID<int> getLobbyHost();
    virtual void leaveLobby();
    virtual void setReady(bool _ready);
    virtual void startGame();
    virtual std::string getUsername(NetID<int> _ID);
    virtual std::vector<NetID<int>> getLobbyMembers();
    virtual bool isReady(NetID<int> _ID);

};

#endif // !DEMOLOBBYNET_H
