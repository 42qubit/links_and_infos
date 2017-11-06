module Main where

import System.Environment (getArgs) -- fetch the command line arguments
import Prelude



quicksort :: (Ord a) => [a] -> [a]
quicksort [] = []
quicksort (x:xs) =
    let smallerSorted = quicksort [e | e <- xs, e <= x]
        biggerSorted  = quicksort [e | e <- xs, e > x]
    in  smallerSorted ++ [x] ++ biggerSorted


-- main function, that will be called upon start of the execuable
main = do
  -- args <- getArgs          -- black magic
  -- let x = read (head args) -- black magic
  let result = quicksort "Alle meine Entchen, schwimmen auf dem See"       -- compute result
  print result             -- output result
