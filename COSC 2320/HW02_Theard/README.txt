Stefan Theard Peoplesoft ID: 1208198
Cosc 2320

This program is a doubly linked list implementation that will take an input of a scriptfile
with several commands: read, write (forward or backward), union and intersection. Union will take two lists
that were previously initialized with read and combine them, putting them into a single list.
Intersection will take two lists and see which of the words exist in both lists, and insert those words into
a new list.

intersection_func(LinkedList *, Node* LinkedList*)
is the intersection recursive definition function.

union_func(Node*, Node*, LinkedList*)
is the union recursive definition function.

Both intersection and union are done completely with recursion, as well as auxillery functions such as

LinkedList.doesWordExist(string)
and
ListContainer.find_list(string)

writeForward and writeReverse are also recursive functions