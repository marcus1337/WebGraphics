miniBtnSize = 50

MiniButtonPanel = {}
MiniButtonPanel.__index = MiniButtonPanel

function MiniButtonPanel:new(o)
    o = o or {}
    setmetatable(o, self)
    o.buttons = {}
    if o.hasCancel then
        o:addButton(getCancelButton())
    end
    if o.hasSettings then
        o:addButton(getSettingsButton())
    end
    if o.hasSound then
        local btn = getSoundButton()
        btn.onPressCallback = function() 
            o:soundClick()
        end
        o.soundButton = btn
        o:addButton(btn)
    end
    if o.hasScreen then
        o:addButton(getFullScreenButton())
    end
    return o
end

function MiniButtonPanel:addButton(btn)
    local btnIndex = #self.buttons
    btn:setPosition(btnIndex*60 + 20, 1010)
    self.buttons[btnIndex+1] = btn
end

function MiniButtonPanel:soundClick()
    if isSoundMuted() then
        unmuteSound()
    else
        muteSound()
    end
    self.soundButton:setImage(getSoundButtonImageStr())
end

function MiniButtonPanel:update()
    for k, v in pairs(self.buttons) do 
        v:update()
    end
end

function MiniButtonPanel:render()
    for k, v in pairs(self.buttons) do 
        v:render()
    end
end

function getCancelButton()
    local btn = Button.new(miniBtnSize, miniBtnSize)
    btn:setPosition(20, 1010)
    btn:setImage("icons/cancel.png")
    btn.onPressCallback = onCancel
    return btn
end

function getSettingsButton()
    local btn = Button.new(miniBtnSize, miniBtnSize)
    btn:setPosition(80, 1010)
    btn:setImage("icons/settings.png")
    btn.onPressCallback = onSettings
    return btn
end

function getFullScreenButton()
    local btn = Button.new(miniBtnSize, miniBtnSize)
    btn:setPosition(140, 1010)
    btn:setImage(getScreenButtonImageStr())
    btn.onPressCallback = onScreenButtonClick
    return btn
end

function getSoundButton()
    local btn = Button.new(miniBtnSize, miniBtnSize)
    btn:setPosition(80, 1010)
    btn:setImage(getSoundButtonImageStr())
    btn.onPressCallback = onSoundButtonClick
    return btn
end

function getScreenButtonImageStr()
    if isFullScreen() then
        return "icons/retract.png"
    else
        return "icons/expand.png"
    end
end

function getSoundButtonImageStr()
    if isSoundMuted() then
        return "icons/soundr.png"
    else
        return "icons/sound.png"
    end
end

function onScreenButtonClick()
    setFullScreen(not isFullScreen())
    fullScreenButton:setImage(getScreenButtonImageStr())
end

