
miniBtnPanel = MiniButtonPanel:new{hasCancel = true, hasSettings = true}
elements = Elements:new{list = {miniBtnPanel}}

local mover = Mover:new()
local board = Board:new{mover = mover}

local promoteWidth = 115 * 4
local promoteXPosition = math.floor(board.x + board.width / 2.0 - promoteWidth / 2.0)
local promoteYPosition = math.floor (board.y + 115 * 8 + 10.0) 
local promoteView = PromoteView:new{x = promoteXPosition, y = promoteYPosition, width = promoteWidth, mover = mover}

function update()
    elements:update()
    board:update()
    promoteView:update()
    if mover:isReady() then
        mover:move()
    end
end

function render()
    elements:render()
    board:render()
    promoteView:render()
end