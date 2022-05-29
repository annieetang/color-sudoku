#!/bin/bash

fails=0

echo "******************* sudoku tester *******************"
./sudoku create | ./sudoku solve > "testfiles/result.txt"

vi "testfiles/sol2.txt"

"testfiles/input2.txt" > ./sudoku solve > "testfiles/sol2.txt"

diff -q --brief "testfiles/comp2.txt" "testfiles/sol2.txt"
if [ $? != 0 ]; 
then 
    echo "<< Test $i Failed>>"
    fails=$fails+1
fi

#3324
# ./sudoku solve
# 6 5 8 0 0 0 0 7 0
# 0 7 0 0 5 0 8 0 0
# 0 3 9 0 0 0 5 4 0
# 0 0 2 6 0 5 0 0 7
# 0 6 0 9 7 4 0 0 0
# 7 0 0 3 0 0 6 0 0 
# 0 4 6 0 0 0 2 5 0
# 0 0 7 0 6 0 0 0 0
# 0 0 0 0 0 0 7 6 8
# | > "testfiles/sol3.txt"

# diff -q --brief "testfiles/comp3.txt" "testfiles/sol3.txt"
# if [ $? != 0 ]; 
# then 
#     echo "<< Test $i Failed>>"
#     fails=$fails+1
# fi

# #9378
# ./sudoku solve
# 0 0 0 0 0 8 0 3 1
# 7 3 0 6 0 0 0 0 0
# 0 0 0 3 4 0 9 0 2
# 3 0 0 0 0 0 0 0 0
# 5 0 0 0 0 0 8 0 3
# 0 0 6 1 3 0 0 0 0
# 0 0 2 0 0 4 3 0 0
# 4 0 3 2 7 0 0 0 0
# 0 9 0 5 0 0 0 0 6
# | > "testfiles/sol4.txt"

# diff -q --brief "testfiles/comp4.txt" "testfiles/sol4.txt"
# if [ $? != 0 ]; 
# then 
#     echo "<< Test $i Failed>>"
#     fails=$fails+1
# fi

echo $fails