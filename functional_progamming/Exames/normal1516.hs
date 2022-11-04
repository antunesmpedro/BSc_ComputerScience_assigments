--Exame 15/16
1
a) [6,9]
b) ["abc","","dce"]
c) 4
d) [1,5,9,13,17]
e) [False, False, True, True, True]
f) True
g) [[(-1)^x)*x | x <- [2..11]]
h) -6
i) [Int] -> [Int]
j) ?
k) E a -> (a -> a -> a) -> a
l) [a] -> Int -> a
--2a
somavalor :: [Int] -> Int -> [Int]
somavalor [] x = []
somavalor l x = map (+x) l
 
--2b
maiorque :: Int -> [Int] -> Bool
maiorque x xs = and(map (<x) xs)
 
--3a
matid :: Int -> [[Int]]
matid n = [[if x == y then 1 else 0 | y <- [1..n]] | x <- [1..n]]
 
simetrica :: [[Int]] -> Bool
simetrica xs = and[(xs!!x)!!y == (xs!!y)!!x | x <- [0..n-1] , y <- [0..n-1]] where
           n = length xs
 
--4a
strings :: [String]
strings = "":[c : s | s <- strings, c <- ['a'..'z']]
 
--4b
menores :: Int -> [String]
menores n = take (quantos (n-1)) strings
 
quantos :: Int -> Int
quantos 0 = 1
quantos n = (26^n) + quantos (n-1)
 
--5a
data Arv a = Folha a | No (Arv a) (Arv a)
 
soma :: Arv Int -> Int
soma (Folha x) = x
soma (No esq dir) = soma esq + soma dir
 
listar :: Arv a -> [a]
listar (Folha x) = [x]
listar (No esq dir) = (listar esq) ++ (listar dir)