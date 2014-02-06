-- Aris Bezas 6:22 PM Apr 22, 2013

midi = of.midi()

----------------------------------------------------
function setup()
         midi:setup()
end
----------------------------------------------------
function update()
         midi:update()
end
----------------------------------------------------
function draw()
         of.fill()
         of.setColor(225,200,230,120)
         of.rect(0,0,midi:map(1, 0,400),midi:map(2, 200,700))
end
----------------------------------------------------
function exit()
end
