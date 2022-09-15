
exitButton = getExitButton()
settingsButton = getSettingsButton()
backgroundImage = getBackgroundImage("background3.png")

lobbyButton = getMenuButton("Lobby", onLobby)
lobbyButton:setPosition(800, 600)

function update()
    exitButton:update()
    settingsButton:update()
    lobbyButton:update()
end

function render()
    backgroundImage:render()
    exitButton:render()
    settingsButton:render()
    lobbyButton:render()
end


