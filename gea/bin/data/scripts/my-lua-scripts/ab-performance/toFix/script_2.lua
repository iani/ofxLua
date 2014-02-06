----------------------------------------------------
function setup()
	of.setWindowTitle("liveCoding_1")
	of.setFrameRate(30)
--        of.background(255)
end
----------------------------------------------------
function update()
end
----------------------------------------------------
function draw()
      of.fill()
--      of.setColor(0,0,30,2)
--      of.rect(0,0,1200,1000)
      of.noFill()
      of.setColor(255,255,250,220)
      local samples = {}
      of.beginShape()
      for i = 0, 800 do
          local a = (math.TWO_PI/100)*i;
--          samples[i]=200*math.cos(1*a + 1.2);
--          samples[i]=300*math.cos(math.cos(1*a + 1.2));
          samples[i]=300*math.cos(math.sin(50*a*0.2));
          of.vertex(of.getWidth() + math.sin(of.getFrameNum()*0.05)*samples[i],i*2)
      end
      of.endShape(false)
end
----------------------------------------------------
function exit()
end
----------------------------------------------------
--[[
    ofBeginShape();

    int numSamples = ofGetScreenWidth()/4;
    float samples[numSamples];
    for(int i=0; i<numSamples;i++){
        float a = TWO_PI/numSamples*i;
        samples[i]=amp*cos(freq*a + phase);
        ofVertex(x + sin(ofGetFrameNum()*speed)*samples[i],i*4);
    }
    ofEndShape();



]]




--[[
       of.setColor(0,0,30,20)
       of.rect(0,0,1200,1000)

      for    variable = 0, 50 do
              local rand = of.random(1000)
              of.line(0, rand, 1000, rand)
       end
       of.setColor(5,0,170,55)
       for    variable = 0, 50 do
              local rand = of.random(1000)
              of.line(rand, 0, rand, 1000)
       end
]]
