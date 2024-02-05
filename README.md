## Concordance

A program constructing a concordance for a text file.
A text concordance is an alphabetical listing of all distinct words in a piece of text. 

The words are to be stored in an array/vector of 26 binary search trees. Part of each node of the BST 
will have a circular linked list Queue. When the concordance is being output, the words should be in alphabetical order, and for 
each word the line numbers will be displayed in ascending order.

##### Output desired:

**Concordance [A]:**

- A -> 1 5 6 7 8 9
- ADDITION -> 1
- ALREADYSOAKED -> 1
- ALSO -> 3
- ALTUS -> 9
- AMARILLO -> 5
- AND -> 1 5 5 6 6 7 8 8 8 9 9
- ANGELO -> 7
- ARE -> 3 3
- AREA -> 3 5 6 7 8 9
- AS -> 1 3

**Concordance [B]:**

<- EMPTY ->

**Concordance [C]:**

- CDT -> 5 6 7 8 9
- CENTER -> 4
- CITY -> 8
- COLORADO -> 6 6

**Concordance [D]:**

- DODGE -> 8

etc
