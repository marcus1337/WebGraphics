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

    TileView:setBackgroundRect(o)

    return o
end

function TileView:setBackgroundRect(o)
    local rect = Rect()
    rect:setRadius(0)
    rect:setAlpha(0.5)
    rect:setPosition(o.x,o.y)
    rect:setSize(o.width, o.width)
    rect:setColor(o:getColor())
    o.rect = rect
end

function TileView:getColor()
    local color1 = vec3(0.15,0.15,0.15)
    local color2 = vec3(0.5,0.5,0.3)
    if self.file % 2 == 0 and self.rank % 2 == 0 then
        return color1
    elseif self.file % 2 == 0 and self.rank % 2 ~= 0 then
        return color2
    end
    if self.file % 2 ~= 0 and self.rank % 2 == 0 then
        return color2
    elseif self.file % 2 ~= 0 and self.rank % 2 ~= 0 then
        return color1
    end
    return nil
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

function TileView:renderTarget()
   local dot = Circle.new()
   local radius = math.floor(self.width/2.5)
   local x = math.floor(self.x + self.width/2 - radius/2)
   local y = math.floor(self.y + self.width/2 - radius/2)
   dot:setPosition(x, y)
   dot:setColor(vec3(0.7,0.5,0.2))
   dot:setAlpha(0.5)
   dot:setSize(radius, radius)
   dot:setThickness(1.0)
   dot:render()
end

function TileView:getPieceView()
    local tileInfo = getChessRef():getTile(Point:new(self.file, self.rank))
    local piece = tileInfo:getPiece()
    return Piece:new{x = self.x, y = self.y, width = self.width, type = piece.type, color = piece.color}
end
