
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

function getVolumeSlider(value, onValueChange)
    local slider = Slider(500, 30)
    slider:setBoxColor(vec3(0.7,0.7,0.7))
    slider:setLineColor(vec3(0.5,0.5,0.5))
    slider:setBackgroundColor(vec3(0.6,0.5,0.6))
    slider:setBackgroundAlpha(0.7)
    slider.onValueChangeCallback = onValueChange
    slider:setValue(value)
    return slider
end

fullScreenButton = getFullScreenButton()
cancelButton = getCancelButton()
soundButton = getSoundButton()
backgroundImage = getBackgroundImage("background2.png")

musicVolumeSlider = getVolumeSlider(getMusicVolume(), musicVolumeChange)
musicVolumeSlider:setPosition(600,700)
effectVolumeSlider = getVolumeSlider(getEffectVolume(), effectVolumeChange)
effectVolumeSlider:setPosition(600,550)

musicVolumeText = Text("Music Volume")
musicVolumeText:setPosition(740, 750)
musicVolumeText:setPixelHeight(36)
musicVolumeText:setColor(vec3(0.8,0.8,0.8))

effectVolumeText = Text("Effect Volume")
effectVolumeText:setPosition(740, 605)
effectVolumeText:setPixelHeight(36)
effectVolumeText:setColor(vec3(0.8,0.8,0.8))

function getVolumeText(value)
    value = value * 100.0
    local valueStr = string.format("%.1f%%", value)
    local txt = Text(valueStr)
    txt:setPixelHeight(40)
    txt:setColor(vec3(0.8,0.8,0.8))
    return txt
end

function musicVolumeChange(value)
    setMusicVolume(value)
end
function effectVolumeChange(value)
    setEffectVolume(value)
end

function update()
    cancelButton:update()
    soundButton:update()
    musicVolumeSlider:update()
    effectVolumeSlider:update()
    fullScreenButton:update()
end

function render()
    backgroundImage:render()
    cancelButton:render()
    soundButton:render()
    musicVolumeSlider:render()
    effectVolumeSlider:render()
    musicVolumeText:render()
    effectVolumeText:render()
    fullScreenButton:render()

    local effectVolumePercentageText = getVolumeText(getEffectVolume())
    effectVolumePercentageText:setPosition(1130, 550)
    effectVolumePercentageText:render()

    local musicVolumePercentageText = getVolumeText(getMusicVolume())
    musicVolumePercentageText:setPosition(1130, 700)
    musicVolumePercentageText:render()
end

