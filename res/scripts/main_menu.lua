
img = nil
btn = nil
line = nil
circle = nil
rect = nil

function init()
    print('main_menu: init()')
    img = Image.new()
    btn = Button.new()
    --btn.setText("FullScreen?")
    line = Line.new(50,50, 100, 100)
    line:setColor(vec3(0.8,0.5,0.5))
    btn.onPressCallback = foo
    circle = Circle()
    rect = Rect()

    rect:setSize(600,300)
    rect:setColor(vec3(0.6,0.5,0.2))
    rect:setPosition(250,200)
    rect:setThickness(0.04)
end

function foo()
    setFullScreen(not isFullScreen())
end

function update()
    --print('main_menu: update()')
    img:setPosition(50,55)
    img:setSize(200,55)
    btn:update()
    line:setPosition(100, 800)
    circle:setPosition(200,200)
    circle:setSize(250,250)
    circle:setColor(vec3(0.4,0.4,0.8))
    circle:setFade(0.01)
    circle:setThickness(0.75)
end

function render()
    --print('main_menu: render()')
    --img:render()
    btn:render()
    --line:render()
    circle:render()
    rect:render()
end

