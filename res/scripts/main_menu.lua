
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
    btn:setPosition(20 + miniBtnSize + 5, 1010)
    btn:setImage("icons/settings.png")
    return btn
end

exitButton = getExitButton()
settingsButton = getSettingsButton()
backgroundImage = Image("background1.png")
backgroundImage:setTexture("background3.png")
backgroundImage:setPosition(0,0)
backgroundImage:setSize(1920,1080)

function update()
    exitButton:update()
    settingsButton:update()
end

function render()
    backgroundImage:render()
    exitButton:render()
    settingsButton:render()
end

