module Main where

g :: Int -> Int
g x = x * 2

f :: Int -> Int
f x = g x + 1

main :: IO ()
main = print (f 5)
