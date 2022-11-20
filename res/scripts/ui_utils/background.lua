

function getBackgroundImage(name)
	local image = Image(name)
	image:setPosition(0,0)
	image:setSize(1920,1080)
	return image
end


Background = {}
function Background:new(o)
    o = o or {}
    setmetatable(o, self)
	self.__index = self
	o.view = View(1920, 1080)

	Background:paintRectangles(o.view)

    return o
end

function Background:paintRectangles(view)
	local rectList = Background:getRectList()
    for k, rect in pairs(rectList) do
        view:paint(rect)
    end
end

function Background:getRectColor(row, col)
	row = row or 0
	col = col or 0
	local color1 = vec3(0.5,0.5,0.5)
    local color2 = vec3(0.3,0.3,0.3)
    if row % 2 == 0 and col % 2 == 0 then
        return color1
    elseif row % 2 == 0 and col % 2 ~= 0 then
        return color2
    end
    if row % 2 ~= 0 and col % 2 == 0 then
        return color2
    elseif row % 2 ~= 0 and col % 2 ~= 0 then
        return color1
    end
    return nil
end

function Background:getRect(size, row, col)
	local rect = Rect()
	rect:setSize(size,size)
	rect:setRadius(0.0)
	rect:setPosition(col*size, row*size)
	rect:setColor(Background:getRectColor(row,col))
	return rect
end

function Background:getRectList()
	local list = {}
	local size = 120
	local numCols = math.floor(1920 / size)
	local numRows = math.floor(1080 / size)
	for col=0, numCols - 1 do 
		for row=0, numRows - 1 do
			list[#list+1] = Background:getRect(size, row, col)
		end
	end
	return list
end

function Background:render()
	self.view:render()
end