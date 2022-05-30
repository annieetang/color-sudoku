#!/bin/bash

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
./sudoku solvefile testfiles/output1.txt < testfiles/input1.txt

diff -w "testfiles/output1.txt" "testfiles/answer1.txt" || echo "<< Test 1 Failed>>"

#9378
./sudoku solvefile testfiles/output2.txt < testfiles/input2.txt
diff -w "testfiles/output2.txt" "testfiles/answer2.txt" || echo "<< Test 2 Failed>>"

# from https://sandiway.arizona.edu/sudoku/examples.html, Daily Telegraph January 19th "Diabolical"
./sudoku solvefile testfiles/output3.txt < testfiles/input3.txt
diff -w "testfiles/output3.txt" "testfiles/answer3.txt" || echo "<< Test 3 Failed>>"

# from https://sandiway.arizona.edu/sudoku/examples.html, Vegard Hanssen puzzle 2155141
./sudoku solvefile testfiles/output4.txt < testfiles/input4.txt
diff -w "testfiles/output4.txt" "testfiles/answer4.txt" || echo "<< Test 4 Failed>>"

# from https://sandiway.arizona.edu/sudoku/examples.html, Challenge 2 from Sudoku Solver by Logic
./sudoku solvefile testfiles/output5.txt < testfiles/input5.txt
diff -w "testfiles/output5.txt" "testfiles/answer5.txt" || echo "<< Test 5 Failed>>"