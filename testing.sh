#!/bin/bash
#
# purpose: fuzz tests on sudoku creator and solver, and runs some extra test cases
#
# input: number of sudokus to generate and solve. shell script 
# reads from user, it is not a command-line argument
#
# when a puzzle is created, it means that it only has one solution because our
# creator (see create.c) only prints out the puzzle if there is only one possible solution.
#
# when a puzzle is solved, it means that it follows all sudoku rules and that no
# already filled cells are changed because our solver (see solve.c) only puts in numbers where
# the number is zero (meaning it was not already filled) and it is possible for
# that number to go there according to the sudoku rules.
# 
# Devon Starr, Annie Tang, & Amanda Sun
# CS50 Spring 2022


echo ""
echo "******************* sudoku tester *******************"
# ./sudoku create | ./sudoku solve > "testfiles/result.txt"

echo "***generating and solving 10 sudokus using ./sudoku create | ./sudoku solve***"
echo "***  delaying one second each time to refresh the random number generator  ***"
echo "Enter number of iterations: "
read END
for i in $(seq 1 $END);
do
   echo "Creating sudoku $i..."
   ./sudoku create | tee testfiles/temp # tee prints to stdout and also to a file
   sleep 0.5
   echo ""

   echo "Solving sudoku $i..."
   ./sudoku solve < testfiles/temp
   sleep 0.5
   echo ""
done
echo "******************* hardcoded sudoku tester, only prints if failed *******************"

#3324
./sudoku solve < testfiles/input1.txt > testfiles/output1.txt
diff -w "testfiles/output1.txt" "testfiles/answer1.txt" || echo "<< Test 1 Failed>>"

# #9378
./sudoku solve < testfiles/input2.txt > testfiles/output2.txt
diff -w "testfiles/output2.txt" "testfiles/answer2.txt" || echo "<< Test 2 Failed>>"

# # from https://sandiway.arizona.edu/sudoku/examples.html, Daily Telegraph January 19th "Diabolical"
./sudoku solve < testfiles/input3.txt > testfiles/output3.txt
diff -w "testfiles/output3.txt" "testfiles/answer3.txt" || echo "<< Test 3 Failed>>"

# # from https://sandiway.arizona.edu/sudoku/examples.html, Vegard Hanssen puzzle 2155141
./sudoku solve < testfiles/input4.txt > testfiles/output4.txt
diff -w "testfiles/output4.txt" "testfiles/answer4.txt" || echo "<< Test 4 Failed>>"

# # from https://sandiway.arizona.edu/sudoku/examples.html, Challenge 2 from Sudoku Solver by Logic
./sudoku solve < testfiles/input5.txt > testfiles/output5.txt
diff -w "testfiles/output5.txt" "testfiles/answer5.txt" || echo "<< Test 5 Failed>>"