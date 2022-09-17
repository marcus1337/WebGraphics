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

