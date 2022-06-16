
#include "DemoLobbyNet.h"

DemoLobbyNet::DemoLobbyNet() {

}

std::vector<NetID<int>> DemoLobbyNet::getOpenLobbies() {
    std::vector<NetID<int>> lobbies;

    lobbies.push_back(NetID<int>(1));
    lobbies.push_back(NetID<int>(2));
    lobbies.push_back(NetID<int>(3));

    return lobbies;
}

void DemoLobbyNet::joinLobby(NetID<int> lobbyID) {

}

void DemoLobbyNet::createLobby() {

}

bool DemoLobbyNet::setInviteLobbyID() {

    return false;
}

bool DemoLobbyNet::isInLobby() {

    return false;
}

NetID<int> DemoLobbyNet::getLobbyHost() {

    return NetID<int>(0);
}

void DemoLobbyNet::leaveLobby() {

}

void DemoLobbyNet::setReady(bool _ready) {

}

void DemoLobbyNet::startGame() {

}

std::string DemoLobbyNet::getUsername(NetID<int> _ID) {

    return "username123";
}

void DemoLobbyNet::update() {

}

std::vector<NetID<int>> DemoLobbyNet::getLobbyMembers() {
    return { userID };
}

bool DemoLobbyNet::isReady(NetID<int> _ID) {
    return true;
}