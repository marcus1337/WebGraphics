
miniBtnPanel = MiniButtonPanel:new{hasCancel = true, hasSettings = true}
elements = Elements:new{list = {miniBtnPanel}}

local mover = Mover:new()
local board = Board:new{mover = mover}
local animator = Animator:new{board = board}

local promoteWidth = 115 * 4
local promoteXPosition = math.floor(board.x + board.width / 2.0 - promoteWidth / 2.0)
local promoteYPosition = math.floor (board.y + 115 * 8 + 10.0) 
local promoteView = PromoteView:new{x = promoteXPosition, y = promoteYPosition, width = promoteWidth, mover = mover}

function update()
    elements:update()
    if not animator:isStarted() then
        board:update()
    end
    promoteView:update()
    if (mover:isReady() or mover:isWaitingToSetPromotePiece()) and not animator:isStarted() then
        animator:start(mover:getMove())
    end

    if not mover:isReady() and not mover:isWaitingToSetPromotePiece() and animator:isStarted() then
        animator:onFinish()
    end

    if mover:isReady() and animator:isDone() then
        animator:onFinish()
        mover:applyMove()
    end
end

function render()
    elements:render()
    board:render()
    if animator:isStarted() then
        animator:render()
    end
    promoteView:render()
end