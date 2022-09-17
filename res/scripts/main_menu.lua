

backgroundImage = getBackgroundImage("background3.png")

lobbyButton = MenuButton:new{btnText = "Lobby", onPressCallback = onLobby, y = 600}
exitButton = MenuButton:new{btnText = "Exit", onPressCallback = onQuit, y = 400}
titleText = TitleText:new{textStr = "Menu"}

setUIElements{exitButton, getSettingsButton(), lobbyButton}

function update()
    updateUIElements()
end

function render()
    backgroundImage:render()
    titleText:render()
    renderUIElements()
end


