BoardController = {}
function BoardController:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self

    o.from = nil

    return o
end

function BoardController:getMoves()
    local moves = {}
    local chess = getChessRef()
    if self:isToSelect() then
        local moveVec = chess:getMoves(self.from)
        for k=1,#moveVec do
            moves[#moves+1] = moveVec[k]
        end
    end
    return moves
end

function BoardController:setFrom(from)
    self.from = from
end

function BoardController:setTo(to)
    local chess = getChessRef()
    chess:move(self.from, to)
    self.from = nil
end

function BoardController:isFromSelect()
    return self.from == nil
end

function BoardController:isToSelect()
    return self:isFromSelect() == false
end


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

function Tile:get()
    local chess = getChessRef()
    return chess:getTile(Point:new(self.file, self.rank))
end

function Tile:isSelectable()
    local tileInfo = self:get()
    local chess = getChessRef()
    if self.controller:isFromSelect() and tileInfo:isOccupied() and chess:getTurnColor() == tileInfo:getPiece().color then
        return true
    end
    if self.controller:isToSelect() and self:isTarget() then
        return true
    end
    return false
end

function Tile:isTarget()
    print("isTarget()")
    local moves = self.controller:getMoves()
    local validMove = false
    for k, v in pairs(moves) do
        print( v:toString())
        if v.file == self.file and v.rank == self.rank then
            validMove = true
        end
    end
    return validMove
end

function Tile:getPoint()
    return Point:new(self.file, self.rank)
end

function Tile:onClick()
    print("Tile(" .. tostring(self.file) .. "," .. tostring(self.rank) .. ") selectable? " .. tostring(self:isSelectable()) )
    if not self:isSelectable() then
        self.controller:setFrom(nil)
        return
    end

    if self.controller:isFromSelect() then
        self.controller:setFrom(self:getPoint())
    elseif self.controller:isToSelect() then
        self.controller:setTo(self:getPoint())
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

function Tile:render()
    self.rect:render()
    local chess = getChessRef()
    local tileInfo = chess:getTile(Point:new(self.file, self.rank))
    if tileInfo:isOccupied() then
        local piece = tileInfo:getPiece()
        pieceView = Piece:new{x = self.x, y = self.y, width = self.width, type = piece.type, color = piece.color}
        pieceView:render()
    end
end

Board = {}

function Board:new(o)
    o = o or {}
    o.width = o.width or 8*115
    local tileWidth = math.floor(o.width/8)
    o.x = o.x or 500
    o.y = o.y or 50
    o.controller = BoardController:new()
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
            local tile = Tile:new{x = x, y = y, file = file, rank = rank, width = tileWidth, controller = o.controller}
            tiles[#tiles+1] = tile
        end
    end
    self.tiles = tiles
    return o
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

