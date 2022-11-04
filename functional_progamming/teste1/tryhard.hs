-- teste 1 

--exercicio 2


ttriangulo :: Eq a => a -> a -> a -> String
ttriangulo a b c 	| a==b && b==c = "equilátero"
					| a/=b && b/=c = "escaleno"
					| otherwise  = "isósceles"


rectangulo :: Int -> Int -> Int -> Bool
rectangulo a b c	| a^2 == b^2 + c^2 = True
					| b^2 == a^2 + c^2 = True
					| c^2 == a^2 + b^2 = True
					| otherwise = False 


-- exercicio 3
maiores :: Ord a => [a] -> [a] 
maiores [x] = []
maiores (x:y:xs)	| x > y = x : maiores (y:xs)
					| otherwise = maiores (y:xs)


-- exercicio 4

somapares :: Num a => [(a,a)] -> [a]
somapares [] = []
somapares ((x,y):xs) = (x+y) : somapares xs


somapares2 :: Num a => [(a,a)] -> [a]
somapares2 l = [(x+y) | (x,y) <- l]

--exercicio 5

