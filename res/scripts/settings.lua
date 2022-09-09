
miniBtnSize = 50

function getCancelButton()
    local btn = Button.new(miniBtnSize, miniBtnSize)
    btn:setPosition(20, 1010)
    btn:setImage("icons/cancel.png")
    btn.onPressCallback = onCancel
    return btn
end

cancelButton = getCancelButton()
backgroundImage = Image("background2.png")
backgroundImage:setPosition(0,0)
backgroundImage:setSize(1920,1080)

function update()
    cancelButton:update()
end

function render()
    backgroundImage:render()
    cancelButton:render()
end

