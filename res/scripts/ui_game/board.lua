
Board = {}

function Board:new(o)
    o = o or {}
    o.width = o.width or 8*115
    o.x = o.x or 500
    o.y = o.y or 50
    setmetatable(o, self)
    self.__index = self
    o.move = Move:new()
    Board:setBackground(o)
    Board:setTiles(o)

    return o
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
    self:handleTileClick()
    for k, v in pairs(self.tiles) do
        v:update()
    end
end

function Board:render()
    self.backround:render()    
    for k, v in pairs(self.tiles) do
        v:render()
    end
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
    for k, toTile in pairs(self.tiles) do
        toTile.state.target = self.move:canMove(fromTile, toTile)
    end
end

function Board:setTileHighlightStates()
    local selectedTile = self:getSelectedTile()
    for k, tile in pairs(self.tiles) do
        tile.state.highlightable = (selectedTile == nil or tile.state.target) and not self.move.promoting
    end
end

function Board:handleTileClick()
    local tile = self:getClickedTile()
    if tile == nil then
        return
    end
    tile.state.clicked = false
    if tile.state.target then
        if self.move:isPromoteMove(self:getSelectedTile(), tile) then
            print("Promote move.....")
            self.move.promoting = true
        else
            getChessRef():move(self:getSelectedTile():getPoint(), tile:getPoint())
        end
        self:clearTileSelectStates()
        self:clearTileTargetStates()
    elseif tile:isSelectable() and not tile.state.selected then
        self:clearTileSelectStates()
        tile.state.selected = true
        self:setTileTargetStates(tile)
    else
        self:clearTileSelectStates()
        self:clearTileTargetStates()
    end
    self:setTileHighlightStates()
end



