
VolumeSlider = {}
VolumeSlider.__index = VolumeSlider

function VolumeSlider:updatePointer()
    self.slider:setValue(self.valueGetter())
end

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
    local sliderValue = o.valueGetter()
    o.slider = self:getSlider(sliderValue, o.onValueChange)
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
    if self.title == "Music Volume" and self.slider:isPressed() then
       queueMusic("sample", 1)
    end
    if self.title == "Effect Volume" and self.slider:isPressed() then
       queueEffect("boom1", 1)
    end
    if not isSoundMuted() then
        musicVolumeSlider.slider:setActive()
        effectVolumeSlider.slider:setActive()
    else
        musicVolumeSlider.slider:setInactive()
        effectVolumeSlider.slider:setInactive()
    end
    musicVolumeSlider:updatePointer()
    effectVolumeSlider:updatePointer()
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

titleText = TitleText:new{textStr = "Settings"}
miniBtnPanel = MiniButtonPanel:new{hasCancel = true, hasSound = true , hasScreen = true}
elements = Elements:new{list = {musicVolumeSlider, effectVolumeSlider, miniBtnPanel }}

function update()
    elements:update()
end

function render()
    backgroundImage:render()
    elements:render()
    titleText:render()
end

