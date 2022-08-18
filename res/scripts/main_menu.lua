
img = nil
btn = nil
line = nil

function init()
    print('main_menu: init()')
    img = Image.new()
    btn = Button.new()
    line = Line.new(50,50, 100, 100)
    line:setColor(vec3(0.8,0.5,0.5))
    btn.onPressCallback = foo
end

function foo()
    print("foo function...")
end

function update()
    --print('main_menu: update()')
    img:setPosition(50,55)
    img:setSize(200,55)
    btn:update()
    line:setPosition(100, 800)
end

function render()
    --print('main_menu: render()')
    --img:render()
    --btn:render()
    line:render()
end

