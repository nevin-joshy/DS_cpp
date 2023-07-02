HOMEWORK 9: DISTANCE FIELDS & FAST MARCHING METHOD


NAME:  Nevin Joshy


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

cplusplus.com

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  23



NAIVE ALGORITHM:

Order Notation: O(w*h*w*h)

Timing Experiment Data:
tiny_5x5 - 0.111s
small_10x10 - 0.043s
squiggle_30x30 - 0.114s
lines_100x100 - 1.399s
data_structures_300x300 - 1m48s
dots_1000x1000 - DNF(over 20 minutes)

Discussion: 
This algorithm is O(w*h*w*h) becuase it loops throught the pixels twice in a nested
loop. First getting the first pixel to compare and then looping throgh the pixels
again within the loop until a black pixel is found, then calculating the distance.


IMPROVED ALGORITHM:

Order Notation: O(w*h*(number of black pixels))

Timing Experiment Data:
tiny_5x5 - 0.043s
small_10x10 - 0.045s
squiggle_30x30 - 0.047s
lines_100x100 - 0.100s
data_structures_300x300 - 14.187s
dots_1000x1000 - DNF(over 20 minutes)

Discussion: 
This algorithm is Order Notation: O(w*h*(number of black pixels)) because first it
loops through all the pixels and adds the black pixels to a vector, and then it runs
through all the pixels again in a separate loop, and for each pixel loops through the
vector of black pixels to find the distances, which is much better than looping through
all of the pixels again to find the black pixels.


FAST MARCHING METHOD (with a map):

Order Notation:O(w*h * log(w*h))

Timing Experiment Data:
tiny_5x5 - 0.043s
small_10x10 - 0.045s
squiggle_30x30 - 0.047s
lines_100x100 - 0.091s
data_structures_300x300 - 0.523s
dots_1000x1000 - 5.945s

Discussion: 
This algorithm is O(w*h * log(w*h)) becuase it first loops through the pixels and adds
the black pixels to a vector, which is O(w*h) but that is separate and smaller than the
rest of the algorithm so it is not included. The code then ends up going though every
pixel(w*h), and pushes all 8 of its neighbors into the priority queue, but the 8 is not
inlcuded and push is O(1). But each pixel is also popped, which is a log operation, so
the w*h is multipled bu log(w*h)


DISTANCE FIELD VISUALIZATIONS FOR EXTRA CREDIT:




FAST MARCHING METHOD (with a hash table) FOR EXTRA CREDIT:

Order Notation:

Timing Experiment Data:

Discussion:



MISC. COMMENTS TO GRADER:  
Optional, please be concise!






