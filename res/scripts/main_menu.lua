

backgroundImage = getBackgroundImage("background3.png")

gameButton = MenuButton:new{btnText = "Game", onPressCallback = onGame, y = 600}
createLobbyButton = MenuButton:new{btnText = "Create Lobby", onPressCallback = onLobby, y = 500}
findLobbyButton = MenuButton:new{btnText = "Find Lobby", onPressCallback = onFindLobby, y = 400}
instructionsButton = MenuButton:new{btnText = "Instructions", onPressCallback = onInstructions, y = 300}
exitButton = MenuButton:new{btnText = "Exit", onPressCallback = onQuit, y = 200}
titleText = TitleText:new{textStr = "Menu"}

setUIElements{exitButton, getSettingsButton(), createLobbyButton, findLobbyButton, instructionsButton, gameButton}

function update()
    updateUIElements()
end

function render()
    backgroundImage:render()
    titleText:render()
    renderUIElements()
end


