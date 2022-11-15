Move = {}

function Move:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    o.fromPoint = nil
    o.toPoint = nil
    o.promoteType = nil
    return o
end

function Move:getPromoteTypeValue(promoteType)
    if promoteType == PieceType.KNIGHT then
        return 1
    elseif promoteType == PieceType.BISHOP then
        return 2
    elseif promoteType == PieceType.ROOK then
        return 3
    elseif promoteType == PieceType.QUEEN then
        return 4
    else 
        return 0
    end
end

function Move:getPromotePoint(point, promoteType)
    if point.rank == 7 then
        point.rank = point.rank + self:getPromoteTypeValue(self.promoteType)
    end
    if point.rank == 0 then
        point.rank = point.rank - self:getPromoteTypeValue(self.promoteType)
    end
    return point
end

function Move:clear()
    self.fromPoint = nil
    self.toPoint = nil
    self.promoteType = nil
end

function Move:promote()
    if self.fromPoint == nil or self.toPoint == nil or self.promoteType == nil then
        print("promote(): nil error.")
    end
    local chess = getChessRef()
    local toPoint = self:getPromotePoint(self.toPoint, self.promoteType)
    chess:move(self.fromPoint, toPoint)
    self:clear()
end

function Move:isPromoteMove(fromTile, toTile)
    local fromPiece = fromTile:get():getPiece()
    local toPoint = toTile:getPoint()
    return fromPiece.type == PieceType.PAWN and (toPoint.rank == 0 or toPoint.rank == 7)
end

function Move:isPromotePieceRank(rank)
    return rank < 0 or rank > 7
end

function Move:getPromoteTilePoint(toPoint)
    if toPoint.rank > 7 then
        return Point:new(toPoint.file, 7)
    end
    return Point:new(toPoint.file, 0)
end

function Move:canMove(fromTile, toTile)
    local toPoint = toTile:getPoint()
    local moves = fromTile:getMoves()
    for k, point in pairs(moves) do
        if self:isPromotePieceRank(point.rank) then
            point = self:getPromoteTilePoint(point)
        end
        if point.file == toPoint.file and point.rank == toPoint.rank then
            return true
        end
    end
    return false
end

