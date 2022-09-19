MenuButton = {}
MenuButton.__index = MenuButton

function MenuButton:new(o)
    o = o or {}
    o.btn = Button.new(500,90)
    setmetatable(o, self)
    local btnText = o.btnText or "empty"
    local txt = Text(btnText)
    local y = o.y or 500
    txt:setPosition(0, 6)
    txt:setPixelHeight(46)
    txt:setFont("Roboto-Bold")
    txt:setColor(vec3(0.7,0.7,0.6))
    self.btn = o.btn
    self.btn:setText(txt)
    self.btn:setPosition(math.floor(1920/2 - 500/2), y)
    self.btn.onPressCallback = o.onPressCallback
    return o
end

function MenuButton:update()
    self.btn:update()
end

function MenuButton:render()
    self.btn:render()
end

function getMenuButton(name, onPress)
    local btn = Button.new(200, 80)
    btn:setPosition(80, 1010)
	local btnText = Text("empty")
	btnText:setPixelHeight(40)
	btnText:setColor(vec3(0.7,0.7,0.3))
	btn:setText(btnText)
	btn.onPressCallback = onPress
    return btn
end

function getExitButton()
    local btn = Button.new(miniBtnSize, miniBtnSize)
    btn:setPosition(20, 1010)
    btn:setImage("icons/cancel.png")
    btn.onPressCallback = onQuit
    return btn
end

