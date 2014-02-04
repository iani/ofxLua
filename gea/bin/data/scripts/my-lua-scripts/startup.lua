--gea = of.gea()
app = of.app();

function setup()
   of.setWindowTitle("osc")
   of.background(0)
   --app:test()
   --gea:setup()
end
----------------------------------------------------
function update()
   --gea:update()
   app:amp()

   
end
----------------------------------------------------
function draw()
   of.fill()
   of.setColor(100,0,0,100)
   of.rect(10,0,of.getWidth(), of.getHeight())
end
----------------------------------------------------
function keyPressed(key)
   if key == string.byte("s") then
   end
end
