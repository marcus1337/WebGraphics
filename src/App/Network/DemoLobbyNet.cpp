
#include "DemoLobbyNet.h"

std::vector<NetID<int>> DemoLobbyNet::getOpenLobbies() {
    std::vector<NetID<int>> lobbies;

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

bool DemoLobbyNet::areAllReady() {

    return false;
}

void DemoLobbyNet::startGame() {

}

std::string DemoLobbyNet::getUsername(NetID<int> _ID) {

    return "username123";
}

