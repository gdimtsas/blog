for i=1,100,1 do
local entity = Engine.Entity(i)
local tc = Engine.TransformationComponent(i, i, i)
entity:addComponent(tc)
engine:addEntity(entity)
end
