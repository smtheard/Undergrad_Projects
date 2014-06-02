Stefan Theard PSID: 1208198

Spell Checker (HW05)

This program uses an AVL HEIGHT BALANCED TREE to check input files for mispelled words.
The syntax is spellchecker script=script.script;dictionary=dictionary.txt where the script and txt
files are any filename you specify. The dictionary is read into the program as an AVL height balanced tree (all of the avl tree functions and definition are all inside of the class "TreeContainer" inside of spellchecker.cpp) and this serves to maintain a log(n) search time for any searches through the tree. The program takes inputs in the script file of the following:


read(listname,'textnamehere.txt')       //reads textnamehere into listname

check(listname1,list-you-want-to-check) //checks the specified list for misspelled words, stores 						//the results into listname1

write(listname,'textnamehere.txt',forward)// This writes the listname to the textnamehere.txt file
					  // the "forward" part can be empty (default to forward)
					  // or it can be "reverse" and it will be written reverse
					  // to the text file

intersection(listname1, listname2, listname3)
//This computes the set theory intersection of listnames 1 and 2, and stores it into listname3

union(listname1, listname2, listname3)
//This computes the set theory union of listnames 1 and 2, and stores it into listname3

