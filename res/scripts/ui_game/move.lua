Mover = {}

function Mover:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    o.fromPoint = nil
    o.toPoint = nil
    o.promoteType = nil
    return o
end

function Mover:clear()
    self.fromPoint = nil
    self.toPoint = nil
    self.promoteType = nil
end

function Mover:isWaitingToSetPromotePiece()
    return self.fromPoint ~= nil and self.toPoint ~= nil and getChessRef():isPromoteMove(self.fromPoint, self.toPoint)
end

function Mover:isReadyToPromote()
    return self.fromPoint ~= nil and self.toPoint ~= nil and self.promoteType ~= nil
end

function Mover:isReady()
    return (not self:isWaitingToSetPromotePiece() and self.fromPoint ~= nil and self.toPoint ~= nil) or self:isReadyToPromote()
end

function Mover:move()
    local chess = getChessRef()
    if self:isReadyToPromote() then
        chess:promote(self.fromPoint, self.toPoint, self.promoteType)
    else
        chess:move(self.fromPoint, self.toPoint)
    end
    self:clear()
end

function Mover:prepare(fromPoint, toPoint)
    self.fromPoint = fromPoint
    self.toPoint = toPoint
end

function Mover:setPromoteType(promoteType)
    self.promoteType = promoteType
end

function Mover:getMove()
    local chess = getChessRef()
    return chess:getMove(self.fromPoint, self.toPoint)
end



