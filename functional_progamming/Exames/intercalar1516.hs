-- 1
-- a) [2,3,1,4,4]
-- b) [0, 10, 20, 30, 40]
-- c) [[],[3,4],[5]]
-- d) 5
-- e) [1,1,1,1,1,1]
-- f) [(1,4), (2,3), (3,2)]
-- g) [2^x | x<-[0..6]]
-- h) 0
-- i) [(Bool, Int)]
-- j) troca:: (a,b) -> (b,a)
-- k) g:: Int -> Int -> Int
-- l) [([a], a)]

-- 2
-- a)
ttriangulo:: Eq a => a -> a -> a -> String
ttriangulo x y z | x==y && x==z && y==z = "equilatero"
                 | x==y || x==z || y==z = "isosceles"
                 | otherwise = "escaleno"

-- b)
rectangulo:: Float -> Float -> Float -> Bool
rectangulo x y z = if ((x^2+y^2==z^2) || (x^2+z^2==y^2) || (y^2+z^2==x^2)) then True else False

-- 3
maiores:: Ord a => [a] -> [a]
maiores [] = []
maiores (x:[]) = []
maiores (x:y:xs) = if x>y then x:maiores (y:xs) else maiores (y:xs)

-- 4
-- a)
somapares:: Num a => [(a,a)] -> [a]
somapares [] = []
somapares ((x,y):xs) = (x+y):somapares xs

-- b)
somapares2:: Num a => [(a,a)] -> [a]
somapares2 xs = [x+y | (x,y)<-xs]

-- 5
-- a)
itera:: Int -> (Int -> Int) -> Int -> Int
itera 0 f v = 0
itera 1 f v = f v
itera n f v = f (itera (n-1) f v)

-- b)
mult:: Int -> Int -> Int
mult x y = itera x (+y) 0