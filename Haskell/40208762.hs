{-
READ ME: Change the name of this file to YOURSTUDENTNUMBER.hs. For example, if your
student number were 123456789, then you would rename the file 123456789.hs.

Fill in the function definitions for each of the questions, and uncomment them. 
The names of the functions correspond to the names given in the document cwk_15_16.pdf. 

DO NOT CHANGE THE TYPE SIGNATURES, OR THE ORDER OF THE ARGUMENTS!

You may add as many extra or helper functions as you wish, but do not make any "import" statements.
-}

-- QUESTION 1 

doubleList [] = []
doubleList (x:xs) = (fst x, fst x) : (snd x, snd x) : doubleList xs

uniqueListT :: (Eq a) => [(a,a)] -> [(a, a)]
uniqueListT [] = []
uniqueListT (x:xs)
    | elem x xs = uniqueListT xs
    | otherwise = x : uniqueListT xs

isReflexive' _ [] = True
isReflexive' xs (y:ys)
    | elem y xs = isReflexive' xs ys
    | otherwise = False

isReflexive :: (Eq a) => [(a,a)] -> Bool
isReflexive xs
    | isReflexive' xs (uniqueListT (doubleList xs)) = True
    | otherwise = False

isSymmetric' _ [] = True
isSymmetric' xs (y:ys)
    | elem (snd y, fst y) xs = isSymmetric' xs ys
    | otherwise = False

isSymmetric :: (Eq a) => [(a,a)] -> Bool
isSymmetric xs = isSymmetric' xs xs

dList' [] _ = []
dList' (x:xs) y
    | fst (x) == snd (y) = (snd (x), fst (y)) : dList' xs y
    | otherwise = dList' xs y

dList _ [] = []
dList xs (y:ys) = (dList' xs y) ++ dList xs ys

isTransitive' [] _ = True
isTransitive' (x:xs) ys
    | elem x ys = isTransitive' xs ys
    | otherwise = False

isTransitive :: (Eq a) => [(a,a)] -> Bool
isTransitive xs = isTransitive' (dList xs xs) xs

isEquivalence :: (Eq a) => [(a,a)] -> Bool
isEquivalence xs = isReflexive xs && isSymmetric xs && isTransitive xs

eqClassOf' [] _ = []
eqClassOf' (x:xs) y
    | fst x == y = (snd x) : eqClassOf' xs y
    | otherwise = eqClassOf' xs y

eqClassOf2' [] _ = []
eqClassOf2' (x:xs) y
    | snd x == y = (fst x) : eqClassOf' xs y
    | otherwise = eqClassOf' xs y

eqClassOf :: (Eq a) => [(a,a)] -> a -> [a]
eqClassOf xs y = uniqueList((eqClassOf' xs y) ++ (eqClassOf2' xs y))

uniqueList :: (Eq a) => [a] -> [a]
uniqueList [] = []
uniqueList (x:xs)
    | elem x xs = uniqueList xs
    | otherwise = x : uniqueList xs

-- TEST SET FOR Q1
{-
Your functions should have the following behaviour:
isReflexive [(1,2),(2,1),(1,1),(2,2)] is True
isReflexive [(1,2),(2,1),(2,2)] is False
isSymmetric [(1,2),(2,1),(2,2)] is True
isSymmetric [(1,2),(1,1),(2,2)] is False
isTransitive [(1,2),(2,1),(1,1),(2,2)] is True
isTransitive [(1,2),(2,3)] is False
isEquivalence [(1,2),(2,1),(1,1),(2,2)] is True
eqClassOf [(1,2),(2,1),(1,1),(2,2)] 1 is [1,2]
-}

-- QUESTION 2
muRemove [] _ = []
muRemove (x:xs) y
    | x == y = y : muRemove xs y
    | otherwise = muRemove xs y

muEq [] _ _ = True
muEq (x:xs) ys zs
    | muRemove ys x == muRemove zs x = muEq xs ys zs
    | otherwise = False

multiEqual :: (Eq a) => [a] -> [a] -> Bool
multiEqual xs ys = muEq xs xs ys

muCheck [] _ _ = []
muCheck (x:xs) ys zs
    | length (muRemove ys x) > length (muRemove zs x) = (muRemove ys x) ++ muCheck xs ys zs
    | otherwise = (muRemove zs x) ++ muCheck xs ys zs

muCheck2 [] _ _ = []
muCheck2 (x:xs) ys zs
    | length (muRemove ys x) < length (muRemove zs x) = (muRemove ys x) ++ muCheck2 xs ys zs
    | otherwise = (muRemove zs x) ++ muCheck2 xs ys zs
    
multiUnion :: (Eq a) => [a] -> [a] -> [a]
multiUnion xs ys = muCheck (uniqueList((xs ++ ys))) xs ys

multiIntersection :: (Eq a) => [a] -> [a] -> [a]
multiIntersection xs ys = muCheck2 (uniqueList((ys ++ xs))) ys xs


-- TEST SET FOR Q2
{-
Your functions should have the following behaviour:
multiEqual [1,1,2] [1,2,1] is True
multiEqual [1,1,2] [1,2] is False
multiUnion [1,1,2] [1,2,2] is [1,1,2,2]
multiIntersection [1,1,2] [1,2,2] is [1,2]
-}

-- QUESTION 3

{-
trace :: (Num a) => [[a]] -> Maybe a
-}
{-
matMult3 :: (Num a) => [[a]] -> [[a]] -> [[a]]
FIRST ARGUMENT IS A, SECOND IS B, YOU ARE TO WORK OUT AB 
-} 

-- TEST SET FOR Q3
{-
Your functions should have the following behaviour:
trace [[1,2],[6,4]] is Just 5
matMult3 [[1,0,1],[0,1,0],[0,0,1]] [[0,1,0],[1,0,1],[1,1,0]] is
[[1,2,0],[1,0,1],[1,1,0]]
-}

-- QUESTION 4

{-
triNumber :: Int -> Int -> [Int]
FIRST ARGUMENT IS ROW NUMBER, SECOND IS SEED/VALUE AT TIP OF TRIANGLE
-}

-- TEST SET FOR Q4
{-
Your function should have the following behaviour:
triNumber 3 1 is [2,3,5]
-}

-- QUESTION 5

{-
combine :: Int -> Int -> (Int, Int, Int)
-}

-- TEST SET FOR Q5
{-
Your function should have the following behaviour:
combine 3(n) 2(m) is (1(a),-1(b),1(gcd(n,m)))
am + bn = gcd(n,m)
-}


