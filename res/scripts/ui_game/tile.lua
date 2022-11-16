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

    o.state = TileState:new()
    o.view = TileView:new{x = o.x, y = o.y, width = o.width, file = o.file, rank = o.rank}
    Tile:setButton(o)

    return o
end

function Tile:setButton(o)
    local btn = Button.new(o.width, o.width)
    btn:setPosition(o.x, o.y)
    btn:clearView()
    btn.onPressCallback = function ()
        o:onClick()
    end
    o.btn = btn
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

function Tile:isSelectable()
    local tileInfo = self:get()
    return tileInfo:isOccupied() and getChessRef():getTurnColor() == tileInfo:getPiece().color and #self:getMoves() > 0
end

function Tile:isTarget(fromTile)
    for _, point in pairs(getChessRef():getHumanMoves(fromTile:getPoint())) do
        if self:isPoint(point) then
            return true
        end
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

function Tile:getPoint()
    return Point:new(self.file, self.rank)
end

function Tile:isPoint(otherPoint)
    local point = self:getPoint()
    return point.file == otherPoint.file and point.rank == otherPoint.rank
end

function Tile:onClick()
    print("Tile(" .. tostring(self.file) .. "," .. tostring(self.rank) .. ")")
    self.state.clicked = true
end

function Tile:isOccupied()
    return getChessRef():getTile(self:getPoint()):isOccupied()
end

function Tile:isHovered()
    return self.btn:isHovered()
end

function Tile:isHighlighted()
    return self.state.highlightable and self:isHovered() and ((not self.state.selected and self:isSelectable()) or self.state.target)
end

function Tile:render()
    self.view.rect:render()
    if self:isOccupied() then
        self.view:renderPiece()
    end
    if self.state.target then  
        self.view:renderTarget()
    end
    if self:isHighlighted() then
        self.view:renderHighlight()
    end
end



