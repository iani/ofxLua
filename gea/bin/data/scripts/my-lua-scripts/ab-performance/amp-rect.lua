mygea = of.getApp()

function setup()
   of.setWindowTitle("play with amplitude")
   of.background(0)
end
----------------------------------------------------
function update()
   
   of.fill()
   of.setColor(0,0,0,20)
   of.rect(0,0,of.getWidth(),of.getHeight())

   of.fill()
   of.setColor(255,255,255,250)
   of.rect(100, 0, 10, mygea.amp*5000)
   of.rect(100, mygea.amp*5000+120, 10, of.getHeight()-mygea.amp*5000)

end
----------------------------------------------------
function draw()
end

