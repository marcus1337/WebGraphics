

function getBackgroundImage(name)
	local image = Image(name)
	image:setPosition(0,0)
	image:setSize(1920,1080)
	return image
end

uiElements = {}
function setUIElements(elements)
    uiElements = elements
end
function updateUIElements()
    for k, v in pairs(uiElements) do 
        v:update()
    end
end
function renderUIElements()
    for k, v in pairs(uiElements) do 
        v:render()
    end
end

