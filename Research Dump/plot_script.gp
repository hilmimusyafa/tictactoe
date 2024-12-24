set terminal png size 800,600
set output '"D:/Campus/Courses/3rd Semester/Analysis Complecity of Algorithm/Big Project/tictactoe/duration_plot.png"'
set title 'Bot Thinking Time'
set xlabel 'Move Number'
set ylabel 'Duration (seconds)'
plot '"D:/Campus/Courses/3rd Semester/Analysis Complecity of Algorithm/Big Project/tictactoe/iterative_times.dat"' with lines title 'Iterative', \
     '"D:/Campus/Courses/3rd Semester/Analysis Complecity of Algorithm/Big Project/tictactoe/recursive_times.dat"' with lines title 'Recursive'
