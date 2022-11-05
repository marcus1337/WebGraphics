
miniBtnPanel = MiniButtonPanel:new{hasCancel = true, hasSettings = true}
elements = Elements:new{list = {miniBtnPanel}}

board = Board:new{}

function update()
    elements:update()
end

function render()
    elements:render()
    board:render()
end