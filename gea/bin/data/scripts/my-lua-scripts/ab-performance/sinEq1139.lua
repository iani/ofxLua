-- add 3 min
local speed = 0.001
local amp = 100
local freq = 0.03
local xPos = of.getWidth()/2
----------------------------------------------------
function setup()
	of.setWindowTitle("sinEq")
end
----------------------------------------------------
function update()
end
----------------------------------------------------
function draw()
   of.fill()
   of.setColor(0,0,0,20)
   of.rect(0,0,of.getWidth(),of.getHeight())
   for i=1,10 do
      sinEq(50*i, speed,200, 0.3*math.sin(of.getFrameNum()/100))
   end
end
----------------------------------------------------
function sinEq(xPos,speed,amp,freq)
   of.noFill()
   of.setColor(255,255,250,100)
   local samples = {}
   of.beginShape()
   for i = 0, 500 do
      local a = (3.14/10)*i;
      samples[i]=amp*math.cos(math.sin(freq*a));
          of.vertex(
             xPos + math.sin(of.getFrameNum()*speed)*samples[i],
             i*2
          )
   end
   of.endShape(false)
end
----------------------------------------------------
function exit()
end
----------------------------------------------------
