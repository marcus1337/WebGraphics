Mover = {}

function Mover:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    o.move = nil
    return o
end

function Mover:clear()
    self.move = nil
end

function Mover:isWaitingToSetPromotePiece()
    return self.move ~= nil and self.move:isPromote() and not self.move:isPromoteTypeSet()
end

function Mover:isReady()
    return self.move ~= nil and self.move:isReady()
end

function Mover:applyMove()
    local chess = getChessRef()
    chess:move(self.move:getFrom(), self.move:getTo())
    self:clear()
end

function Mover:prepare(fromPoint, toPoint)
    self.move = getChessRef():getMove(fromPoint, toPoint)
end

function Mover:setPromoteType(promoteType)
    self.move:setPromoteType(promoteType)
end

function Mover:getMove()
    return self.move
end



