
titleText = TitleText:new { textStr = "Instructions" }
setUIElements({MiniButtonPanel:new{hasCancel = true}})

function update()
    updateUIElements()
end

function render()
    titleText:render()
    renderUIElements()
end