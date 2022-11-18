
VolumeSlider = {}
VolumeSlider.__index = VolumeSlider

function VolumeSlider:updatePointer()
    self.slider:setValue(self.valueGetter())
end

function VolumeSlider:getSlider(value, onValueChange)
    local slider = Slider(600, 30)
    slider:setBoxColor(vec3(0.5,0.5,0.5))
    slider:setLineColor(vec3(0.5,0.5,0.5))
    slider:setMarkedLineColor(vec3(0.5,0.5,0.5))
    slider:setBackgroundColor(vec3(0.2,0.2,0.2))
    slider:setBackgroundAlpha(1.0)
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

function VolumeSlider:update()
    self.slider:update()
    if self.title == "Music Volume" and self.slider:isPressed() then
       queueMusic("sample", 1)
    end
    if self.title == "Effect Volume" and self.slider:isPressed() then
       queueEffect("boom1", 1)
    end
    if not isSoundMuted() then
        effectVolumeSlider.slider:setActive()
    else
        effectVolumeSlider.slider:setInactive()
    end
    effectVolumeSlider:updatePointer()
end

function VolumeSlider:render()
    self.slider:render()
    local titleText = Text(self.title or "")
    titleText:setPosition(self.slider:getX() + math.floor(self.slider:getWidth()/2 - titleText:getPixelWidth()/4), self.slider:getY() + 50)
    titleText:setPixelHeight(36)
    titleText:setColor(vec3(0.8,0.8,0.8))
    titleText:render()
end

backgroundImage = getBackgroundImage("background2.png")
effectVolumeSlider = VolumeSlider:new{valueGetter = getEffectVolume, onValueChange = setEffectVolume, x = 650, y = 600, title = "Sound Volume"}

titleText = TitleText:new{textStr = "Settings"}
miniBtnPanel = MiniButtonPanel:new{hasCancel = true, hasSound = true , hasScreen = true}
elements = Elements:new{list = {effectVolumeSlider, miniBtnPanel }}



VolumePanel = {}

function VolumePanel:new(o)
    o = o or {}
    o.width = o.width or 800
    o.height = o.height or 500
    o.x = o.x or 0
    o.y = o.y or 0
    setmetatable(o, self)
    self.__index = self
    return o
end

function VolumePanel:render()
    local backRect = Rect()
    local radius = 0.15
    backRect:setPosition(self.x, self.y)
    backRect:setSize(self.width, self.height)
    backRect:setRadius(radius)
    backRect:setAlpha(0.95)
    backRect:setColor(vec3(0.15,0.1,0.1))
    backRect:render()

    local backRim = Rect()
    backRim:setPosition(self.x, self.y)
    backRim:setSize(self.width, self.height)
    backRim:setRadius(radius)
    backRim:setThickness(0.01)
    backRim:setAlpha(1.0)
    backRim:setColor(vec3(0.5,0.5,0.4))
    backRim:render()
end

local tmpWidth = 800
volumePanel = VolumePanel:new{x = math.floor(1920/2 - tmpWidth/2), y = 500, width = tmpWidth, height = 250}

function update()
    elements:update()
end

function render()
    backgroundImage:render()
    volumePanel:render()
    elements:render()
    titleText:render()
end

