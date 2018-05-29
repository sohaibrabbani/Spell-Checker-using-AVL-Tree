# Spell Checker using AVL Tree

A relatively simple spell checker for text. The spell checker will incorporate a database of known words, built from a simple word list and organized for efficient searching.

## Program execution:
The program will be invoked with three command-line parameters:
**spellcheck '<command file> <dictionary file> <log file>'
The program will verify the existence of the two input files; if either is missing, it will
print an error message and exit. Otherwise, the program will first open the dictionary
file and add the words to the spell checker's database. Next, the program will open the
command file, and process the commands one by one. Results will be written to the log
file, as described below. There is one interesting constraint.
Thanks to the performance of the AVL tree, checking the spelling of a word is not a
terribly expensive operation if the word is found. But if a word is not found,
determining the list of suggestions is quite expensive. The rules given above do not
permit any real optimization of the search. It is necessary to traverse the entire AVL
tree, comparing the misspelled word to each element of the tree. This has some
consequences.
First, you must decide what traversal to apply when searching for substitutions. Any
traversal would do, but some may be more efficient than others.
Second, there are issues relating to responsibility when the substitutions are being
determined. Ideally the AVL tree storing the word list should not know anything about
the data type it's storing, much less be responsible for defining a complex comparison
