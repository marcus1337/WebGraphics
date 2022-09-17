Seat = {}
Seat.__index = Seat

function Seat:getTeamBackgroundColor(team)
    if team == 0 then
        return vec3(0.05, 0.35, 0.55)
    else
        return vec3(0.55, 0.35, 0.05)
    end
end

function Seat:getTeamBackground2Color(team)
    if team == 0 then
        return vec3(0.15, 0.15, 0.25)
    else
        return vec3(0.25, 0.15, 0.15)
    end
end

function Seat:new(o)
    o = o or {}
    setmetatable(o, self)
    local x = o.x or 0
    local y = o.y or 0
    local width = 600
    local height = 150
    local team = o.team or 0
    self.background = Rect.new()
    self.background:setSize(width, height)
    self.background:setPosition(x, y)
    self.background:setRadius(0.3)
    self.background:setColor(self:getTeamBackgroundColor(team))

    self.background2 = Rect.new()
    self.background2:setSize(width - 25, height - 25)
    self.background2:setPosition(x + 12, y + 12)
    self.background2:setRadius(0.3)
    self.background2:setColor(self:getTeamBackground2Color(team))

    self.descriptionText = Text("Goalie")
    self.descriptionText:setColor(vec3(0.9, 0.9, 0.9))
    self.descriptionText:setPixelHeight(50)
    self.descriptionText:setPosition(x + 30, y + 50)

    self.playerText = Text("...")
    self.playerText:setColor(vec3(0.9, 0.9, 0.9))
    self.playerText:setPixelHeight(50)
    self.playerText:setPosition(x + width - self.playerText:getPixelWidth() - 50, y + 50)
    return o
end

function Seat:update()

end

function Seat:render()
    self.background:render()
    self.background2:render()
    self.descriptionText:render()
    self.playerText:render()
end

titleText = TitleText:new { textStr = "Lobby" }
setUIElements { getCancelButton(), getSettingsButton() }

seat1 = Seat:new {}

function update()
    updateUIElements()
end

function render()
    renderUIElements()
    titleText:render()
    seat1:render()
end
