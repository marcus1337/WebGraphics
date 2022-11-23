
miniBtnPanel = MiniButtonPanel:new{hasCancel = true, hasSettings = true}
elements = Elements:new{list = {miniBtnPanel}}

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


local move = Move:new()
local board = Board:new{move = move}

local promoteWidth = 115 * 4
local promoteXPosition = math.floor(board.x + board.width / 2.0 - promoteWidth / 2.0)
local promoteYPosition = math.floor (board.y + 115 * 8 + 10.0) 
local promoteView = PromoteView:new{x = promoteXPosition, y = promoteYPosition, width = promoteWidth, move = move}

function update()
    elements:update()
    board:update()
    promoteView:update()
    if move:isReady() then
        move:apply()
    end
end

function render()
    elements:render()
    board:render()
    promoteView:render()
end