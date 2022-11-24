Animator = {}

function Animator:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    self.started = false
    return o
end

function Animator:getAnimationTime(fromPoint, toPoint)
    local milliSecondsPerTileMove = 60
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
    local numFrames = 60.0 * (self.animationTime/1000.0)
    local xDelta = (xTo - xFrom)/numFrames
    local frame = math.floor(self.unitInterval * numFrames)
    local xNow = xDelta * frame + xFrom
    return math.floor(xNow)
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
    self.unitInterval = self:getUnitInterval()
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
