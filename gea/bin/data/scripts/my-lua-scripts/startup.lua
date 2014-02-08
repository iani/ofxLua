function setup()
   of.setWindowTitle("startUp")
   of.background(0)
end
----------------------------------------------------
function update()
end
----------------------------------------------------
function draw()
   of.fill()
   of.setColor(0,0,0,20)
   of.rect(10,0,of.getWidth(), of.getHeight())
end
----------------------------------------------------
function keyPressed(key)
   if key == string.byte("s") then
   end
end
