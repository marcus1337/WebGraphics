miniBtnSize = 50

function getExitButton()
    local btn = Button.new(miniBtnSize, miniBtnSize)
    btn:setPosition(20, 1010)
    btn:setImage("icons/cancel.png")
    btn.onPressCallback = onCancel
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

function update()
    exitButton:update()
    settingsButton:update()
end

function render()
    exitButton:render()
    settingsButton:render()
end
