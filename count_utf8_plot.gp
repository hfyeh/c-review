set title "Count UTF-8"
set xlabel "Buffer length (bytes)"
set ylabel "Elapsed time (ms)"
set terminal png font " Times_New_Roman,12 "
set output "count-utf8.png"
set xtics 0,5000,40000
set key left 

plot \
"utf8_release.txt" using 1:2 with linespoints linewidth 2 title 'count_utf8', \
"utf8_release.txt" using 1:3 with linespoints linewidth 2 title 'swar\_count\_utf8'

