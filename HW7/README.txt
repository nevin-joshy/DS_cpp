HOMEWORK 7: SUPER SMASH BROS. FRAMES


NAME:  Nevin Joshy


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

cplusplus.com

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  20



ORDER NOTATION ANALYSIS:
Consider the following variables and give the complexity for both running
time AND space along with a short justification for each of the queries below.
For the commands, do not count the space occupied by the database in the space
complexity analysis.

f: The total number of fighters
m: The number of different moves
t: The highest number of moves that have the same starting frame for a particular move

reading the database/populating your initial data structure:

-q (specific move): O(logf + logm)- my code finds the fighter in the map, and then finds
the move within the fighter object map. If there is less than 7 fighters, logm is greater
so both must be included.

-q (all): O(logf + m) - my code finds the fighter using .find in the fighter map, and 
then goes through each of the moves in the object's moves map, which will cost O(m). 
However, both must be inlcuded becuase with a large enough amount of fighters, logf 
could be greater than m

-f: O(f) - my code goes through each of the fighters to add them to a map by their frame
for the specific move, in which they are then sorted by name in the values through a set.
I then go through the first "limit" number of values in the map/sets.

-s: O(f) - uses the same code as -f, but goes through the last "limit" number of values
using a reverse iterator

-d: O(f) - Goes through each of the fighters and outputs of the frame for the move 
matches.


MISC. COMMENTS TO GRADER:  
(optional, please be concise!)






