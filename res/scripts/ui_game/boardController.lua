BoardController = {}
function BoardController:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self

    o.from = nil

    return o
end

function BoardController:setFrom(from)
    self.from = from
end

function BoardController:setTo(to)
    local chess = getChessRef()
    chess:move(self.from, to)
    self.from = nil
end

function BoardController:isFromSelect()
    return self.from == nil
end

function BoardController:isToSelect()
    return self:isFromSelect() == false
end