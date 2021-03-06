# Spell Checker using AVL Tree

A relatively simple spell checker for text. The spell checker will incorporate a database of known words, built from a simple word list and organized for efficient searching.

## Program execution:
The program will be invoked with three command-line parameters:

**spellcheck &lt;command file&gt; &lt;dictionary file&gt; &lt;log file&gt;**  

## The dictionary file:
The word list file is simply a list of strings, one per line. There is no special parsing required. The controller should just read the words one by one and tell the spell checker to add them to its database. The AVL tree should not allow the insertion of duplicate entries, so if the dictionary file does contain duplicates, they should be filtered out automatically as the tree is being built.

## The command file:
Each line consists of a characters. A newline character will immediately follow the The first two commands are basic searches and must be instrumented as described.

**check&lt;tab&gt;&lt;word&gt;** 
This causes the spellchecker to search the AVL dictionary as described earlier. What should be logged is described below.

**add&lt;tab&gt;&lt;word&gt;** 
This causes the specified word to be added to the AVL dictionary, unless it is a duplicate of course. A message indicating success or failure should be logged.

**remove&lt;tab&gt;&lt;word&gt;** 
This causes the specified word to be removed from the AVL dictionary, provided it is present of course. A message indicating success or failure should be logged.

**display&lt;tab&gt;** 
This causes the AVL tree to be written to the log file, using any traversal
order.

## The log file:
After building the AVL tree, you should display the number of words it contains. The main part of the log file consists of output from the commands. When searching for a word during a spell check, the AVL tree should be instrumented to log the sequence of words that were compared to the sought word along the way. For words that fail the spell check, you must also log the alternatives suggested by the spell checker. The formatting is up to you, but it should be neat and easily read.


## License

* [Apache Version 2.0](http://www.apache.org/licenses/LICENSE-2.0.html)

## Contributing

Please fork this repository and contribute back using
[pull requests](https://github.com/sohaibrabbani/Spell-Checker-using-AVL-Tree/pulls).

Any contributions, large or small, major features, bug fixes, additional
language translations, unit/integration tests are welcomed and appreciated
but will be thoroughly reviewed and discussed.
