
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

function onSoundButtonClick()
    if isSoundMuted() then
        unmuteSound()
    else
        muteSound()
    end
    soundButton:setImage(getSoundButtonImageStr())
end

VolumeSlider = {}
VolumeSlider.__index = VolumeSlider

function VolumeSlider:getSlider(value, onValueChange)
    local slider = Slider(500, 30)
    slider:setBoxColor(vec3(0.7,0.7,0.7))
    slider:setLineColor(vec3(0.5,0.5,0.5))
    slider:setBackgroundColor(vec3(0.6,0.5,0.6))
    slider:setBackgroundAlpha(0.7)
    slider.onValueChangeCallback = onValueChange
    slider:setValue(value)
    return slider
end

function VolumeSlider:new(o)
    o = o or {}
    o.x = o.x or 0
    o.y = o.y or 0
    setmetatable(o, self)
    o.slider = self:getSlider(o.valueGetter(), o.onValueChange)
    o.slider:setPosition(o.x, o.y)
    return o
end

function VolumeSlider:getVolumeText()
    local value = self.valueGetter() * 100.0
    local valueStr = string.format("%.1f%%", value)
    local txt = Text(valueStr)
    txt:setPixelHeight(40)
    txt:setColor(vec3(0.8,0.8,0.8))
    return txt
end

function VolumeSlider:update()
    self.slider:update()
end

function VolumeSlider:render()
    self.slider:render()
    local volumePercentageText = self:getVolumeText()
    volumePercentageText:setPosition(self.slider:getX() + self.slider:getWidth() + 10, self.slider:getY())
    volumePercentageText:render()

    local titleText = Text(self.title or "")
    titleText:setPosition(self.slider:getX() + math.floor(self.slider:getWidth()/2 - titleText:getPixelWidth()/4), self.slider:getY() + 50)
    titleText:setPixelHeight(36)
    titleText:setColor(vec3(0.8,0.8,0.8))
    titleText:render()
end

backgroundImage = getBackgroundImage("background2.png")
musicVolumeSlider = VolumeSlider:new{valueGetter = getMusicVolume, onValueChange = setMusicVolume, x = 700, y = 550, title = "Music Volume"}
effectVolumeSlider = VolumeSlider:new{valueGetter = getEffectVolume, onValueChange = setEffectVolume, x = 700, y = 400, title = "Effect Volume"}

soundButton = getSoundButton()
fullScreenButton = getFullScreenButton()
titleText = TitleText:new{textStr = "Settings"}
setUIElements{getCancelButton(), fullScreenButton, soundButton, musicVolumeSlider, effectVolumeSlider}

function update()
    updateUIElements()
end

function render()
    backgroundImage:render()
    renderUIElements()
    titleText:render()
end

