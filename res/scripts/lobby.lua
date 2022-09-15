
titleText = TitleText:new{textStr = "Lobby"}

uiElements = {getCancelButton(), getSettingsButton()}

function update()
    for k, v in pairs(uiElements) do 
        v:update()
    end
end

function render()
    for k, v in pairs(uiElements) do 
        v:render()
    end
    titleText:render()
end
