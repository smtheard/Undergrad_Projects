Name: Stefan Theard
Peoplesoft ID: 1208198

This program will take a simple input of exactly 1 argument, that has to have filname="TC1.txt" or filname=TC1.txt where TC1.txt is any valid .txt file. 
First it will use a command line parser I built from scratch to clean the 'filename=' from the input and store that into a variable to use for opening the .txt file
It will then use that to open and read the input of the given text file. It then will call the constructor of a class I created called "Database" with the argument of an array
of the .txt files' input. Then a series of augmentative functions are called such as db.strip_punctuation, db.tolowercase that take the object's local storage of the input and
modify it in order to easily find the word count later. It will then call find_word_counts() and get the count of each word in the input, I made use of a class called "Word" for this
in order to bunch together the word and it's respective count. Finally it will call a simple sort+display function called output_results() This will use a basic sort to sort into descending
order and then output the results, if multiple results are tied for top position, the program will output all respective contenders and not just restrict itself to a single top word.
While writing this I noticed that I didn't have a solution for malformed arguments or if the file was not in the folder of the exe so I added in an if statement to catch if the file.open()
fails, it now outputs an error message instead.