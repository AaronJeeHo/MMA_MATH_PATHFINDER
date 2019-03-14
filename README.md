# MMA_MATH_PATHFINDER
This program takes in two fighter names, and outputs each fighters individual win/loss record and fight metrics.
The program then outputs the shortest path from FighterA->FighterB, and FighterB->FighterA respectively.

The path is outputted as: 
Fighter1->Fighter2->Fighter3->Fighter4

This can be translated to, fighter1 beat fighter2 who beat fighter3 who beat fighter4...

Afterwards the program uses the individual fighters fight metrics and path to make a prediction regarding who will win a fight between the two, and how they will win(Although I wouldn’t use this to decide on who to bet the house on the next UFC event)

The program can be ran using two different executables 

The first being:
./build/part3  fighter_1 fighter_2 output_file

This executable allows you to directly input the fighter names and output file onto the command line, and outputs the analysis to the output.txt of your choosing

The second being:
./build/interactive

This executable will prompt you to input the name for fighterA and fighterB, unlike the direct executable, this one will continuously ask for an input until you give it a valid fighter name. This program by default outputs to “output.txt”

COMPILE WITH MAKE

ALL INPUTS SHOULD BE LOWERCASE

