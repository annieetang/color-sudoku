# Sudoku

## CS 50 22S, Final Project

## Members: Devon Starr, Amanda Sun, Annie Tang

### To run colorsudoku

Mac users:

* install `node` first
    * to check if you have `node`, in terminal type `node -v`
    * if no version exists, `brew install node`
* try `npm start`
    * if this works, then the app should run
    * if not, `npm install react-scripts --save`
    * afterwards, try `npm start` again, and it should work

### Usage
The *querier* must be called with `make` and then `./querier pageDir fileName`. The user will continue to enter input, until control-D or control-C are pressed. The input will be searched if it follows this output:
- no literals in the beginning, end, or sequentially
- no non-alpha, non-space characters 
- no empty lines or enters

If any of those cases occur, an error statement will be printed and the user will be prompted for another query.

To generate random test cases, *fuzzquery* must be called with `make all` and then `fuzzquery filename number seed`

The `testing.sh` file assumes there is a data and tse-output folder on the same hierarchy as querier.

### Assumptions

For querier:
* The doc_id is not more than 3 digits.
* The sub-methods assume that the arguments are valid and non-NULL. This is because the main checks these arguments before allowing the next function to proceed.

### Files
* `.gitignore` - ignores files
* `REQUIREMENTS.md` – given for the Lab 6
* `DESIGN.md`- abstract details, pseudocode, APIs
* `IMPLEMENTATION.md` - specific, hardware and language-type implementation
* `Makefile`- see Usage
* `README.md`- this
* `fuzzquery.c`- produces test text from source files
* `querier.c` - the main code
* `testing.sh`- test querier using fuzzquery
* `testing.out` - output of testing.sh