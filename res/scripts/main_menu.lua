

function getExitButton()
    local btn = Button.new(100, 100)
    btn:setPosition(1600, 950)
    btn:setImage("icons/cancel.png")
    --btn.onPressCallback = toggleFullScreen
    return btn
end

exitButton = getExitButton()
settingsButton = nil
rect = Rect()
rect:setSize(1520,880)
rect:setColor(vec3(0.6,0.5,0.2))
rect:setPosition(500,300)

function init()
    print('main_menu: init()')
end

function update()
    exitButton:update()
    --rect:update()
end

function render()
    rect:render()
    exitButton:render()
end

