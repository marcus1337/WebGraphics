Tile = {}
function Tile:new(o)
    o = o or {}
    o.width = o.width or 100
    o.x = o.x or 0
    o.y = o.y or 0
    o.file = o.file or 0
    o.rank = o.rank or 0
    setmetatable(o, self)
    self.__index = self

    local rect = Rect()
    rect:setRadius(0)
    rect:setAlpha(0.5)
    rect:setPosition(o.x,o.y)
    rect:setSize(o.width, o.width)
    rect:setColor(o:getColor())
    o.rect = rect

    local btn = Button.new(o.width, o.width)
    btn:setPosition(o.x, o.y)
    btn:clearView()
    btn.onPressCallback = function ()
        o:onClick()
    end
    o.btn = btn

    return o
end

function Tile:update()
    self.btn:update()
end

function Tile:getPoint()
    return Point:new(self.file, self.rank)
end

function Tile:get()
    return getChessRef():getTile(self:getPoint())
end

function Tile:isSelectAction()
    local tileInfo = self:get()
    if self.controller:isFromSelect() and tileInfo:isOccupied() and getChessRef():getTurnColor() == tileInfo:getPiece().color and #self:getMoves() > 0 then
        return true
    end
    return false
end

function Tile:getMoves(from)
    from = from or self:getPoint()
    local moves = {}
    local moveVec = getChessRef():getMoves(from)
    for k=1,#moveVec do
        moves[#moves+1] = moveVec[k]
    end
    return moves
end

function Tile:isPossibleTarget()
    return self:canMoveTo(self.controller.from) 
end

function Tile:canMoveTo(from)
    local moves = self:getMoves(from)
    for k, v in pairs(moves) do
        if v.file == self.file and v.rank == self.rank then
            return true
        end
    end
    return false
end

function Tile:getPoint()
    return Point:new(self.file, self.rank)
end

function Tile:onClick()
    print("Tile(" .. tostring(self.file) .. "," .. tostring(self.rank) .. ")")
    if self:isSelectAction() then
        self.controller:setFrom(self:getPoint())
    elseif self:isPossibleTarget() then
        self.controller:setTo(self:getPoint())
    else
        self.controller:setFrom(nil)
    end
end

function Tile:getColor()
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

function Tile:getPieceView()
    local tileInfo = getChessRef():getTile(self:getPoint())
    local piece = tileInfo:getPiece()
    return Piece:new{x = self.x, y = self.y, width = self.width, type = piece.type, color = piece.color}
end

function Tile:renderPiece()
    self:getPieceView():render()
end

function Tile:renderTarget()
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

function Tile:isOccupied()
    return getChessRef():getTile(self:getPoint()):isOccupied()
end

function Tile:render()
    self.rect:render()
    if self:isOccupied() then
        self:renderPiece()
    end
    if self:isPossibleTarget() then  
        self:renderTarget()
    end
end
