
btn = nil
rect = nil

function toggleFullScreen()
    setFullScreen(not isFullScreen())
end

function updateFSButtonText()
    local str = "Full Screen"
    if isFullScreen() then 
        str = str .. " (on)"
    else
        str = str .. " (off)"
    end
    setButtonText(btn, str)
end

function getFSButton()
    local b = nil
    b = Button.new(300, 100)
    b:setPosition(1510, 760)
    b:setImage("background3.png")
    setButtonText(b, "empty...")
    b.onPressCallback = toggleFullScreen
    return b
end

function setButtonText(b, str)
    local txt = Text(str)
    txt:setPixelHeight(35)
    txt:setColor(vec3(0.9,0.9,0.9))
    b:setText(txt)
end

function init()
    print('main_menu: init()')
    btn = getFSButton()

    rect = Rect()
    rect:setSize(1520,900)
    rect:setColor(vec3(0.6,0.5,0.2))
    rect:setPosition(200,100)
    rect:setThickness(0.01)
end

function update()
    updateFSButtonText()
    btn:update()
end

function render()
    rect:render()
    btn:render()
end

