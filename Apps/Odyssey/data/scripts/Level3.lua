playerStartX = 128
playerStartY = 3072
 
 

 
 botTypes = {
 
 
MAGE_BOSS = {bot1={x=2240,y=2240}}				
 --RANGE_BOT = {bot1={x=40,y=50},bot2={x=140,y=150}}
 
 }


function getBotType(type)
return type
end

function getBotX(x)
return x
end

function getBotY(y)
return y
end
 
 function processBot(type,y,x)
 	--print(type)
 	--print(y)
 	--print(x)
	getBotType(type)
	getBotX(y)
	getBotY(x)
 	end
	
	function getAllBots()
 for k, v in pairs(botTypes) do 
 	--print(k) 
 	for t,z in pairs(v) do
 		--print(t)
 
 			processBot(k,z.x,z.y)
 		end
 end
 end