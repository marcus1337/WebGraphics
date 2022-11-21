TileView = {}

function TileView:new(o)
    o = o or {}
    o.width = o.width or 100
    o.x = o.x or 0
    o.y = o.y or 0
    o.file = o.file or 0
    o.rank = o.rank or 0
    setmetatable(o, self)
    self.__index = self

    o.view = View(o.width, o.width)
    o.view:setShaderProgram("tile")
    o.view:setAlpha(1.0)
    o.view:setPosition(o.x,o.y)
    TileView:setBackgroundRect(o)

    return o
end

function TileView:setBackgroundRect(o)
    local rect = Rect()
    rect:setRadius(0)
    rect:setAlpha(1.0)
    rect:setPosition(0,0)
    rect:setSize(o.width, o.width)
    rect:setColor(o:getColor())
    o.rect = rect
end

function TileView:getColor()
    local darkColor = vec3(0.2,0.2,0.2)
    local lightColor = vec3(0.4,0.4,0.3)
    if self.file % 2 == 0 and self.rank % 2 == 0 then
        return darkColor
    elseif self.file % 2 == 0 and self.rank % 2 ~= 0 then
        return lightColor
    end
    if self.file % 2 ~= 0 and self.rank % 2 == 0 then
        return lightColor
    elseif self.file % 2 ~= 0 and self.rank % 2 ~= 0 then
        return darkColor
    end
    return nil
end

function TileView:render()
    self.view:paint(self.rect)
    self.view:render()
end

function TileView:renderHighlight()
    local rect = Rect()
    rect:setSize(self.width, self.width)
    rect:setPosition(self.x, self.y)
    rect:setColor(vec3(0.5,0.5,0.0))
    rect:setThickness(0.05)
    rect:setRadius(0.1)
    rect:render()
end

function TileView:renderPiece()
    self:getPieceView():render()
end

function TileView:renderTarget(highlighted)
   local dot = Circle.new()
   local radius = math.floor(self.width)
   local x = math.floor(self.x + self.width/2 - radius/2)
   local y = math.floor(self.y + self.width/2 - radius/2)
   dot:setPosition(x, y)
   dot:setColor(vec3(0.2,0.5,0.2))
   if highlighted then
    dot:setColor(vec3(0.5,0.5,0.4))
   end
   dot:setAlpha(1.0)
   dot:setSize(radius, radius)
   dot:setThickness(1.0)
   dot:setUniform("target", 1.0)
   dot:render()
end

function TileView:getPieceView()
    local tileInfo = getChessRef():getTile(Point:new(self.file, self.rank))
    local piece = tileInfo:getPiece()
    return Piece:new{x = self.x, y = self.y, width = self.width, type = piece.type, color = piece.color}
end
