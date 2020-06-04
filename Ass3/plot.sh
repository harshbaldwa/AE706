cd codes/ && gcc -lm 170010035.c && ./a.out

if [ $1 == 1 ]
then
     python3 plot.py
fi

if [ $1 == 2 ]
then
    python3 plot_parts.py
fi
