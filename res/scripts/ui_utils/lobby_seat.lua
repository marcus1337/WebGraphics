SimpleButton = {x = 0, y = 0, width = 700, height = 150, button = Button(200,100)}

function SimpleButton:update()
    self.button:update()
end
function SimpleButton:paintView()
end
function SimpleButton:render()
    local button = self.button
    button:setPosition(self.x, self.y)
    button:render()
end

Seat = SimpleButton

function Seat:getTeamBackgroundColor(team)
    if team == 2 then
        return vec3(0.05, 0.35, 0.55)
    else
        return vec3(0.55, 0.35, 0.05)
    end
end

function Seat:getTeamBackground2Color(team)
    if team == 2 then
        return vec3(0.15, 0.15, 0.25)
    else
        return vec3(0.25, 0.15, 0.15)
    end
end

function Seat:onPress()
    print("Seat pressed")
end

function Seat:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    o.team = o.team or 1
    o.role = o.role or "???"

    o:setViewComponents()
    o.button = Button.new(self.width, self.height)
    o.button:setPosition(self.x, self.y)
    o.button.onPressCallback = o.onPress
    o:paintView()
    return o
end

function Seat:setViewComponents()
    local background = Rect.new()
    local width = self.width
    local height = self.height
    background:setSize(width, height)
    background:setRadius(0.3)
    background:setColor(self:getTeamBackgroundColor(self.team))

    local background2 = Rect.new()
    background2:setSize(width - 25, height - 25)
    background2:setPosition(12, 12)
    background2:setRadius(0.3)
    background2:setColor(self:getTeamBackground2Color(self.team))

    local descriptionText = Text(self.role)
    descriptionText:setColor(vec3(0.9, 0.9, 0.9))
    descriptionText:setPixelHeight(50)
    descriptionText:setPosition(30, 50)

    local playerText = Text("...")
    playerText:setColor(vec3(0.9, 0.9, 0.9))
    playerText:setPixelHeight(50)
    playerText:setPosition(width - playerText:getPixelWidth() - 50, 50)

    self.background = background
    self.background2 = background2
    self.descriptionText = descriptionText
    self.playerText = playerText
end

function Seat:paintView()
    local button = self.button
    button:clearView()
    button:paint(self.background)
    button:paint(self.background2)
    button:paint(self.descriptionText)
    button:paint(self.playerText)
end



