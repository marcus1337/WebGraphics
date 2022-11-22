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

function Move:promote()
    if self.fromPoint == nil or self.toPoint == nil or self.promoteType == nil then
        print("promote(): nil error.")
    end
    local chess = getChessRef()
    chess:promote(self.fromPoint, self.toPoint, self.promoteType)
    self:clear()
end

function Move:isWaitingToPromote()
    return self.fromPoint ~= nil and self.toPoint ~= nil and getChessRef():isPromoteMove(self.fromPoint, self.toPoint)
end

function Move:prepare(fromPoint, toPoint)
    self.fromPoint = fromPoint
    self.toPoint = toPoint
end




