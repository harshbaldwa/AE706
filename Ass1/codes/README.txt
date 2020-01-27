for compiling code:
    gcc 170010035.c -o main

5 arguments to be given to the code
    a) Initial case No.
        1 -> Step Input
        2 -> Sin Input with frequency 4pi
        3 -> Sin Input with frequency 8pi
        4 -> Sin Input with frequency 12pi

    b) Mu value
        1 -> 0.5
        2 -> 1.0
        3 -> 1.5
    
    c) Finite Difference Scheme
        1 -> FTFS
        2 -> FTCS
        3 -> FTBS
        4 -> LW
        5 -> BW
        6 -> FR

    d) Complete or Solution at any instant
        1 -> Solution @ t=T
        2 -> Complete Solution

    e) Time instant
        0 -> When Complete Solution is selected
        T -> Time instant T

So here are some examples for this:

    a) If we want to plot graph of Step input FTBS Scheme for Mu = 1.0 and at time T = 20,
        run the following code:
            ./main 1 2 3 1 20 && python3 plotting.py

    b) If we want to plot graph of Sin input with 12pi frequency BW Scheme for Mu = 1.5 (complete animation),
        run the following code:
            ./main 4 3 5 2 0 && python3 animations.py

CAUTION: Please enter 5th argument as 0 when solving for complete solution

For any clarification, please contact me @ +91-7742895101