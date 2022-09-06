
function toggleFullScreen()
    setFullScreen(not isFullScreen())
end

function setFSButtonText(btn)
    local str = "Full Screen"
    if isFullScreen() then 
        str = str .. " (on)"
    else
        str = str .. " (off)"
    end
    setButtonText(btn, str)
end

function getFSButton()
    local btn = Button.new(300, 100)
    btn:setPosition(1600, 950)
    btn:setImage("background3.png")
    setFSButtonText(btn)
    btn.onPressCallback = toggleFullScreen
    return btn
end

function setButtonText(btn, str)
    local txt = Text(str)
    txt:setPixelHeight(35)
    txt:setColor(vec3(0.9,0.9,0.9))
    btn:setText(txt)
end

fsBtn = nil
rect = nil

function init()
    print('main_menu: init()')
    fsBtn = getFSButton()

    rect = Rect()
    rect:setSize(1520,880)
    rect:setColor(vec3(0.6,0.5,0.2))
    rect:setPosition(200,100)
    rect:setThickness(0.01)
    rect:setRadius(0.3)
end

function update()
    setFSButtonText(fsBtn)
    fsBtn:update()
end

function render()
    rect:render()
    fsBtn:render()
end

