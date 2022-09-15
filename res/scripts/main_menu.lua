
miniBtnSize = 50

function getExitButton()
    local btn = Button.new(miniBtnSize, miniBtnSize)
    btn:setPosition(20, 1010)
    btn:setImage("icons/cancel.png")
    btn.onPressCallback = onQuit
    return btn
end

function getSettingsButton()
    local btn = Button.new(miniBtnSize, miniBtnSize)
    btn:setPosition(80, 1010)
    btn:setImage("icons/settings.png")
    btn.onPressCallback = onSettings
    return btn
end

exitButton = getExitButton()
settingsButton = getSettingsButton()
backgroundImage = Image("background1.png")
backgroundImage:setTexture("background3.png")
backgroundImage:setPosition(0,0)
backgroundImage:setSize(1920,1080)

lobbyButton = Button.new(200, 80)
lobbyBtnText = Text("Lobby")
lobbyBtnText:setPixelHeight(40)
lobbyBtnText:setColor(vec3(0.7,0.7,0.3))
lobbyButton:setText(lobbyBtnText)
lobbyButton:setPosition(800, 600)
lobbyButton.onPressCallback = onLobby

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

test()
print("woah " .. tostring(testVariable))
