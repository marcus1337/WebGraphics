miniBtnSize = 50

function getExitButton()
    local btn = Button.new(miniBtnSize, miniBtnSize)
    btn:setPosition(20, 1010)
    btn:setImage("icons/cancel.png")
    btn.onPressCallback = onQuit
    return btn
end

function getCancelButton()
    local btn = getExitButton()
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

function getMenuButton(name, onPress)
    local btn = Button.new(200, 80)
    btn:setPosition(80, 1010)
	local btnText = Text("Lobby")
	btnText:setPixelHeight(40)
	btnText:setColor(vec3(0.7,0.7,0.3))
	btn:setText(btnText)
	btn.onPressCallback = onPress
    return btn
end

function getBackgroundImage(name)
	local image = Image(name)
	image:setPosition(0,0)
	image:setSize(1920,1080)
	return image
end

uiElements = {}
function setUIElements(elements)
    uiElements = elements
end
function updateUIElements()
    for k, v in pairs(uiElements) do 
        v:update()
    end
end
function renderUIElements()
    for k, v in pairs(uiElements) do 
        v:render()
    end
end

TitleText = {textStr = "empty"}
function TitleText:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    self.text = Text(o.textStr)
    self.text:setColor(vec3(0.7,0.7,0.6))
    self.text:setFont("Roboto-Bold")
    self.text:setPixelHeight(75)
    self.text:setPosition(math.floor(1920/2 - self.text:getPixelWidth()/2), 900)
    return o
end

function TitleText:render()
    self.text:render()
end