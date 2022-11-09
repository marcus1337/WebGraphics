
Board = {}

function Board:new(o)
    o = o or {}
    o.width = o.width or 8*115
    o.x = o.x or 500
    o.y = o.y or 50
    o.controller = BoardController:new()
    setmetatable(o, self)
    self.__index = self

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
            local tile = Tile:new{x = x, y = y, file = file, rank = rank, width = tileWidth, controller = o.controller}
            tiles[#tiles+1] = tile
        end
    end
    self.tiles = tiles
end

function Board:update()
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

