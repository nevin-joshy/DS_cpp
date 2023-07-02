HOMEWORK 8: B+ TREES


NAME:  Nevin Joshy


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

cplusplus.com, Adriano

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  35


TESTING & DEBUGGING STRATEGY: 
Discuss your strategy for testing & debugging your program.  
What tools did you use (gdb/lldb/Visual Studio debugger,
Valgrind/Dr. Memory, std::cout & print, etc.)?  How did you test the
"corner cases" of your implementation?


I used valgrind for memory debuggiing, and often used gdb for other kinds of debugging
with breakpoints and backtracing. I tested the corner cases, such as with higher degrees
3, in my own test cases.


MISC. COMMENTS TO GRADER:  
While it may have been possible to combine some aspects of my checkparent and insert,
I found it more clear to separate them because of the difference in the split for leafs 
and parents. For print BFS, if the degree is even, we were never told which side, the top
or bottom, the extra node should be on. My code will put the extra on the bottom.

