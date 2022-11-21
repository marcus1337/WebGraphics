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

function TileView:isDark()
    if self.file % 2 == 0 and self.rank % 2 == 0 then
        return true
    elseif self.file % 2 == 0 and self.rank % 2 ~= 0 then
        return false
    end
    if self.file % 2 ~= 0 and self.rank % 2 == 0 then
        return false
    elseif self.file % 2 ~= 0 and self.rank % 2 ~= 0 then
        return true
    end
    return nil
end

function TileView:getColor()
    local darkColor = vec3(0.2,0.2,0.2)
    local lightColor = vec3(0.4,0.4,0.3)
    if self:isDark() then
        return darkColor
    end
    return lightColor
end
function TileView:getTextColor()
    local darkColor = vec3(0.2,0.2,0.2)
    local lightColor = vec3(0.4,0.4,0.3)
    if self:isDark() then
        return lightColor
    end
    return darkColor
end

function TileView:getTextLetter(str)
    local text = Text(str)
    text:setFont("Roboto-Bold")
    text:setColor(self:getTextColor())
    text:setPixelHeight(30)
    return text
end

function TileView:getFileLetter()
    if self.rank == 0 then
        local str = string.char(97 + self.file)
        local text = self:getTextLetter(str)
        text:setPosition(5,5)
        return text
    end
    return nil
end

function TileView:getRankLetter()
    if self.file == 7 then
        local str = string.char(48 + self.rank)
        local text = self:getTextLetter(str)
        text:setPosition(95,85)
        return text
    end
    return nil
end

function TileView:render()
    self.view:paint(self.rect)
    local txt = self:getFileLetter()
    if txt ~= nil then
        self.view:paint(txt)
    end
    txt = self:getRankLetter()
    if txt ~= nil then
        self.view:paint(txt)
    end

    self.view:render()
end

function TileView:renderPiece()
    self:getPieceView():render()
end

function TileView:getPieceView()
    local tileInfo = getChessRef():getTile(Point:new(self.file, self.rank))
    local piece = tileInfo:getPiece()
    return Piece:new{x = self.x, y = self.y, width = self.width, type = piece.type, color = piece.color}
end
