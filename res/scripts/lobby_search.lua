
titleText = TitleText:new { textStr = "Lobby Search" }
setUIElements({MiniButtonPanel:new{hasCancel = true}})

function update()
    updateUIElements()
end

function render()
    titleText:render()
    renderUIElements()
end