local count=0
midi = of.midi()
----------------------------------------------------
function setup()
	of.setWindowTitle("liveCoding_3")
        midi:setup()
--        of.background(0)

end
----------------------------------------------------
function update()
         midi:update()
end
----------------------------------------------------
function draw()

      of.fill()
      of.setColor(0,0,30,20)
      of.rect(0,0,1200,1000)

      of.noFill()
      of.setColor(255,255,250,220)
      local samples = {}
      of.beginShape()
      for i = 0, 800 do
          local a = (3.14/100)*i;
          samples[i]=300*math.cos(10*math.sin(count*0.1)*math.sin(5*a*midi:map(1,0,5)));
          of.vertex(400 + math.sin(count)*samples[i],i*2)
      end
      of.endShape(false)

      count=count+1

end
----------------------------------------------------
function exit()
end
----------------------------------------------------
