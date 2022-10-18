
miniBtnPanel = MiniButtonPanel:new{hasCancel = true, hasSettings = true}
elements = Elements:new{list = {miniBtnPanel}}
titleText = TitleText:new{textStr = "Game"}

function update()
    elements:update()
end

function render()
    elements:render()
    titleText:render()
end