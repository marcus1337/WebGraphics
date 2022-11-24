Animator = {}

function Animator:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    self.started = false
    return o
end

function Animator:getAnimationTime(fromPoint, toPoint)
    local milliSecondsPerTileMove = 90
    local distance = self:getPointDistance(fromPoint, toPoint)
    local timeMilliSeconds = distance * milliSecondsPerTileMove
    return timeMilliSeconds
end

function Animator:setValues(move)
    self.fromPoint = move:getFrom()
    self.toPoint = move:getTo()
    if self.toPoint.rank > 7 then
        self.toPoint.rank = 7
    end
    if self.toPoint.rank < 0 then
        self.toPoint.rank = 0
    end
    self.piece = move:getPiece()
    self.animationTime = math.floor(self:getAnimationTime(self.fromPoint, self.toPoint))
    self.move = move
end

function Animator:start(move)
    self.started = true
    self:setValues(move)
    self.board:stopRenderPiece(self.fromPoint)
    self.timer = Timer:new()
end

function Animator:isDone()
    local passedMilliseconds = self.timer:getPassedMilliseconds()
    return passedMilliseconds > self.animationTime
end

function Animator:onFinish()
    self.board:startRenderPiece(self.fromPoint)
    self.started = false
end

function Animator:getFromX()
    return self.board.x + self.fromPoint.file * self.board:getTileWidth()
end

function Animator:getToX()
    return self.board.x + self.toPoint.file * self.board:getTileWidth()
end

function Animator:getFromY()
    return self.board.y + self.fromPoint.rank * self.board:getTileWidth()
end

function Animator:getToY()
    return self.board.y + self.toPoint.rank * self.board:getTileWidth()
end

function Animator:getUnitInterval()
    local unitInterval = self.timer:getPassedMilliseconds() / self.animationTime
    return math.min(unitInterval, 1.0)
end

function Animator:getLerp(from, to)
    local t = self.unitInterval
    return from*(1-t) + t*to
end

function Animator:getXPos()
    local xFrom = self:getFromX()
    local xTo = self:getToX()
    local xNow = math.floor(self:getLerp(xFrom, xTo) + 0.5)
    return xNow
end

function Animator:getYPos()
    local yFrom = self:getFromY()
    local yTo = self:getToY()
    local yNow = math.floor(self:getLerp(yFrom, yTo) + 0.5)
    return yNow
end

function Animator:getPointDistance(fromPoint, toPoint)
    local xDelta = math.abs(fromPoint.file - toPoint.file)
    local yDelta = math.abs(fromPoint.rank - toPoint.rank)
    local distance = math.sqrt(xDelta * xDelta + yDelta * yDelta)
    return distance
end

function Animator:getPieceView()
    local distance = (self:getPointDistance(self.fromPoint, self.toPoint)*60.0/60.0) * self.board:getTileWidth()
    self.unitInterval = math.floor(self:getUnitInterval()*distance + 0.5)/distance
    --print(tostring(yNow) .. " " .. tostring(yFrom) .. " - " .. tostring(yTo) .. " " .. tostring(self:getLerp(yFrom, yTo) + 0.5))
    local piece = Piece:new({x = self:getXPos(), y = self:getYPos(), width = self.board:getTileWidth(), type = self.piece.type, color = self.piece.color})
    return piece
end

function Animator:isStarted()
    return self.started
end

function Animator:render()
    --print(tostring(self.animationTime) .. " " .. tostring(self.timer:getPassedMilliseconds() .. " " .. tostring(self:getUnitInterval())))
    self:getPieceView():render()
end
