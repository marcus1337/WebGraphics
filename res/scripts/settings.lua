
miniBtnSize = 50

function getCancelButton()
    local btn = Button.new(miniBtnSize, miniBtnSize)
    btn:setPosition(20, 1010)
    btn:setImage("icons/cancel.png")
    btn.onPressCallback = onCancel
    return btn
end

function getSoundButton()
    local btn = Button.new(miniBtnSize, miniBtnSize)
    btn:setPosition(80, 1010)
    btn:setImage(getSoundButtonImageStr())
    btn.onPressCallback = onSoundButtonClick
    return btn
end

function getSoundButtonImageStr()
    if isSoundMuted() then
        return "icons/soundr.png"
    else
        return "icons/sound.png"
    end
end

function onSoundButtonClick()
    if isSoundMuted() then
        unmuteSound()
    else
        muteSound()
    end
    soundButton:setImage(getSoundButtonImageStr())
end

function getVolumeSlider()
    local slider = Slider(500, 30)
    slider:setBoxColor(vec3(0.7,0.7,0.7))
    slider:setLineColor(vec3(0.5,0.5,0.5))
    slider:setBackgroundColor(vec3(0.6,0.5,0.6))
    slider:setBackgroundAlpha(0.7)
    return slider
end

cancelButton = getCancelButton()
soundButton = getSoundButton()
backgroundImage = Image("background2.png")
backgroundImage:setPosition(0,0)
backgroundImage:setSize(1920,1080)

musicVolumeSlider = getVolumeSlider()
musicVolumeSlider.onValueChangeCallback = musicVolumeChange
musicVolumeSlider:setPosition(600,700)
musicVolumeSlider:setValue(getMusicVolume())

effectVolumeSlider = getVolumeSlider()
effectVolumeSlider.onValueChangeCallback = effectVolumeChange
effectVolumeSlider:setPosition(600,550)
effectVolumeSlider:setValue(getEffectVolume())

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
end

function render()
    backgroundImage:render()
    cancelButton:render()
    soundButton:render()
    musicVolumeSlider:render()
    effectVolumeSlider:render()
    musicVolumeText:render()
    effectVolumeText:render()

    local effectVolumePercentageText = getVolumeText(getEffectVolume())
    effectVolumePercentageText:setPosition(1130, 550)
    effectVolumePercentageText:render()

    local musicVolumePercentageText = getVolumeText(getMusicVolume())
    musicVolumePercentageText:setPosition(1130, 700)
    musicVolumePercentageText:render()
end

