
btn = nil
circle = nil
rect = nil

function toggleFullScreen()
    setFullScreen(not isFullScreen())
end

function init()
    print('main_menu: init()')
    btn = Button.new()
    txt = Text("FullScreen?")
    txt:setPixelHeight(35)
    txt:setColor(vec3(0.9,0.9,0.9))
    btn:setPosition(1710, 960)
    btn:setImage("background3.png")
    btn:setText(txt)
    btn.onPressCallback = toggleFullScreen

    circle = Circle()

    rect = Rect()
    rect:setSize(1520,900)
    rect:setColor(vec3(0.6,0.5,0.2))
    rect:setPosition(200,100)
    rect:setThickness(0.01)
end


function update()
    btn:update()
    circle:setPosition(0,0)
    circle:setSize(200,200)
    circle:setColor(vec3(0.4,0.4,0.8))
    circle:setFade(0.01)
    circle:setThickness(0.75)
end

function render()
    btn:render()
    circle:render()
    rect:render()
end

