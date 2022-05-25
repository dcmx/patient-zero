#!/bin/bash

size="1.6in,1.6in"
xoffset="offset 0,0.5"
yoffset="offset 1,0"
ls='\\ps'

gnuplot <<EOF

set title ''

set terminal epslatex size $size
set lmargin at screen 0.15
set bmargin at screen 0.15
set rmargin at screen 0.95
set tmargin at screen 0.95

set datafile separator "|"

set xlabel 'probability \$p\$' $xoffset
set ylabel 'success rate' $yoffset

set output "plot1.tex"
set format y "\$%.1F\$"
set format x "\$%.1F\$"
set xtics 0.2
set ytics 0.2

#set key default
set key right bottom
set key samplen 1

set xrange [0 to 1]
set yrange [0 to 1]
set samples 1000


plot \
1/0 w l t "$ls ER" ls 1 lw 5,\
1/0 w l t "$ls CM" ls 2 lw 5,\
1/0 w l t "$ls RGG" ls 3 lw 5,\
"data-8-100k4dER" using (\$1):(\$2/(\$2 + \$3 + \$4)) with lines ls 1 t "", \
"data-8-100k4dCM" using (\$1):(\$2/(\$2 + \$3 + \$4)) with lines ls 2 t "", \
"data-8-100k16dRGG" using (\$1):(\$2/(\$2 + \$3 + \$4)) with lines ls 3 t ""

set output "plot2.tex"
set key right bottom

plot \
1/0 w l t "$ls 8 rounds" ls 3 lw 5,\
1/0 w l t "$ls 16 rounds" ls 4 lw 5,\
1/0 w l t "$ls 32 rounds" ls 5 lw 5,\
"data-8-100k16dRGG" using (\$1):(\$2/(\$2 + \$3 + \$4)) with lines ls 3 t "", \
"data-16-100k16dRGG" using (\$1):(\$2/(\$2 + \$3 + \$4)) with lines ls 4 t "", \
"data-32-100k16dRGG" using (\$1):(\$2/(\$2 + \$3 + \$4)) with lines ls 5 t ""

unset yrange
set xrange [0 to 10]
set xtics 1
set format x "\$%.0F\$"
set output "plot3.tex"
set key left top
unset ytics
set xlabel 'distance to \$\\pz\$' $xoffset
set ylabel 'fraction of candidates' $yoffset
plot \
1/0 w l t "0.45" ls 6 lw 5,\
1/0 w l t "0.50" ls 7 lw 5,\
1/0 w l t "0.55" ls 8 lw 5,\
"pt-0.55" using (\$1):(\$2/\$3) with lines ls 8 t "", \
"pt-0.50" using (\$1):(\$2/\$3) with lines ls 7 t "", \
"pt-0.45" using (\$1):(\$2/\$3) with lines ls 6 t ""
EOF




