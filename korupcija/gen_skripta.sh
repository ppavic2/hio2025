rm test/*

#dummy tests
./gen 1 1 > test/korupcija.dummy.in.1
./gen 1 2 > test/korupcija.dummy.in.2
./gen 1 3 > test/korupcija.dummy.in.3

./gen 6 4 1   > test/korupcija.in.1a
./gen 10 2 1  > test/korupcija.in.1b
./gen 10 2 2  > test/korupcija.in.1c
./gen 10 3 1  > test/korupcija.in.1d
./gen 10 3 2  > test/korupcija.in.1e
./gen 10 3 3  > test/korupcija.in.1f
./gen 10 3 4  > test/korupcija.in.1g
./gen 10 3 5  > test/korupcija.in.1h
./gen 10 3 6  > test/korupcija.in.1i
./gen 10 4 2  > test/korupcija.in.1j
./gen 10 4 7  > test/korupcija.in.1k
./gen 10 4 19 > test/korupcija.in.1l
./gen 10 4 27 > test/korupcija.in.1m
./gen 10 4 35 > test/korupcija.in.1n
./gen 10 4 12 > test/korupcija.in.1o
./gen 10 4 30 > test/korupcija.in.1p
./gen 10 4 33 > test/korupcija.in.1q
./gen 10 4 21 > test/korupcija.in.1r
./gen 11 2 1  > test/korupcija.in.1s
./gen 11 3 2  > test/korupcija.in.1t
./gen 11 4 3  > test/korupcija.in.1u

#subtask 2
./gen 5 10 2 7  1 > test/korupcija.in.2a
./gen 5 10 2 8  2 > test/korupcija.in.2b
./gen 5 20 2 9  2 > test/korupcija.in.2c
./gen 5 20 1 10 1 > test/korupcija.in.2d
./gen 5 20 2 11 1 > test/korupcija.in.2e
./gen 5 20 2 12 1 > test/korupcija.in.2f
./gen 5 20 2 13 1 > test/korupcija.in.2g
./gen 5 20 2 14 1 > test/korupcija.in.2h
./gen 5 20 2 15 1 > test/korupcija.in.2i
./gen 5 20 2 16 1 > test/korupcija.in.2j
./gen 5 20 2 17 1 > test/korupcija.in.2k
./gen 5 20 2 18 1 > test/korupcija.in.2l
./gen 5 20 2 19 1 > test/korupcija.in.2m


#subtask 3
./gen 6 6 1  > test/korupcija.in.3a
./gen 8 2 2  > test/korupcija.in.3b
./gen 8 3 3  > test/korupcija.in.3c
./gen 8 4 4  > test/korupcija.in.3d
./gen 8 4 4  > test/korupcija.in.3e
./gen 8 5 5  > test/korupcija.in.3f
./gen 8 5 5  > test/korupcija.in.3g
./gen 8 5 5  > test/korupcija.in.3h
./gen 8 6 6  > test/korupcija.in.3i
./gen 9 1    > test/korupcija.in.3j
./gen 9 4    > test/korupcija.in.3k
./gen 9 7    > test/korupcija.in.3l
./gen 9 10   > test/korupcija.in.3m
./gen 7 1    > test/korupcija.in.3n
./gen 7 2    > test/korupcija.in.3o
./gen 11 6 4 > test/korupcija.in.3p
./gen 11 6 5 > test/korupcija.in.3q
./gen 11 6 6 > test/korupcija.in.3r

#subtask 4
./gen 2 20 33     > test/korupcija.in.4a
./gen 2 20 34     > test/korupcija.in.4b
./gen 2 20 35     > test/korupcija.in.4c
./gen 2 20 36     > test/korupcija.in.4d
./gen 2 20 37     > test/korupcija.in.4e
./gen 3 20 38     > test/korupcija.in.4f
./gen 3 20 39     > test/korupcija.in.4g
./gen 3 20 40     > test/korupcija.in.4h
./gen 3 20 41     > test/korupcija.in.4i
./gen 3 20 42     > test/korupcija.in.4j
./gen 4 8         > test/korupcija.in.4k
./gen 4 10        > test/korupcija.in.4l
./gen 4 15        > test/korupcija.in.4m
./gen 4 16        > test/korupcija.in.4n
./gen 4 20        > test/korupcija.in.4o
./gen 5 20 1 43 3 > test/korupcija.in.4p
./gen 5 20 2 44 3 > test/korupcija.in.4q
./gen 5 20 3 45 3 > test/korupcija.in.4r
./gen 5 20 4 46 3 > test/korupcija.in.4s
./gen 5 20 5 47 3 > test/korupcija.in.4t
./gen 6 10 48     > test/korupcija.in.4u
./gen 6 15 49     > test/korupcija.in.4v
./gen 6 20 50     > test/korupcija.in.4w
./gen 7 1         > test/korupcija.in.4x
./gen 7 2         > test/korupcija.in.4y
./gen 8 2 51      > test/korupcija.in.4z
./gen 8 3 52      > test/korupcija.in.4aa
./gen 8 4 53      > test/korupcija.in.4ab
./gen 8 5 54      > test/korupcija.in.4ac
./gen 8 6 55      > test/korupcija.in.4ad
./gen 8 7 56      > test/korupcija.in.4ae
./gen 8 8 57      > test/korupcija.in.4af
./gen 9 2         > test/korupcija.in.4ag
./gen 9 5         > test/korupcija.in.4ah
./gen 9 8         > test/korupcija.in.4ai
./gen 9 10        > test/korupcija.in.4aj
./gen 11 20 114   > test/korupcija.in.4ak
./gen 11 20 115   > test/korupcija.in.4al
./gen 11 20 116   > test/korupcija.in.4am
./gen 11 20 111   > test/korupcija.in.4an
./gen 11 20 112   > test/korupcija.in.4ao
./gen 11 20 113   > test/korupcija.in.4ap
