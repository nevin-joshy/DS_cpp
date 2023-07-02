HOMEWORK 10: MINIBLAST


NAME:  Nevin Joshy


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

cplusplus.com

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  25


HASH FUNCTION DESCRIPTION

I used the has function from the lab on hash tables.



HASH TABLE IMPLEMENTATION

I used a vector of vector of pairs, in which the pairs would hold the
kmer string and their index in the genome. I use linear probing to avoid collisions with
different kmers. Repeats of the same kmer are purposefully collided for easy access when
satisying queries.

ANALYSIS OF PERFORMANCE OF YOUR ALGORITHM:
(order notation & concise paragraph, < 200 words)

The order notation of my algorithm is O(L + p * q * number of queries) because
it requires L spaces in the vector and for each query, we need to access the number of
locations the key is found for each query and alayle the length of the query, all
times the number of queries

L = length of the genome sequence
q - query length
p - number of different locations where key is found
k - key size (k-mer size)

How much memory will the hash table data structure require (order notation for memory use)?

The has table requires O(L * p * k) because it requires as many spaces in the overarching
vector as there are characters in the genome because of the overlap(worst case assuming
no repeats). Then, that is multiplied by as many elements are in each specific vector,
which is the number of locations where the query is found. It is multiplied by k because
each instance in the nested vector holds the kmer.

What is the order notation for performance (running time) of each of
the commands? What about for the hash table's insert, find, and resize?

genome - O(1) - reading genome file line by line and coverting to long string
table size = O(1) -reading in int
occupancy - O(1) - reading in float
kmer - O(1) - reading in an int
insert - Average Case O(1), worst case O(L) because of linear probing
find - Average Case O(q * p)
resize- O(L * p) - go through each row and each column


EXTRA CREDIT
Add a new command to implement the database using one of the other
 data structures that we have covered so far in the course: 
vectors, lists, arrays etc. 

Compare the performance your alternative method to the homework method
by making a table of run times for each of the genomes and query 
sets provided with the homework  and compare the times to build
the index and the times to process the queries. 
Document any new commands you have added in your README file.



MISC. COMMENTS TO GRADER:  
(optional, please be concise!)

I wasnt sure where to put the concise 200 word description, with the order
notation of the algorithm so I put one for the overall algorithm at the top

