Move = {}

function Move:new(o)
    o = o or {}
    --if o.tiles == nil then
    --    print("Error Move:new(); missing tiles input parameter.")
    --    return
    --end
    setmetatable(o, self)
    self.__index = self
    o.promoting = false
    return o
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

