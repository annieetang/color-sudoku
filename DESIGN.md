# Sudoku Design File

## CS 50 22S, Final Project

## Members: Devon Starr, Amanda Sun, Annie Tang


# NOTES: 

Github issues
Github feature branch flow

two running modes:
./sudoku create
    >=40 missin gnumbers

./sudoku solve
    accept puzle with multiple solutions
    reads puzzle from stdin to stdout

This Design Spec contains several sections:

* User interface
* Inputs and Outputs
* Functional decomposition into modules
* Pseudo code for logic/algorithmic flow
* Dataflow through modules
* Major data structures
* Testing plan

# FROM PREVIOUS LAB TO USE AS A TEMPLATE:

### User interface

The indexer's only interface with the user is on the command-line; it must always have 2 arguments.

`./querier pageDirectory indexFilename`
   * where `pageDirectory` is the pathname of a directory produced by the Crawler, and
   * where `indexFilename` is the pathname of a file produced by the Indexer.

For example:

``` bash
$ ./querier ../data my_index_file
```

### Inputs and outputs

Input: the only inputs are command-line parameters; see the User Interface above.

Output: 

will return error if the query syntax is somehow invalid, and prompt for the next query.

### Functional decomposition into modules

We anticipate the following modules or functions:

*validate_args* to check usage syntax
*check_query* to see if query is of valid syntax
*split* which takes the input and creates an array of words
*clean_query* prints the query
*intersection* looks for documents with wordA AND wordB
*union* looks for documents with wordA OR wordB

### Pseudo code for logic/algorithmic flow
The querier will run as follows:

1. execute from a command line with usage syntax
   * `./querier pageDirectory indexFilename`
   * where `pageDirectory` is the pathname of a directory produced by the Crawler, and
   * where `indexFilename` is the pathname of a file produced by the Indexer.

2. validate its command-line arguments:
	* `pageDirectory` is the pathname for an existing directory; if it cannot be verified to be a directory produced by the Crawler, the indexer shall print an error message and exit non-zero. 
	* `indexFilename` is the pathname of a readable file; if it is not possible to open it for reading, the querier should print an error message and exit non-zero.

2. load the index from `indexFilename` into an internal data structure.

3. read search queries from stdin, one per line, until EOF.
	4. clean and parse each query according to the *syntax* described below.
	5. if the query syntax is somehow invalid, print an error message, do not perform the query, and prompt for the next query.
6. print the 'clean' query for user to see.
7. use the index to identify the set of documents that *satisfy* the query.
	8. if the query is empty (no words), print nothing.
	6. if no documents satisfy the query, print `No documents match.`
	10. Structure your code to follow the structure of the grammar, which has two non-terminals (query and andsequence), to write a function that handles each.
One function to return set of documents that satisfy an andsequence, looping over words in the andsequence; accumulate an answer (like a running product) as you go.
Another function to return set of documents that satisfy a query, looping over calls to the above function for each andsequence; accumulate an answer (like a running total) as you go.
	7. otherwise, rank the resulting set of documents according to its *score*, as described below, and print the set of documents in decreasing rank order; for each, list the score, document ID and URL.
(Obtain the URL by reading the first line of the relevant document file from the `pageDirectory`.)
	8. Exit with zero status when EOF is reached on stdin.

### Dataflow through modules

 1. 

### Major data structures

Two helper modules provide the data structures:

 6.

### Testing plan
1. 