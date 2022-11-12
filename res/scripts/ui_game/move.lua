Move = {}

function Move:new(o)
    o = o or {}
    --if o.tiles == nil then
    --    print("Error Move:new(); missing tiles input parameter.")
    --    return
    --end

    setmetatable(o, self)
    self.__index = self
    return o
end

function Move:canMove(fromTile, toTile)
    local fromPoint = fromTile:getPoint()
    local toPoint = toTile:getPoint()
    local moves = fromTile:getMoves()

    for k, v in pairs(moves) do
        if v.file == toPoint.file and v.rank == toPoint.rank then
            return true
        end
    end

    return false
end

