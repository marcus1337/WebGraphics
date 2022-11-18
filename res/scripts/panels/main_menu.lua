

backgroundImage = getBackgroundImage("background3.png")

gameButton = MenuButton:new{btnText = "Player vs Player", onPressCallback = onGame, y = 570}
exitButton = MenuButton:new{btnText = "Exit", onPressCallback = onQuit, y = 250}
titleText = TitleText:new{textStr = "Main Menu"}

elements = Elements:new{list = {exitButton, gameButton, MiniButtonPanel:new{hasSettings = true}}}

function update()
    elements:update()
end

function render()
    backgroundImage:render()
    titleText:render()
    elements:render()
end


