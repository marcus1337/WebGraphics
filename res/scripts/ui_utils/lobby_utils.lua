TitleText = {textStr = "empty"}
function TitleText:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    self.text = Text(o.textStr)
    self.text:setColor(vec3(0.7,0.7,0.6))
    self.text:setFont("Roboto-Bold")
    self.text:setPixelHeight(75)
    self.text:setPosition(math.floor(1920/2 - self.text:getPixelWidth()/2), 900)
    return o
end

function TitleText:render()
    self.text:render()
end