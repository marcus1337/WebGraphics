TileState = {}
function TileState:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    self.clicked = false
    self.selected = false
    self.target = false
    return o
end



