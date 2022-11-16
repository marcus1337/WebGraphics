PromoteButton = {}

function PromoteButton:new(o)
    o = o or {}
    o.width = o.width or 100
    o.pieceType = o.pieceType or PieceType.PAWN
    o.pieceColor = o.pieceColor or PieceColor.BLACK
    o.x = o.x or 0
    o.y = o.y or 0
    o.clicked = false
    o.piece = o.piece or Piece:new{x = o.x, y = o.y, width = o.width, type = o.pieceType, color = o.pieceColor}
    setmetatable(o, self)
    self.__index = self
    PromoteButton:setButton(o)
    PromoteButton:setBackgroundRect(o)
    PromoteButton:setHoverBackgroundRect(o)
    return o
end

function PromoteButton:setBackgroundRect(o)
    local rect = Rect()
    rect:setRadius(0)
    rect:setAlpha(0.9)
    rect:setPosition(o.x,o.y)
    rect:setSize(o.width, o.width)
    rect:setColor(vec3(0.6,0.6,0.6))
    o.rect = rect
end

function PromoteButton:setHoverBackgroundRect(o)
    local hoverRect = Rect()
    hoverRect:setRadius(0)
    hoverRect:setAlpha(0.5)
    hoverRect:setPosition(o.x,o.y)
    hoverRect:setSize(o.width, o.width)
    hoverRect:setColor(vec3(0.8,0.8,0.0))
    o.hoverRect = hoverRect
end

function PromoteButton:setButton(o)
    local btn = Button.new(o.width, o.width)
    btn:setPosition(o.x, o.y)
    btn:clearView()
    btn.onPressCallback = function ()
        o:onClick()
    end
    o.btn = btn
end

function PromoteButton:onClick()
    print("PromoteButton() click")
    self.clicked = true
end

function PromoteButton:update()
    self.btn:update()
end


function PromoteButton:render()
    self.rect:render()
    if self.btn:isHovered() then
        self.hoverRect:render()
    end
    self.piece:render()
end
