
titleText = TitleText:new{textStr = "Lobby"}

setUIElements{getCancelButton(), getSettingsButton()}

function update()
    updateUIElements()
end

function render()
    renderUIElements()
    titleText:render()
end
