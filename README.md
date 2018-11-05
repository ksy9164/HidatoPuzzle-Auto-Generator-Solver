Hidato Puzzle Auto Generator & Solver
====================================================================

###Generating Hidato Puzzle and Auto Solver  (C++ ) 

###
Compile
--------
````bash
$ make
````
####
Run
--------
````bash
$./autoHidato
````
###
Structure
-----------
This code has two thread one is for Generator and the other is for Solver.
###
###Generator
######
 * Generator has two modes one is generating Hidato Puzzle which has a unique solution. 
The other mode is generating Hidato Puzzle which has not unique solutions.  
######
 * The Generator adjusts the difficulty level based on the time the solver spending.
######
 * The Generator check answer which solved by Solver.  

###Solver
######
 * The Solver solves the Hidato Puzzle which given by Generator.
######
 * The solver checks if the puzzles created by the generator have a unique solution.
