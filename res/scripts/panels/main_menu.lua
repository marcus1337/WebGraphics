

backgroundImage = getBackgroundImage("background3.png")

gameButton = MenuButton:new{btnText = "Game", onPressCallback = onGame, y = 600}
instructionsButton = MenuButton:new{btnText = "Instructions", onPressCallback = onInstructions, y = 400}
exitButton = MenuButton:new{btnText = "Exit", onPressCallback = onQuit, y = 200}
titleText = TitleText:new{textStr = "Menu"}

setUIElements{exitButton, createLobbyButton, findLobbyButton, instructionsButton, gameButton, MiniButtonPanel:new{hasSettings = true}}

function update()
    updateUIElements()
end

function render()
    backgroundImage:render()
    titleText:render()
    renderUIElements()
end


