
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
    btn.onPressCallback = onSettings
    return btn
end

exitButton = getExitButton()
settingsButton = getSettingsButton()
backgroundImage = Image("background1.png")
backgroundImage:setTexture("background3.png")
backgroundImage:setPosition(0,0)
backgroundImage:setSize(1920,1080)
slider = Slider(250, 30)
slider.onValueChangeCallback = sliderFunction
slider:setPosition(200,200)
slider:setBoxColor(vec3(0.2,0.0,0.0))
slider:setLineColor(vec3(0.3,0.4,0.3))
slider:setBackgroundColor(vec3(0.7,0.3,0.5))
slider:setBackgroundAlpha(0.6)

function sliderFunction(value)
    print("slider value: " .. value)
end

function update()
    exitButton:update()
    settingsButton:update()
    slider:update()
end

function render()
    backgroundImage:render()
    exitButton:render()
    settingsButton:render()
    slider:render()
end

