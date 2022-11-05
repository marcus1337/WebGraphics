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

    return o
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

function Tile:render()
    self.rect:render()
end

Board = {}

function Board:new(o)
    o = o or {}
    o.width = o.width or 8*115
    local tileWidth = math.floor(o.width/8)
    o.x = o.x or 500
    o.y = o.y or 50
    setmetatable(o, self)
    self.__index = self

    local backround = Rect()
    backround:setRadius(0.0)
    backround:setColor(vec3(0.5,0.5,0.5))
    backround:setSize(o.width, o.width)
    backround:setPosition(o.x, o.y)
    self.backround = backround
    local tiles = {}
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
    return o
end

function Board:render()
    self.backround:render()    
    for k, v in pairs(self.tiles) do
        v:render()
    end
end