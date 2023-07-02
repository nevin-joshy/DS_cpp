HOMEWORK 5: LINKED TRAIN CARS


NAME:  Nevin Joshy


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

Adriano Andrade, Yanelle

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  25



DESCRIPTION OF IMPROVED SHIPFREIGHT ALGORITHM FOR EXTRA CREDIT 
Aiming for optimal (fastest train speed, most freight, fewest number
of engines used, and fewest resulting trains) for any input.  Note:
Student choice on how to prioritze between these goals.  Describe your
priorization and your implementation.

My shipfrieght is prioritized because it does no twaste the potential of
engines because it sees whether an engine can hold more freight if it was in
a new train. This prevents engines from being wasted just so the maxcar limit
can be reached

DESCRIPTION OF IMPROVED SEPARATE ALGORITHM FOR EXTRA CREDIT 
Aiming for optimally comfortable trains (smaller values for average
distance to dining and/or larger values for closest engine to sleeper)
and/or optimally handling cases with > 2 engines.  Student choice on how 
to prioritze between these goals.  Describe your priorization and your
implementation.

My code optimizes for when there are more than two engines because it starts as split
down the middle, but will even out the number of engines by counting the number of
engines in each train, then pushing back or pushfront, depending on the train, so that
there is the same number of engines and minimal shifts. furhtermore, in the case of odd
number of engines, my code adds an additional car to the train with more engines so that
speed will be more similar.


MISC. COMMENTS TO GRADER:  
Optional, please be concise!


