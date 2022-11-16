
Board = {}

function Board:new(o)
    o = o or {}
    local tileWidth = 115
    o.width = o.width or 8*tileWidth
    o.x = o.x or 500
    o.y = o.y or 25
    setmetatable(o, self)
    self.__index = self
    o.move = Move:new()

    self:setPromoteHandler(o, tileWidth)
    Board:setBackground(o)
    Board:setTiles(o)

    return o
end

function Board:setPromoteHandler(o, tileWidth)
    local promoteWidth = tileWidth * 4
    local promoteXPosition = math.floor(o.x + o.width / 2.0 - promoteWidth / 2.0)
    local promoteYPosition = math.floor (o.y + tileWidth * 8 + 10.0) 
    o.promoteHandler = PromoteHandler:new{x = promoteXPosition, y = promoteYPosition, width = promoteWidth, move = o.move}
end

function Board:setBackground(o)
    local backround = Rect()
    backround:setRadius(0.0)
    backround:setColor(vec3(0.5,0.5,0.5))
    backround:setSize(o.width, o.width)
    backround:setPosition(o.x, o.y)
    self.backround = backround
end

function Board:setTiles(o)
    local tiles = {}
    local tileWidth = math.floor(o.width/8)
    for file=0,7 do 
        for rank=0,7 do
            local width = math.floor(o.width/8)
            local x = file * width + o.x
            local y = rank * width + o.y
            local tile = Tile:new{x = x, y = y, file = file, rank = rank, width = tileWidth}
            tiles[#tiles+1] = tile
        end
    end
    self.tiles = tiles
end

function Board:update()

    self.promoteHandler:update()

    if self:getClickedTile() ~= nil then 
        self:handleTileClick()
    end
    for k, v in pairs(self.tiles) do
        v:update()
    end
end

function Board:render()
    self.backround:render()    
    for k, v in pairs(self.tiles) do
        v:render()
    end
    self.promoteHandler:render()
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
        tile.state.highlightable = (selectedTile == nil or tile.state.target) and not self.move.promoting
    end
end

function Board:handleTargetClick(tile)
    local fromPoint = self:getSelectedTile():getPoint()
    local toPoint = tile:getPoint()
    local chess = getChessRef()
    if chess:isPromoteMove(fromPoint, toPoint) then
        self.promoteHandler:prepareMove(fromPoint, toPoint)
    else
        chess:move(fromPoint, toPoint)
    end
    self:handleTileCancelClick()
end

function Board:handleSelectClick(tile)
    self:clearTileSelectStates()
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
    self:setTileHighlightStates()
end



