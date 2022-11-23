Move = {}

function Move:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    o.fromPoint = nil
    o.toPoint = nil
    o.promoteType = nil
    return o
end

function Move:clear()
    self.fromPoint = nil
    self.toPoint = nil
    self.promoteType = nil
end

function Move:isWaitingToSetPromotePiece()
    return self.fromPoint ~= nil and self.toPoint ~= nil and getChessRef():isPromoteMove(self.fromPoint, self.toPoint)
end

function Move:isReadyToPromote()
    return self.fromPoint ~= nil and self.toPoint ~= nil and self.promoteType ~= nil
end

function Move:isReady()
    return (not self:isWaitingToSetPromotePiece() and self.fromPoint ~= nil and self.toPoint ~= nil) or self:isReadyToPromote()
end

function Move:apply()
    local chess = getChessRef()
    if self:isReadyToPromote() then
        chess:promote(self.fromPoint, self.toPoint, self.promoteType)
    else
        chess:move(self.fromPoint, self.toPoint)
    end
    self:clear()
end

function Move:prepare(fromPoint, toPoint)
    self.fromPoint = fromPoint
    self.toPoint = toPoint
end

function Move:setPromoteType(promoteType)
    self.promoteType = promoteType
end




