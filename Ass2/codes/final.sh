gcc -lm 170010035.c

if [ $1 == 1 ]
then
    ./a.out 1 && python3 -c "import final; final.error_iterations()"
fi

if [ $1 == 2 ]
then
    ./a.out 2
fi

if [ $1 == 3 ]
then
    ./a.out 3 && python3 -c "import final; final.optimum_w()"
fi

if [ $1 == 4 ]
then
    ./a.out 4 $2 && python3 -c "import final; final.plot_result_midlines()"
fi

if [ $1 == 5 ]
then
    ./a.out 5 $2 && python3 -c "import final; final.contour_plotting()"
fi

