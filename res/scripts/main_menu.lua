

backgroundImage = getBackgroundImage("background3.png")

lobbyButton = MenuButton:new{btnText = "Lobby", onPressCallback = onLobby, y = 700}
titleText = TitleText:new{textStr = "Menu"}

setUIElements{getExitButton(), getSettingsButton(), lobbyButton}

function update()
    updateUIElements()
end

function render()
    backgroundImage:render()
    titleText:render()
    renderUIElements()
end


