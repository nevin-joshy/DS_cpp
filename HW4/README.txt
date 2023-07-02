HOMEWORK 4: TOOL RENTAL LISTS


NAME:  Nevin Joshy


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

Cameron Arner

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  25



ORDER NOTATION:
Use these variables to analyze each phase of computation.  Briefly
justify your answer for each part.


i = # of different inventory items
c = # of different customers
p = # of pending customers
q = max quantity of a particular tool owned by the store
r = max # of tools rented or requested by a customer at one time
p = total # of pending tool rentals
e = # of rental or return events


Load inventory file: O(i)
Inventory file has runtime 1 for each element of the inventory list, so O(i)

Rental event: O(c+i)
A rental event goes through the the customer list to see whether the customer is already
in the list, and the inventory list to find information about the tool

Return event - no pending customer(s): O(r+p)
With no pending customer, code goes through tools the customer is renting
as well as going thorugh all of the customers that are renting the tool

Return event - with pending customer(s): O(p(c+r+p))
With pending customers, code goes through each customer to find the id of customer
in pending list, each tool in the pending list to find the quantity, and then the quantity,
all as many times as there are customers in the pending list

Entire program: O(e(c+i) + e(r+p) + e(p(c+r+p))
Each equation is multiplied by e, because each operation happens each time there is a rental
or return event, so e times.

MISC. COMMENTS TO GRADER:
(optional, please be concise!)

