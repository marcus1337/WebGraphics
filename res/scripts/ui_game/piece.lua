Piece = {theme = "alpha"}

function Piece:new(o)
    o = o or {}
    o.width = o.width or 100
    o.x = o.x or 0
    o.y = o.y or 0
    o.type = o.type or PieceType.KING
    o.color = o.color or PieceColor.WHITE
    setmetatable(o, self)
    self.__index = self
    return o
end

function Piece:render()
    local img = Image(self:getImgPath())
    img:setSize(self.width, self.width)
    img:setPosition(self.x, self.y)
    img:render()
end

function Piece:getPieceFileName()
    return self:getPieceFileColorName() .. self:getPieceFilePieceName() .. ".png"
end

function Piece:getImgPath()
    return "pieces//" .. self.theme .. "//" .. self:getPieceFileName()
end

function Piece:getPieceFilePieceName()
    if self.type == PieceType.KING then
        return "K"
    elseif self.type == PieceType.ROOK then
        return "R"
    elseif self.type == PieceType.QUEEN then
        return "Q"
    elseif self.type == PieceType.BISHOP then
        return "B"
    elseif self.type == PieceType.KNIGHT then
        return "N"
    else
        return "P"
    end
end

function Piece:getPieceFileColorName()
    if self.color == PieceColor.WHITE then
        return "w"
    else
        return "b"
    end
end