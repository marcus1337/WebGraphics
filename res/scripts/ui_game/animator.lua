Animator = {}

function Animator:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self

    return o
end

function Animator:getAnimationTime(fromPoint, toPoint)
    local milliSecondsPerTileMove = 1000
    local xDelta = math.abs(fromPoint.file - toPoint.file)
    local yDelta = math.abs(fromPoint.rank - toPoint.rank)
    local distance = math.sqrt(xDelta * xDelta + yDelta * yDelta)
    local timeMilliSeconds = distance * milliSecondsPerTileMove
    return timeMilliSeconds
end

function Animator:setPointsAndPiece(fromPoint, toPoint, piece)
    self.fromPoint = fromPoint
    self.toPoint = toPoint
    self.piece = piece
    self.animationTime = self:getAnimationTime(self.fromPoint, self.toPoint)
end

function Animator:start()
    self.timer = Timer()
end
