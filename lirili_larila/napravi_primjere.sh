#!/bin/bash

zadatak="./test/lirili_larila"

cls=1

./gen 300 10  SMALL_CYCLES SHALLOW 	> ./test/lirili_larila.in."$cls"a
./gen 300 30  SMALL_CYCLES SHALLOW 	> ./test/lirili_larila.in."$cls"b
./gen 300 20  SMALL_CYCLES SHALLOW 	> ./test/lirili_larila.in."$cls"c

./gen 300 50  SMALL_CYCLES SHALLOW	> ./test/lirili_larila.in."$cls"d
./gen 300 100 SMALL_CYCLES SHALLOW 	> ./test/lirili_larila.in."$cls"e
./gen 300 300 SMALL_CYCLES SHALLOW 	> ./test/lirili_larila.in."$cls"f
./gen 300 50  SMALL_CYCLES DEEP	 	> ./test/lirili_larila.in."$cls"g
./gen 300 50  SMALL_CYCLES DEEP	 	> ./test/lirili_larila.in."$cls"h
./gen 300 300 SMALL_CYCLES DEEP 	> ./test/lirili_larila.in."$cls"i
./gen 300 100 SMALL_CYCLES DEEP 	> ./test/lirili_larila.in."$cls"j
./gen 300 100 SMALL_CYCLES DEEP 	> ./test/lirili_larila.in."$cls"k
./gen 300 300 SMALL_CYCLES DEEP 	> ./test/lirili_larila.in."$cls"l

./gen 300 50  LARGE_CYCLES SHALLOW 	> ./test/lirili_larila.in."$cls"m
./gen 300 100 LARGE_CYCLES SHALLOW 	> ./test/lirili_larila.in."$cls"n
./gen 300 300 LARGE_CYCLES SHALLOW 	> ./test/lirili_larila.in."$cls"o
./gen 300 50  LARGE_CYCLES DEEP 	> ./test/lirili_larila.in."$cls"p
./gen 300 50  LARGE_CYCLES DEEP 	> ./test/lirili_larila.in."$cls"q
./gen 300 100 LARGE_CYCLES DEEP 	> ./test/lirili_larila.in."$cls"r
./gen 300 100 LARGE_CYCLES DEEP 	> ./test/lirili_larila.in."$cls"s
./gen 300 300 LARGE_CYCLES DEEP		> ./test/lirili_larila.in."$cls"t
./gen 300 300 LARGE_CYCLES DEEP		> ./test/lirili_larila.in."$cls"u

./gen 300 50  SMALL_CYCLES SHALLOW	> ./test/lirili_larila.in."$cls"v
./gen 300 50  SMALL_CYCLES SHALLOW	> ./test/lirili_larila.in."$cls"w
./gen 300 50  SMALL_CYCLES SHALLOW	> ./test/lirili_larila.in."$cls"x
./gen 300 50  SMALL_CYCLES SHALLOW	> ./test/lirili_larila.in."$cls"y
./gen 300 50  SMALL_CYCLES SHALLOW	> ./test/lirili_larila.in."$cls"z

./gen 300 50 SMALL_SUN X 			> ./test/lirili_larila.in."$cls"aa
./gen 300 50 SMALL_SUN X 			> ./test/lirili_larila.in."$cls"ab
./gen 300 50 SMALL_SUN X 			> ./test/lirili_larila.in."$cls"ac
./gen 300 50 SMALL_SUN X 			> ./test/lirili_larila.in."$cls"ad
./gen 300 100 SMALL_SUN X 		> ./test/lirili_larila.in."$cls"ae
./gen 300 100 SMALL_SUN X 		> ./test/lirili_larila.in."$cls"af
./gen 300 100 SMALL_SUN X 		> ./test/lirili_larila.in."$cls"ag
./gen 300 100 SMALL_SUN X 		> ./test/lirili_larila.in."$cls"ah
./gen 300 300 SMALL_SUN X 		> ./test/lirili_larila.in."$cls"ai
./gen 300 300 SMALL_SUN X 		> ./test/lirili_larila.in."$cls"aj
./gen 300 300 SMALL_SUN X 		> ./test/lirili_larila.in."$cls"ak
./gen 300 300 SMALL_SUN X 		> ./test/lirili_larila.in."$cls"al

./gen 300 300 SPECIAL_1 X > ./test/lirili_larila.in."$cls"ak
./gen 300 300 SPECIAL_2 X > ./test/lirili_larila.in."$cls"am
./gen 300 300 SPECIAL_2 X > ./test/lirili_larila.in."$cls"an
./gen 300 300 SPECIAL_3 X > ./test/lirili_larila.in."$cls"ao
./gen 300 300 SPECIAL_4 X > ./test/lirili_larila.in."$cls"ap
./gen 300 300 SPECIAL_4 X > ./test/lirili_larila.in."$cls"aq


echo $cls

cls=2

./gen 5000 10 	TREE SHALLOW 	> ./test/lirili_larila.in."$cls"a
./gen 5000 50  	TREE SHALLOW 	> ./test/lirili_larila.in."$cls"b
./gen 5000 100  TREE SHALLOW 	> ./test/lirili_larila.in."$cls"c
./gen 5000 5000 TREE SHALLOW 	> ./test/lirili_larila.in."$cls"d

./gen 5000 10 	TREE SQRT 		> ./test/lirili_larila.in."$cls"e
./gen 5000 50  	TREE SQRT 		> ./test/lirili_larila.in."$cls"f
./gen 5000 100  TREE SQRT 		> ./test/lirili_larila.in."$cls"g
./gen 5000 5000 TREE SQRT 		> ./test/lirili_larila.in."$cls"h

./gen 5000 10 	TREE DEEP 		> ./test/lirili_larila.in."$cls"i
./gen 5000 50  	TREE DEEP 		> ./test/lirili_larila.in."$cls"j
./gen 5000 100  TREE DEEP 		> ./test/lirili_larila.in."$cls"k
./gen 5000 5000 TREE DEEP 		> ./test/lirili_larila.in."$cls"l

./gen 5000 5000 TREE CHAIN 	> ./test/lirili_larila.in."$cls"m
./gen 5000 5000 TREE CHAIN 	> ./test/lirili_larila.in."$cls"n
./gen 5000 5000 TREE CHAIN 	> ./test/lirili_larila.in."$cls"o
./gen 5000 5000 TREE CHAIN 	> ./test/lirili_larila.in."$cls"p
./gen 5000 5000 TREE CHAIN 	> ./test/lirili_larila.in."$cls"q

./gen 5000 5000 SPECIAL_1 X > ./test/lirili_larila.in."$cls"r
./gen 5000 5000 SPECIAL_2 X > ./test/lirili_larila.in."$cls"s
./gen 5000 5000 SPECIAL_2 X > ./test/lirili_larila.in."$cls"t


echo $cls

cls=3

./gen 200000 10 	TREE SHALLOW 	> ./test/lirili_larila.in."$cls"a
./gen 200000 50  	TREE SHALLOW 	> ./test/lirili_larila.in."$cls"b
./gen 200000 100  	TREE SHALLOW 	> ./test/lirili_larila.in."$cls"c
./gen 200000 5000 	TREE SHALLOW 	> ./test/lirili_larila.in."$cls"d
./gen 200000 50000 	TREE SHALLOW 	> ./test/lirili_larila.in."$cls"e
./gen 200000 200000 TREE SHALLOW 	> ./test/lirili_larila.in."$cls"f

./gen 200000 10 	TREE SQRT 		> ./test/lirili_larila.in."$cls"g
./gen 200000 50  	TREE SQRT 		> ./test/lirili_larila.in."$cls"h
./gen 200000 100 	TREE SQRT	 	> ./test/lirili_larila.in."$cls"i
./gen 200000 5000 	TREE SQRT 		> ./test/lirili_larila.in."$cls"j
./gen 200000 50000	TREE SQRT 		> ./test/lirili_larila.in."$cls"k
./gen 200000 200000 TREE SQRT 		> ./test/lirili_larila.in."$cls"l

./gen 200000 10 	TREE SQRT 		> ./test/lirili_larila.in."$cls"m
./gen 200000 50  	TREE SQRT 		> ./test/lirili_larila.in."$cls"n
./gen 200000 100  	TREE SQRT 		> ./test/lirili_larila.in."$cls"o
./gen 200000 5000 	TREE SQRT 		> ./test/lirili_larila.in."$cls"p
./gen 200000 50000 	TREE SQRT 		> ./test/lirili_larila.in."$cls"q
./gen 200000 200000 TREE SQRT 		> ./test/lirili_larila.in."$cls"r

./gen 200000 200000 SPECIAL_1 X > ./test/lirili_larila.in."$cls"s
./gen 200000 200000 SPECIAL_2 X > ./test/lirili_larila.in."$cls"t
./gen 200000 200000 SPECIAL_2 X > ./test/lirili_larila.in."$cls"u

echo $cls

cls=4

./gen 5000 10 	SMALL_SUN X 	> ./test/lirili_larila.in."$cls"a
./gen 5000 50  	SMALL_SUN X 	> ./test/lirili_larila.in."$cls"b
./gen 5000 100  SMALL_SUN X 	> ./test/lirili_larila.in."$cls"c
./gen 5000 100  SMALL_SUN X 	> ./test/lirili_larila.in."$cls"d
./gen 5000 100  SMALL_SUN X 	> ./test/lirili_larila.in."$cls"e
./gen 5000 5000 SMALL_SUN X 	> ./test/lirili_larila.in."$cls"f
./gen 5000 5000 SMALL_SUN X 	> ./test/lirili_larila.in."$cls"g
./gen 5000 5000 SMALL_SUN X 	> ./test/lirili_larila.in."$cls"h

./gen 5000 50  	LARGE_SUN X 	> ./test/lirili_larila.in."$cls"i
./gen 5000 100  LARGE_SUN X 	> ./test/lirili_larila.in."$cls"j
./gen 5000 100  LARGE_SUN X 	> ./test/lirili_larila.in."$cls"k
./gen 5000 100  LARGE_SUN X 	> ./test/lirili_larila.in."$cls"l
./gen 5000 5000 LARGE_SUN X 	> ./test/lirili_larila.in."$cls"m
./gen 5000 5000 LARGE_SUN X 	> ./test/lirili_larila.in."$cls"n
./gen 5000 5000 LARGE_SUN X 	> ./test/lirili_larila.in."$cls"o

./gen 5000 100  SIMPLE_SUN SHALLOW 	> ./test/lirili_larila.in."$cls"p
./gen 5000 100  SIMPLE_SUN DEEP 	> ./test/lirili_larila.in."$cls"r
./gen 5000 100  SIMPLE_SUN CHAIN 	> ./test/lirili_larila.in."$cls"q
./gen 5000 500  SIMPLE_SUN SHALLOW 	> ./test/lirili_larila.in."$cls"s
./gen 5000 500 	SIMPLE_SUN DEEP 	> ./test/lirili_larila.in."$cls"t
./gen 5000 500 	SIMPLE_SUN CHAIN 	> ./test/lirili_larila.in."$cls"u
./gen 5000 5000 SIMPLE_SUN SHALLOW 	> ./test/lirili_larila.in."$cls"v
./gen 5000 5000 SIMPLE_SUN DEEP 	> ./test/lirili_larila.in."$cls"w
./gen 5000 5000 SIMPLE_SUN CHAIN 	> ./test/lirili_larila.in."$cls"x

./gen 5000 100 SMALL_SUN X 			> ./test/lirili_larila.in."$cls"y
./gen 5000 100 SMALL_SUN X 			> ./test/lirili_larila.in."$cls"z
./gen 5000 5000 SMALL_SUN X 		> ./test/lirili_larila.in."$cls"aa
./gen 5000 5000 SMALL_SUN X 		> ./test/lirili_larila.in."$cls"ab

./gen 5000 5000 SPECIAL_3 X > ./test/lirili_larila.in."$cls"ac
./gen 5000 5000 SPECIAL_4 X > ./test/lirili_larila.in."$cls"ad
./gen 5000 5000 SPECIAL_4 X > ./test/lirili_larila.in."$cls"ae


echo $cls

cls=5

./gen 200000 50 	SMALL_SUN Y 	> ./test/lirili_larila.in."$cls"a
./gen 200000 50  	SMALL_SUN Y 	> ./test/lirili_larila.in."$cls"b
./gen 200000 100  	SMALL_SUN Y 	> ./test/lirili_larila.in."$cls"c
./gen 200000 5000  	SMALL_SUN Y 	> ./test/lirili_larila.in."$cls"d
./gen 200000 50000  SMALL_SUN Y 	> ./test/lirili_larila.in."$cls"e
./gen 200000 50000 	SMALL_SUN Y 	> ./test/lirili_larila.in."$cls"f
./gen 200000 200000 SMALL_SUN Y 	> ./test/lirili_larila.in."$cls"g
./gen 200000 200000 SMALL_SUN Y 	> ./test/lirili_larila.in."$cls"h

./gen 200000 50 	LARGE_SUN Y 	> ./test/lirili_larila.in."$cls"i
./gen 200000 50  	LARGE_SUN Y 	> ./test/lirili_larila.in."$cls"j
./gen 200000 100  	LARGE_SUN Y 	> ./test/lirili_larila.in."$cls"k
./gen 200000 5000  	LARGE_SUN Y 	> ./test/lirili_larila.in."$cls"l
./gen 200000 50000  LARGE_SUN Y 	> ./test/lirili_larila.in."$cls"m
./gen 200000 50000 	LARGE_SUN Y 	> ./test/lirili_larila.in."$cls"n
./gen 200000 200000 LARGE_SUN Y 	> ./test/lirili_larila.in."$cls"o
./gen 200000 200000 LARGE_SUN Y 	> ./test/lirili_larila.in."$cls"p

./gen 200000 5000  	Y_SIMPLE_SUN SHALLOW 	> ./test/lirili_larila.in."$cls"q
./gen 200000 5000  	Y_SIMPLE_SUN DEEP 	> ./test/lirili_larila.in."$cls"r
./gen 200000 5000  	Y_SIMPLE_SUN CHAIN 	> ./test/lirili_larila.in."$cls"s
./gen 200000 50000  Y_SIMPLE_SUN SHALLOW 	> ./test/lirili_larila.in."$cls"t
./gen 200000 50000 	Y_SIMPLE_SUN DEEP 	> ./test/lirili_larila.in."$cls"u
./gen 200000 50000 	Y_SIMPLE_SUN CHAIN 	> ./test/lirili_larila.in."$cls"v
./gen 200000 200000 Y_SIMPLE_SUN SHALLOW 	> ./test/lirili_larila.in."$cls"w
./gen 200000 200000 Y_SIMPLE_SUN DEEP 	> ./test/lirili_larila.in."$cls"x
./gen 200000 200000 Y_SIMPLE_SUN CHAIN 	> ./test/lirili_larila.in."$cls"y

./gen 200000 100	SMALL_SUN Y 			> ./test/lirili_larila.in."$cls"z
./gen 200000 100 	SMALL_SUN Y 			> ./test/lirili_larila.in."$cls"aa
./gen 200000 5000 	SMALL_SUN Y 			> ./test/lirili_larila.in."$cls"ab
./gen 200000 5000 	SMALL_SUN Y 			> ./test/lirili_larila.in."$cls"ac

echo $cls

cls=6

./gen 200000 50 	SMALL_SUN X 	> ./test/lirili_larila.in."$cls"a
./gen 200000 50  	SMALL_SUN X 	> ./test/lirili_larila.in."$cls"b
./gen 200000 100  	SMALL_SUN X 	> ./test/lirili_larila.in."$cls"c
./gen 200000 5000  	SMALL_SUN X 	> ./test/lirili_larila.in."$cls"d
./gen 200000 50000  SMALL_SUN X 	> ./test/lirili_larila.in."$cls"e
./gen 200000 50000 	SMALL_SUN X 	> ./test/lirili_larila.in."$cls"f
./gen 200000 200000 SMALL_SUN X 	> ./test/lirili_larila.in."$cls"g
./gen 200000 200000 SMALL_SUN X 	> ./test/lirili_larila.in."$cls"h

./gen 200000 50 	LARGE_SUN X 	> ./test/lirili_larila.in."$cls"i
./gen 200000 50  	LARGE_SUN X 	> ./test/lirili_larila.in."$cls"j
./gen 200000 100  	LARGE_SUN X 	> ./test/lirili_larila.in."$cls"k
./gen 200000 5000  	LARGE_SUN X 	> ./test/lirili_larila.in."$cls"l
./gen 200000 50000  LARGE_SUN X 	> ./test/lirili_larila.in."$cls"m
./gen 200000 50000 	LARGE_SUN X 	> ./test/lirili_larila.in."$cls"n
./gen 200000 200000 LARGE_SUN X 	> ./test/lirili_larila.in."$cls"o
./gen 200000 200000 LARGE_SUN X 	> ./test/lirili_larila.in."$cls"p

./gen 200000 5000  	SIMPLE_SUN SHALLOW 	> ./test/lirili_larila.in."$cls"q
./gen 200000 5000  	SIMPLE_SUN DEEP 	> ./test/lirili_larila.in."$cls"r
./gen 200000 5000  	SIMPLE_SUN CHAIN 	> ./test/lirili_larila.in."$cls"s
./gen 200000 50000  SIMPLE_SUN SHALLOW 	> ./test/lirili_larila.in."$cls"t
./gen 200000 50000 	SIMPLE_SUN DEEP 	> ./test/lirili_larila.in."$cls"u
./gen 200000 50000 	SIMPLE_SUN CHAIN 	> ./test/lirili_larila.in."$cls"v
./gen 200000 200000 SIMPLE_SUN SHALLOW 	> ./test/lirili_larila.in."$cls"w
./gen 200000 200000 SIMPLE_SUN DEEP 	> ./test/lirili_larila.in."$cls"x
./gen 200000 200000 SIMPLE_SUN CHAIN 	> ./test/lirili_larila.in."$cls"y

./gen 200000 100 SMALL_SUN X 			> ./test/lirili_larila.in."$cls"z
./gen 200000 100 SMALL_SUN X 			> ./test/lirili_larila.in."$cls"aa
./gen 200000 5000 SMALL_SUN X 			> ./test/lirili_larila.in."$cls"ab
./gen 200000 5000 SMALL_SUN X 			> ./test/lirili_larila.in."$cls"ac

./gen 5000 5000 SPECIAL_3 X > ./test/lirili_larila.in."$cls"ad
./gen 5000 5000 SPECIAL_4 X > ./test/lirili_larila.in."$cls"ae
./gen 5000 5000 SPECIAL_4 X > ./test/lirili_larila.in."$cls"af

echo $cls

cls=7

./gen 5000 10 	SMALL_CYCLES SHALLOW 	> ./test/lirili_larila.in."$cls"a
./gen 5000 50 	SMALL_CYCLES SHALLOW 	> ./test/lirili_larila.in."$cls"b
./gen 5000 50 	SMALL_CYCLES SHALLOW 	> ./test/lirili_larila.in."$cls"c
./gen 5000 200 	SMALL_CYCLES SHALLOW 	> ./test/lirili_larila.in."$cls"d
./gen 5000 5000 SMALL_CYCLES SHALLOW 	> ./test/lirili_larila.in."$cls"e
./gen 5000 200 	SMALL_CYCLES DEEP 	> ./test/lirili_larila.in."$cls"f
./gen 5000 5000 SMALL_CYCLES DEEP 	> ./test/lirili_larila.in."$cls"g
./gen 5000 200 	SMALL_CYCLES SQRT 	> ./test/lirili_larila.in."$cls"h
./gen 5000 5000 SMALL_CYCLES SQRT 	> ./test/lirili_larila.in."$cls"i
./gen 5000 200 	SMALL_CYCLES CHAIN 	> ./test/lirili_larila.in."$cls"j
./gen 5000 5000 SMALL_CYCLES CHAIN 	> ./test/lirili_larila.in."$cls"k

./gen 5000 10 	LARGE_CYCLES SHALLOW 	> ./test/lirili_larila.in."$cls"l
./gen 5000 50 	LARGE_CYCLES SHALLOW 	> ./test/lirili_larila.in."$cls"m
./gen 5000 50 	LARGE_CYCLES SHALLOW 	> ./test/lirili_larila.in."$cls"n
./gen 5000 200 	LARGE_CYCLES SHALLOW 	> ./test/lirili_larila.in."$cls"o
./gen 5000 5000 LARGE_CYCLES SHALLOW 	> ./test/lirili_larila.in."$cls"p
./gen 5000 200 	LARGE_CYCLES DEEP 	> ./test/lirili_larila.in."$cls"q
./gen 5000 5000 LARGE_CYCLES DEEP 	> ./test/lirili_larila.in."$cls"r
./gen 5000 200 	LARGE_CYCLES SQRT 	> ./test/lirili_larila.in."$cls"s
./gen 5000 5000 LARGE_CYCLES SQRT 	> ./test/lirili_larila.in."$cls"t
./gen 5000 200 	LARGE_CYCLES CHAIN 	> ./test/lirili_larila.in."$cls"u
./gen 5000 5000 LARGE_CYCLES CHAIN 	> ./test/lirili_larila.in."$cls"v

./gen 5000 50 	LARGE_CYCLES_WITH_SPACE SHALLOW 	> ./test/lirili_larila.in."$cls"w
./gen 5000 50 	LARGE_CYCLES_WITH_SPACE SHALLOW 	> ./test/lirili_larila.in."$cls"x
./gen 5000 50 	LARGE_CYCLES_WITH_SPACE SHALLOW 	> ./test/lirili_larila.in."$cls"y
./gen 5000 200 	LARGE_CYCLES_WITH_SPACE SHALLOW 	> ./test/lirili_larila.in."$cls"z
./gen 5000 5000 LARGE_CYCLES_WITH_SPACE SHALLOW 	> ./test/lirili_larila.in."$cls"aa
./gen 5000 200 	LARGE_CYCLES_WITH_SPACE DEEP 	> ./test/lirili_larila.in."$cls"ab
./gen 5000 5000 LARGE_CYCLES_WITH_SPACE DEEP 	> ./test/lirili_larila.in."$cls"ac
./gen 5000 200 	LARGE_CYCLES_WITH_SPACE SQRT 	> ./test/lirili_larila.in."$cls"ad
./gen 5000 5000 LARGE_CYCLES_WITH_SPACE SQRT 	> ./test/lirili_larila.in."$cls"ae
./gen 5000 200 	LARGE_CYCLES_WITH_SPACE CHAIN 	> ./test/lirili_larila.in."$cls"af
./gen 5000 5000 LARGE_CYCLES_WITH_SPACE CHAIN 	> ./test/lirili_larila.in."$cls"ag

./gen 5000 200 	ONE_LARGE_CYCLE SHALLOW 	> ./test/lirili_larila.in."$cls"ah
./gen 5000 5000 ONE_LARGE_CYCLE SHALLOW 	> ./test/lirili_larila.in."$cls"ai
./gen 5000 200 	ONE_LARGE_CYCLE DEEP 	> ./test/lirili_larila.in."$cls"aj
./gen 5000 5000 ONE_LARGE_CYCLE DEEP 	> ./test/lirili_larila.in."$cls"ak
./gen 5000 200 	ONE_LARGE_CYCLE SQRT 	> ./test/lirili_larila.in."$cls"al
./gen 5000 5000 ONE_LARGE_CYCLE SQRT 	> ./test/lirili_larila.in."$cls"am
./gen 5000 200 	ONE_LARGE_CYCLE CHAIN 	> ./test/lirili_larila.in."$cls"an
./gen 5000 5000 ONE_LARGE_CYCLE CHAIN 	> ./test/lirili_larila.in."$cls"ao

./gen 5000 50 SMALL_SUN X 			> ./test/lirili_larila.in."$cls"ap
./gen 5000 100 SMALL_SUN X 			> ./test/lirili_larila.in."$cls"aq
./gen 5000 100 SMALL_SUN X 			> ./test/lirili_larila.in."$cls"aq
./gen 5000 100 SMALL_SUN X 			> ./test/lirili_larila.in."$cls"ar
./gen 5000 500 SMALL_SUN X 			> ./test/lirili_larila.in."$cls"as
./gen 5000 5000 SMALL_SUN X 			> ./test/lirili_larila.in."$cls"at
./gen 5000 5000 SMALL_SUN X 			> ./test/lirili_larila.in."$cls"au
./gen 5000 5000 SMALL_SUN X 			> ./test/lirili_larila.in."$cls"av

./gen 5000 10 	SMALL_CYCLES SHALLOW 	> ./test/lirili_larila.in."$cls"aw
./gen 5000 10 	SMALL_CYCLES SHALLOW 	> ./test/lirili_larila.in."$cls"ax
./gen 5000 10 	SMALL_CYCLES SHALLOW 	> ./test/lirili_larila.in."$cls"ay
./gen 5000 10 	SMALL_CYCLES SHALLOW 	> ./test/lirili_larila.in."$cls"az

./gen 5000 5000 SPECIAL_1 X > ./test/lirili_larila.in."$cls"ba
./gen 5000 5000 SPECIAL_2 X > ./test/lirili_larila.in."$cls"bb
./gen 5000 5000 SPECIAL_2 X > ./test/lirili_larila.in."$cls"bc
./gen 5000 5000 SPECIAL_3 X > ./test/lirili_larila.in."$cls"bd
./gen 5000 5000 SPECIAL_4 X > ./test/lirili_larila.in."$cls"be
./gen 5000 5000 SPECIAL_4 X > ./test/lirili_larila.in."$cls"bf


echo $cls

cls=8

./gen 200000 10 	SMALL_CYCLES SHALLOW 	> ./test/lirili_larila.in."$cls"a
./gen 200000 50 	SMALL_CYCLES SHALLOW 	> ./test/lirili_larila.in."$cls"b
./gen 200000 50 	SMALL_CYCLES SHALLOW 	> ./test/lirili_larila.in."$cls"c
./gen 200000 200 	SMALL_CYCLES SHALLOW 	> ./test/lirili_larila.in."$cls"d
./gen 200000 5000 	SMALL_CYCLES SHALLOW 	> ./test/lirili_larila.in."$cls"e
./gen 200000 200 	SMALL_CYCLES DEEP 	> ./test/lirili_larila.in."$cls"f
./gen 200000 5000 	SMALL_CYCLES DEEP 	> ./test/lirili_larila.in."$cls"g
./gen 200000 200 	SMALL_CYCLES SQRT 	> ./test/lirili_larila.in."$cls"h
./gen 200000 5000 	SMALL_CYCLES SQRT 	> ./test/lirili_larila.in."$cls"i
./gen 200000 200 	SMALL_CYCLES CHAIN 	> ./test/lirili_larila.in."$cls"j
./gen 200000 5000 	SMALL_CYCLES CHAIN 	> ./test/lirili_larila.in."$cls"k

./gen 200000 10 	LARGE_CYCLES SHALLOW 	> ./test/lirili_larila.in."$cls"l
./gen 200000 50 	LARGE_CYCLES SHALLOW 	> ./test/lirili_larila.in."$cls"m
./gen 200000 50 	LARGE_CYCLES SHALLOW 	> ./test/lirili_larila.in."$cls"n
./gen 200000 200 	LARGE_CYCLES SHALLOW 	> ./test/lirili_larila.in."$cls"o
./gen 200000 5000	LARGE_CYCLES SHALLOW 	> ./test/lirili_larila.in."$cls"p
./gen 200000 200 	LARGE_CYCLES DEEP 		> ./test/lirili_larila.in."$cls"q
./gen 200000 5000	LARGE_CYCLES DEEP 		> ./test/lirili_larila.in."$cls"r
./gen 200000 200 	LARGE_CYCLES SQRT	 	> ./test/lirili_larila.in."$cls"s
./gen 200000 5000	LARGE_CYCLES SQRT 		> ./test/lirili_larila.in."$cls"t
./gen 200000 200 	LARGE_CYCLES CHAIN 		> ./test/lirili_larila.in."$cls"u
./gen 200000 5000	LARGE_CYCLES CHAIN 		> ./test/lirili_larila.in."$cls"v

./gen 200000 50 	LARGE_CYCLES_WITH_SPACE SHALLOW 	> ./test/lirili_larila.in."$cls"w
./gen 200000 50 	LARGE_CYCLES_WITH_SPACE SHALLOW 	> ./test/lirili_larila.in."$cls"x
./gen 200000 50 	LARGE_CYCLES_WITH_SPACE SHALLOW 	> ./test/lirili_larila.in."$cls"y
./gen 200000 200 	LARGE_CYCLES_WITH_SPACE SHALLOW 	> ./test/lirili_larila.in."$cls"z
./gen 200000 5000	LARGE_CYCLES_WITH_SPACE SHALLOW 	> ./test/lirili_larila.in."$cls"aa
./gen 200000 200 	LARGE_CYCLES_WITH_SPACE DEEP 		> ./test/lirili_larila.in."$cls"ab
./gen 200000 5000 	LARGE_CYCLES_WITH_SPACE DEEP 		> ./test/lirili_larila.in."$cls"ac
./gen 200000 200 	LARGE_CYCLES_WITH_SPACE SQRT 		> ./test/lirili_larila.in."$cls"ad
./gen 200000 5000 	LARGE_CYCLES_WITH_SPACE SQRT 		> ./test/lirili_larila.in."$cls"ae
./gen 200000 200 	LARGE_CYCLES_WITH_SPACE CHAIN 		> ./test/lirili_larila.in."$cls"af
./gen 200000 5000 	LARGE_CYCLES_WITH_SPACE CHAIN 		> ./test/lirili_larila.in."$cls"ag

./gen 200000 200 	ONE_LARGE_CYCLE SHALLOW 			> ./test/lirili_larila.in."$cls"ah
./gen 200000 5000 	ONE_LARGE_CYCLE SHALLOW 			> ./test/lirili_larila.in."$cls"ai
./gen 200000 200 	ONE_LARGE_CYCLE DEEP 				> ./test/lirili_larila.in."$cls"aj
./gen 200000 5000	ONE_LARGE_CYCLE DEEP 				> ./test/lirili_larila.in."$cls"ak
./gen 200000 200 	ONE_LARGE_CYCLE SQRT 				> ./test/lirili_larila.in."$cls"al
./gen 200000 5000	ONE_LARGE_CYCLE SQRT 				> ./test/lirili_larila.in."$cls"am
./gen 200000 200 	ONE_LARGE_CYCLE CHAIN 				> ./test/lirili_larila.in."$cls"an
./gen 200000 5000	ONE_LARGE_CYCLE CHAIN 				> ./test/lirili_larila.in."$cls"ao

./gen 200000 50000	SMALL_CYCLES SHALLOW 				> ./test/lirili_larila.in."$cls"ap
./gen 200000 50000	SMALL_CYCLES SHALLOW 				> ./test/lirili_larila.in."$cls"aq
./gen 200000 200000	SMALL_CYCLES SHALLOW 				> ./test/lirili_larila.in."$cls"ar
./gen 200000 200000	SMALL_CYCLES SHALLOW 				> ./test/lirili_larila.in."$cls"as
./gen 200000 50000	SMALL_CYCLES SQRT 				> ./test/lirili_larila.in."$cls"at
./gen 200000 50000	SMALL_CYCLES SQRT 				> ./test/lirili_larila.in."$cls"au
./gen 200000 200000	SMALL_CYCLES SQRT 				> ./test/lirili_larila.in."$cls"av
./gen 200000 200000	SMALL_CYCLES SQRT 				> ./test/lirili_larila.in."$cls"aw
./gen 200000 50000	SMALL_CYCLES DEEP 				> ./test/lirili_larila.in."$cls"ax
./gen 200000 50000	SMALL_CYCLES DEEP 				> ./test/lirili_larila.in."$cls"ay
./gen 200000 200000	SMALL_CYCLES DEEP 				> ./test/lirili_larila.in."$cls"az
./gen 200000 200000	SMALL_CYCLES DEEP 				> ./test/lirili_larila.in."$cls"ba
./gen 200000 50000	SMALL_CYCLES CHAIN 				> ./test/lirili_larila.in."$cls"bb
./gen 200000 50000	SMALL_CYCLES CHAIN				> ./test/lirili_larila.in."$cls"bc
./gen 200000 200000	SMALL_CYCLES CHAIN 				> ./test/lirili_larila.in."$cls"bd
./gen 200000 200000	SMALL_CYCLES CHAIN 				> ./test/lirili_larila.in."$cls"be

./gen 200000 50000	ONE_LARGE_CYCLE SHALLOW 				> ./test/lirili_larila.in."$cls"bf
./gen 200000 50000	ONE_LARGE_CYCLE SHALLOW 				> ./test/lirili_larila.in."$cls"bg
./gen 200000 200000	ONE_LARGE_CYCLE SHALLOW 				> ./test/lirili_larila.in."$cls"bh
./gen 200000 200000	ONE_LARGE_CYCLE SHALLOW 				> ./test/lirili_larila.in."$cls"bi
./gen 200000 50000	ONE_LARGE_CYCLE SQRT 				> ./test/lirili_larila.in."$cls"bj
./gen 200000 50000	ONE_LARGE_CYCLE SQRT 				> ./test/lirili_larila.in."$cls"bk
./gen 200000 200000	ONE_LARGE_CYCLE SQRT 				> ./test/lirili_larila.in."$cls"bl
./gen 200000 200000	ONE_LARGE_CYCLE SQRT 				> ./test/lirili_larila.in."$cls"bm
./gen 200000 50000	ONE_LARGE_CYCLE DEEP 				> ./test/lirili_larila.in."$cls"bn
./gen 200000 50000	ONE_LARGE_CYCLE DEEP 				> ./test/lirili_larila.in."$cls"bo
./gen 200000 200000	ONE_LARGE_CYCLE DEEP 				> ./test/lirili_larila.in."$cls"bp
./gen 200000 200000	ONE_LARGE_CYCLE DEEP 				> ./test/lirili_larila.in."$cls"bq
./gen 200000 50000	ONE_LARGE_CYCLE CHAIN 				> ./test/lirili_larila.in."$cls"br
./gen 200000 50000	ONE_LARGE_CYCLE CHAIN				> ./test/lirili_larila.in."$cls"bs
./gen 200000 200000	ONE_LARGE_CYCLE CHAIN 				> ./test/lirili_larila.in."$cls"bt
./gen 200000 200000	ONE_LARGE_CYCLE CHAIN 				> ./test/lirili_larila.in."$cls"bu

./gen 200000 50000	LARGE_CYCLES_WITH_SPACE SHALLOW 				> ./test/lirili_larila.in."$cls"bv
./gen 200000 50000	LARGE_CYCLES_WITH_SPACE SHALLOW 				> ./test/lirili_larila.in."$cls"bw
./gen 200000 200000	LARGE_CYCLES_WITH_SPACE SHALLOW 				> ./test/lirili_larila.in."$cls"bx
./gen 200000 200000	LARGE_CYCLES_WITH_SPACE SHALLOW 				> ./test/lirili_larila.in."$cls"by
./gen 200000 50000	LARGE_CYCLES_WITH_SPACE SQRT 				> ./test/lirili_larila.in."$cls"bz
./gen 200000 50000	LARGE_CYCLES_WITH_SPACE SQRT 				> ./test/lirili_larila.in."$cls"ca
./gen 200000 200000	LARGE_CYCLES_WITH_SPACE SQRT 				> ./test/lirili_larila.in."$cls"cb
./gen 200000 200000	LARGE_CYCLES_WITH_SPACE SQRT 				> ./test/lirili_larila.in."$cls"cc
./gen 200000 50000	LARGE_CYCLES_WITH_SPACE DEEP 				> ./test/lirili_larila.in."$cls"cd
./gen 200000 50000	LARGE_CYCLES_WITH_SPACE DEEP 				> ./test/lirili_larila.in."$cls"ce
./gen 200000 200000	LARGE_CYCLES_WITH_SPACE DEEP 				> ./test/lirili_larila.in."$cls"cf
./gen 200000 200000	LARGE_CYCLES_WITH_SPACE DEEP 				> ./test/lirili_larila.in."$cls"cg
./gen 200000 50000	LARGE_CYCLES_WITH_SPACE CHAIN 				> ./test/lirili_larila.in."$cls"ch
./gen 200000 50000	LARGE_CYCLES_WITH_SPACE CHAIN				> ./test/lirili_larila.in."$cls"ci
./gen 200000 200000	LARGE_CYCLES_WITH_SPACE CHAIN 				> ./test/lirili_larila.in."$cls"cj
./gen 200000 200000	LARGE_CYCLES_WITH_SPACE CHAIN 				> ./test/lirili_larila.in."$cls"ck

./gen 200000 100 	SMALL_SUN X 			> ./test/lirili_larila.in."$cls"cl
./gen 200000 100 	SMALL_SUN X 			> ./test/lirili_larila.in."$cls"cm
./gen 200000 100 	SMALL_SUN X 			> ./test/lirili_larila.in."$cls"cn
./gen 200000 5000 	SMALL_SUN X 			> ./test/lirili_larila.in."$cls"co
./gen 200000 5000 	SMALL_SUN X 			> ./test/lirili_larila.in."$cls"cp
./gen 200000 5000 	SMALL_SUN X 			> ./test/lirili_larila.in."$cls"cq
./gen 200000 200000 SMALL_SUN X 			> ./test/lirili_larila.in."$cls"cr
./gen 200000 200000 SMALL_SUN X 			> ./test/lirili_larila.in."$cls"cs

./gen 200000 10 	SMALL_CYCLES SHALLOW 	> ./test/lirili_larila.in."$cls"ct
./gen 200000 10 	SMALL_CYCLES SHALLOW 	> ./test/lirili_larila.in."$cls"cu
./gen 200000 10 	SMALL_CYCLES SHALLOW 	> ./test/lirili_larila.in."$cls"cv

./gen 200000 200000 SPECIAL_1 X > ./test/lirili_larila.in."$cls"cw
./gen 200000 200000 SPECIAL_2 X > ./test/lirili_larila.in."$cls"cx
./gen 200000 200000 SPECIAL_2 X > ./test/lirili_larila.in."$cls"cy
./gen 200000 200000 SPECIAL_3 X > ./test/lirili_larila.in."$cls"cz
./gen 200000 200000 SPECIAL_4 X > ./test/lirili_larila.in."$cls"da
./gen 200000 200000 SPECIAL_4 X > ./test/lirili_larila.in."$cls"db


echo $cls


for f in test/*.in*;
do
  echo $f
  output=$(echo $f | sed 's/in/out/g') 
  ./pavic < $f > $output
  ./checker $f $output $output
done
