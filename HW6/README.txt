HOMEWORK 6: INVERSE WORD SEARCH


NAME:  Nevin Joshy


COLLABORATORS AND OTHER RESOURCES: 
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

cplusplus.com

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.

ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  60


ALGORITHM ANALYSIS:
What's the order notation of your algorithm?

O(w*h*8^(r*s*l))
it has to go through every spot in the grid, (w*h) hand has to recurse for
each direction the word fits in the list, so 8 is the base for the exponent.
Within the recursion, the code needs to go through each good and bad word,
and insert/remove good words with each letter, so in the exponent is r*s*l


TEST CASE SUMMARY:
How did your program perform on the different test cases?  Summarize
the running times.  (It's ok if it didn't finish the harder examples.)
What new test cases did you create and how did it perform on those
tests?
My program ran well for all of the test cases, all taking under a second for both
all and 1 solution except for puzzle 8, which took a bit less than 2 seconds for 
all solutions but still under 1 second for one solution.
My test cases included puzzle9, which tested for a repeated word and that outputted in
less than a second. puzzle10 is a word search I made myself, which had 208 solutions
because of 2 ways to put ice, which creates an open letter. This also ran in less than
a second.

Table:

puzzle      one     all
1          0.034    0.077
2          0.033    0.052    
3          0.039    0.050
4          0.015    0.018
5          0.038    0.095    
6          0.048    0.227
7          0.018    0.252
8          0.395    1.810
9          0.013    0.025
10         0.013    0.299



MISC. COMMENTS TO GRADER:  
Optional, please be concise!

