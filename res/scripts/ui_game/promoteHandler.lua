PromoteHandler = {}

function PromoteHandler:new(o)
    o = o or {}
    o.width = o.width or 500
    o.x = o.x or 500
    o.y = o.y or 25
    setmetatable(o, self)
    self.__index = self
    if o.move == nil then
        print("Promote:new() init error: missing o.move.")
    end
    o.promoteView = PromoteView:new({x = o.x, y = o.y, width = o.width})
    return o
end

function PromoteHandler:update()
    if self.promoteView.visible and self.promoteView:wasClicked() then
        self:makeMove()
    end
    if self.promoteView:isCancelled() then
        self:cancel()
    end
    self.promoteView:update()
end

function PromoteHandler:render()
    self.promoteView:render()
end

function PromoteHandler:cancel()
    self.promoteView:setVisible(false)
    self.move:clear()
end

function PromoteHandler:prepareMove(fromTile, toTile)
    self.promoteView:setVisible(true)
    self.move.fromPoint = fromTile:getPoint()
    self.move.toPoint = toTile:getPoint()
end

function PromoteHandler:makeMove()
    self.promoteView:setVisible(false)
    local promoteType = self.promoteView:getChosenPieceType()
    self.promoteView:clearClicks()
    self.move.promoteType = promoteType
    self.move:promote()
end