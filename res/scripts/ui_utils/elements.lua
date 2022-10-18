Elements = {}
Elements.__index = Elements

function Elements:new(o)
    o = o or {}
    o.list = o.list or {}
    setmetatable(o, self)
    return o
end

function Elements:add(element)
    o.list[#o.list+1] = element
end

function Elements:addList(list)
    for k, v in pairs(list) do 
        self.add(v)
    end
end

function Elements:update()
    for k, v in pairs(self.list) do 
        v:update()
    end
end

function Elements:render()
    for k, v in pairs(self.list) do 
        v:render()
    end
end