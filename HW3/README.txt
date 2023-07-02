HOMEWORK 3: MATRIX CLASS


NAME:  Nevin Joshy


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

Yanelle(Office Hours)
Adriano Andrade
Cameron Arner


Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  8



ORDER NOTATION:
For each of the functions below, write the order notation O().
Write each answer in terms of m = the number of rows and n = the
number of columns.  You should assume that calling new [] or delete []
on an array will take time proportional to the number of elements in
the array.

get O(m*n)

set O(m*n)

num_rows O(m)

get_column O(m)

operator<< O(m*n)

quarter O(m*n)

operator== (m*n)

operator!= (m*n)

swap_rows (m)

rref (provided in matrix_main.cpp) O(m*m) or O(m*n) - depending on whether m or n is bigger



TESTING & DEBUGGING STRATEGY: 
Discuss your strategy for testing & debugging your program.  
What tools did you use (gdb/lldb/Visual Studio debugger,
Valgrind/Dr. Memory, std::cout & print, etc.)?  How did you test the
"corner cases" of your Matrix class design & implementation?

My testing and debugging strategy was to add tests to student test or slowly uncomment
the simple test. I tested corner cases such as when the row or columns are zero in my 
student tests.I also used valgrind to find where memory leaks could be, and I also used
gdb when I ran into seg faults.


EXTRA CREDIT: 
Indicate here if you implemented resize() for extra credit.  
Also document the order notation for your resize() function.

I implemented the resize function. The order would be O(m*n)



MISC. COMMENTS TO GRADER:  
(optional, please be concise!)

