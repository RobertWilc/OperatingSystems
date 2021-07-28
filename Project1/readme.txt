Robby Wilcox rfw14 A02446918

How to compile and run source code.

Problem 1 A:
- pre.c is for problem 1.
- to compile, go to the folder where pre.c is located
- type "gcc -std=c99 pre.c -o pre" without the quotations.
- to run, type ./pre
- the program has no prompts and just waits for user input
- expected input "Name GPA" without the quotations. IE: Robby 4.0
- press enter after each input.
- GPA is a float so use decimal places to the hundredths(2 decimal places) IE: 3.2
- When done typing students names and GPAs, press ctrl-D to send EOF signal to program
- Program will output students names that have a GPA of greater than 2.0

Problem 1 B:
- sort.c is for problem 2.
- to compile, follow same process as problem 1
- type "gcc -std=c99 sort.c -o sort" without the quotations.
- to run, type ./sort
- the program has no prompts and just waits for user input
- expected input is "Name" without the quotations. IE: Robby
- rpess enter after each input.
- when done, press ctrl-D to send EOF signal to program
- program will output the names in alphabetical order

Problem 2:
- With the compiled programs from above, type "./pre | ./sort"
- Follow the same input style as problem 1 A.
- When done, press ctrl-D to send EOF signal to program
- ./sort will output the students that have a GPA > 2.0 in alphabetical order

Problem 3:
- to compile, follow same process as problem 1 A & 1 B.
- type "gcc num3.c -o three" without the quotations.
- to run, type "./three ls"
- program will send the ls command to the terminal and print contents of PWD as well as child PID and PPID.
 
