Seat = {}
Seat.__index = Seat

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

function Seat:new(o)
    o = o or {}
    setmetatable(o, self)
    o.x = o.x or 0
    o.y = o.y or 0
    o.width = o.width or 700
    o.height = o.height or 150
    o.team = o.team or 1
    o.role = o.role or "???"

    o.background = Rect.new()
    o.background = o.background
    o.background:setSize(o.width, o.height)
    o.background:setRadius(0.3)
    o.background:setColor(self:getTeamBackgroundColor(o.team))

    o.background2 = Rect.new()
    o.background2:setSize(o.width - 25, o.height - 25)
    o.background2:setPosition(12, 12)
    o.background2:setRadius(0.3)
    o.background2:setColor(self:getTeamBackground2Color(o.team))

    o.descriptionText = Text(o.role)
    o.descriptionText:setColor(vec3(0.9, 0.9, 0.9))
    o.descriptionText:setPixelHeight(50)
    o.descriptionText:setPosition(30, 50)

    o.playerText = Text("...")
    o.playerText:setColor(vec3(0.9, 0.9, 0.9))
    o.playerText:setPixelHeight(50)
    o.playerText:setPosition(o.width - o.playerText:getPixelWidth() - 50, 50)
    return o
end

function Seat:update()

end

function Seat:render()
    local view = View.new(self.width, self.height)
    view:setPosition(self.x, self.y)
    view:paint(self.background)
    view:paint(self.background2)
    view:paint(self.descriptionText)
    view:paint(self.playerText)

    if isMousePointerInside(view:getX(), view:getY(), view:getWidth(), view:getHeight()) then
        print("Role: " .. self.role .. " Team: " .. tostring(self.team))
    end

    view:render()
end