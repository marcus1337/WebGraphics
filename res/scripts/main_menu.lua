
img = nil
btn = nil

function init()
    print('main_menu: init()')
    img = Image.new()
    btn = Button.new()
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
end

function render()
    --print('main_menu: render()')
    img:render()
    btn:render()
end

