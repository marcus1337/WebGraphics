
miniBtnPanel = MiniButtonPanel:new{hasCancel = true, hasSettings = true}
elements = Elements:new{list = {miniBtnPanel}}
titleText = TitleText:new{textStr = "Game"}

chess = getChessRef()
chess:reset()
chess:print()
print("------------------")
from = Point:new(0,1)
to = Point:new(0,2)
chess:move(from, to)
chess:print()

function update()
    elements:update()
end

function render()
    elements:render()
    titleText:render()
end