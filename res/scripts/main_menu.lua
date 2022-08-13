
img = nil

function init()
    print('main_menu: init()')
    img = Image.new()
end

function update()
    --print('main_menu: update()')
    img:setPosition(50,55)
    img:setSize(200,55)
end

function render()
    --print('main_menu: render()')
    img:render()
end

