PromoteView = {}

function PromoteView:new(o)
    o = o or {}
    o.width = o.width or 500
    o.x = o.x or 500
    o.y = o.y or 25
    o.pieceColor = o.pieceColor or PieceColor.BLACK
    o.visible = false
    setmetatable(o, self)
    self.__index = self
    PromoteButton:setButton(o)
    PromoteButton:setBackgroundRect(o)

    local btnWidth = math.floor(o.width/4)
    o.height = btnWidth

    o.knightButton = PromoteButton:new{x = o.x, y = o.y, width = btnWidth, pieceType = PieceType.KNIGHT, pieceColor = o.pieceColor}
    o.bishopButton = PromoteButton:new{x = o.x + btnWidth, y = o.y, width = btnWidth, pieceType = PieceType.BISHOP, pieceColor = o.pieceColor}
    o.rookButton = PromoteButton:new{x = o.x + btnWidth*2, y = o.y, width = btnWidth, pieceType = PieceType.ROOK, pieceColor = o.pieceColor}
    o.queenButton = PromoteButton:new{x = o.x + btnWidth*3, y = o.y, width = btnWidth, pieceType = PieceType.QUEEN, pieceColor = o.pieceColor}
    o.promoteButtons = {o.knightButton, o.bishopButton, o.rookButton, o.queenButton}
    return o
end

function PromoteView:setBackgroundRect(o)
    local rect = Rect()
    rect:setRadius(0)
    rect:setAlpha(0.9)
    rect:setPosition(o.x,o.y)
    rect:setSize(o.width, o.width)
    rect:setColor(vec3(0.6,0.6,0.6))
    o.rect = rect
end

function PromoteView:update()

    if self.mover:isWaitingToSetPromotePiece() then
        self:setVisible(true)
    end

    if self.visible and self:wasClicked() then
        self:setPromoteType()
    end

    if self.mover:isWaitingToSetPromotePiece() and self:isCancelled() then
        self:cancel()
    end

    if self.visible then
        self.knightButton:update()
        self.bishopButton:update()
        self.rookButton:update()
        self.queenButton:update()
    end
end

function PromoteView:cancel()
    self:setVisible(false)
    self.mover:clear()
end

function PromoteView:setPromoteType()
    self:setVisible(false)
    local promoteType = self:getChosenPieceType()
    self:clearClicks()
    self.mover:setPromoteType(promoteType)
end

function PromoteView:setVisible(visible)
    self:setColor()
    self.visible = visible
end

function PromoteView:setColor()
    local color = getChessRef():getTurnColor()
    for i = 1, #self.promoteButtons do
        self.promoteButtons[i].piece.color = color
    end
end

function PromoteView:getClickedPromoteButton()
    for i = 1, #self.promoteButtons do
        if self.promoteButtons[i].clicked then
            return self.promoteButtons[i]
        end
    end
    return nil
end

function PromoteView:getChosenPieceType()
    local btn = self:getClickedPromoteButton()
    if btn ~= nil then
        return btn.pieceType
    end
    return nil
end

function PromoteView:clearClicks()
    for i = 1, #self.promoteButtons do
        self.promoteButtons[i].clicked = false
    end
end

function PromoteView:isCancelled()
    return self.visible and isMouseRelease() and not isMousePointerInside(self.x, self.y, self.width, self.height)
end

function PromoteView:wasClicked()
    return self:getClickedPromoteButton() ~= nil
end

function PromoteView:render()
    if self.visible then
        self.knightButton:render()
        self.bishopButton:render()
        self.rookButton:render()
        self.queenButton:render()
    end
end
