--1
--a) [[],[5,2]]
--b) [1,4,7,10]
--c) 11
--d) [0,3,6,9]
--e) [1,3,5,7,2]
--f) [(1,3),(2,2)]
--g) [3*x +1 | x<-[0,1.10]]
--h) 60
--i) [a] -> a
--j) [[Int] -> Int]
--k) N -> Int
--l) Ord a => a -> [a] -> [Bool]

--2
--a
maioresQ :: [Int] -> Int -> [Int]
maioresQ l x = filter (>x) l
--ou, [y | y <- l, y> x]

--b
tamanhoS :: [String] -> [Int]
tamanhoS xs = map length xs
--ou, [length l | l <- ls]

--3
--a
timesMat :: [[Int]] -> [[Int]] -> [[Int]]
timesMat l1 l2 = [[if any (==1) (zipWith (*) l1!!l (map (!!c) l2))then 1 else 0 |c <-[0..n]] | l<- [0..n]]
		where n = length l1 -1

--b
transitiva :: [[Int]] -> Bool
transitiva l = menor (timesMat l l) l
		where menor l1 l2 = [l1 !!x!!y <= l2 !!x!!y |x <- [0..length l1-1],y<-[0..length l2-1]]

--4
tabuada:: IO()
tabuada = do n<-getLine
            Sequence [ putStrLn (show x*read n) | x<-[0..10]]

--5
inff = [div (x*(x+1)) 2 | x<-[0,1..]]		

--6
--a
data Arv a = Vazia | No a (Arv a) (Arv a)

listar :: Arv a -> [a]
listar Vazia = []
listar (No n Vazia Vazia) = [n]
listar (No n esq dir) = listar esq ++ [n] ++ listar dir

--b

simetrica :: Arv a -> Arv a
simetrica Vazia = Vazia
simetrica (No n esq dir) = No n (simetrica dir) (simetrica esq)