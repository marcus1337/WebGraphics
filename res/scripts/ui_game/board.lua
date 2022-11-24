
Board = {}

function Board:new(o)
    o = o or {}
    o.width = o.width or 8*115
    o.x = o.x or 500
    o.y = o.y or 25
    setmetatable(o, self)
    self.__index = self
    o.playerColorPerspective = PieceColor.WHITE

    Board:setBackground(o)
    Board:setTiles(o)

    return o
end

function Board:getTileWidth()
    return math.floor(self.width/8)
end

function Board:stopRenderPiece(point)
    self:getTile(point).state.renderPiece = false
end

function Board:startRenderPiece(point)
    self:getTile(point).state.renderPiece = true
end

function Board:setBackground(o)
    local backround = Rect()
    backround:setRadius(0.0)
    backround:setColor(vec3(0.5,0.5,0.5))
    backround:setSize(o.width, o.width)
    backround:setPosition(o.x, o.y)
    o.backround = backround
end

function Board:setTiles(o)
    local tiles = {}
    local width = o:getTileWidth()
    for file=0,7 do 
        for rank=0,7 do
            local x = file * width + o.x
            local y = rank * width + o.y
            if o.playerColorPerspective == PieceColor.BLACK then
                y = (7 - rank) * width + o.y
                x = (7 - file) * width + o.x
            end
            local tile = Tile:new{x = x, y = y, file = file, rank = rank, width = width, playerColorPerspective = o.playerColorPerspective}
            tiles[#tiles+1] = tile
        end
    end
    o.tiles = tiles
end

function Board:update()

    if self:getClickedTile() ~= nil then 
        self:handleTileClick()
    end
    for k, v in pairs(self.tiles) do
        v:update()
    end
    self:setTileHighlightStates()
end

function Board:setColorPerspective(color)
    if self.playerColorPerspective == color then
        return
    end
    self.playerColorPerspective = color
    Board:setTiles(self)
end

function Board:render()
    self.backround:render()    
    for k, v in pairs(self.tiles) do
        v:render()
    end
end

function Board:getTile(point)
    for k, tile in pairs(self.tiles) do
        if tile:getPoint() == point then
            return tile
        end
    end
    return nil
end

function Board:getClickedTile()
    for k, tile in pairs(self.tiles) do
        if tile.state.clicked then
            return tile
        end
    end
    return nil
end

function Board:getSelectedTile()
    for k, tile in pairs(self.tiles) do
        if tile.state.selected then
            return tile
        end
    end
    return nil
end

function Board:clearTileSelectStates()
    for k, tile in pairs(self.tiles) do
        tile.state.selected = false
    end
end

function Board:clearTileTargetStates()
    for k, tile in pairs(self.tiles) do
        tile.state.target = false
    end
end

function Board:setTileTargetStates(fromTile)
    for _, toTile in pairs(self.tiles) do
        if toTile:isTarget(fromTile) then
            toTile.state.target = true
        end
    end
end

function Board:setTileHighlightStates()
    local selectedTile = self:getSelectedTile()
    for k, tile in pairs(self.tiles) do
        tile.state.highlightable = (selectedTile == nil or tile.state.target) and not self.mover:isWaitingToSetPromotePiece()
    end
end

function Board:handleTargetClick(tile)
    local fromPoint = self:getSelectedTile():getPoint()
    local toPoint = tile:getPoint()
    self.mover:prepare(fromPoint, toPoint)
    self:handleTileCancelClick()
end

function Board:handleSelectClick(tile)
    self:handleTileCancelClick()
    tile.state.selected = true
    self:setTileTargetStates(tile)
end

function Board:isSelectClick(tile)
    return tile:isSelectable() and not tile.state.selected
end

function Board:handleTileCancelClick()
    self:clearTileSelectStates()
    self:clearTileTargetStates()
end

function Board:handleTileClick()
    local tile = self:getClickedTile()
    tile.state.clicked = false
    if tile.state.target then
        self:handleTargetClick(tile)
    elseif self:isSelectClick(tile) then
        self:handleSelectClick(tile)
    else
        self:handleTileCancelClick()
    end
end



