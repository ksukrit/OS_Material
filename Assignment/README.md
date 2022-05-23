# Operating Systems (CSF372) Assignments

## Group Members:

<ul>
<li>Sukrit Kumar</li>
<li>Jahnavi Gurdasani</li>
<li>Abhishek Revinipati</li>
<li>Achyut Bajpai</li>
<li>Parth Chauhan</li>
<li>Shubham Priyank</li>
<li>Shubham Singla</li>
<li>Dhruv Makwana</li>
</ul>

# Assignment 1 Multithreaded sudoku solver 
Doesn't work for 36x36 grid sizes
Compile `gcc -pthread sudoku.c -o sudoku.out -lm`
Usage: `./sudoku.out grid_size grid_name`

# Assignment 2 Approximate scheduler RR and Preemptive Priority 
Very approximate scheduler. Priority is inverse of runtime, only runs on 2 processes, but can be extended to more by using a queue or tree structure.
Compile all : `make all`
Usage : `main_sched.out or main_sched_priority.out filename no of ints to sum`
Eg : `/main_sched.out ./TestFiles/hundred.txt 100`
