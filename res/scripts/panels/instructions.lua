
titleText = TitleText:new { textStr = "Instructions" }

miniBtnPanel = MiniButtonPanel:new{hasCancel = true}
elements = Elements:new{list = {miniBtnPanel} }

function update()
    elements:update()
end

function render()
    titleText:render()
    elements:render()
end