
miniBtnPanel = MiniButtonPanel:new{hasCancel = true, hasSettings = true}
elements = Elements:new{list = {miniBtnPanel}}


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
end

function render()
    elements:render()
    board:render()
    promoteView:render()
end