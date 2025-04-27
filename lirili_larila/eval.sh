#!/bin/bash

for f in test/*.in.$2*;
do
  ./$1 < $f > tmp
  ./checker $f tmp tmp > out
  printf $f
  printf " "
  tail -n 1 out
done
