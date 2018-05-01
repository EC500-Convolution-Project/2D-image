# Frank Tranghese 
# EC500 - Parallel Programming
# Project 1 - 2D Convolution on GPU

# SETUP
set term png
set output 'all_kernel_direct.png' # output filename
set title 'Runtime of Direct 2D Convolution with NxN Filter' # set title
set xlabel 'N (image size NxN)' # set x axis label
set ylabel 'Runtime (seconds)' # set y axis label
set key outside right # set legend position
set xrange[0:1024] # adjust x-range
#set format x "%.0s✕10^{%S}" # change xtic to scientific notation
#set format y "%.0s✕10^{%S}" # change xtic to scientific notation
#set xtics font ", 6" # set xtic fontsize
set yrange[0:5.5] # adjust y-range
#set logscale x # set x to logscale
#set logscale y # set y to logscale
set style line 1 lc rgb '#0ce90b' lt 1 lw 3 # --- green
set style line 2 lc rgb '#065fd8' lt 1 lw 3 # --- blue
set style line 3 lc rgb '#bf000a' lt 1 lw 3 # --- red

# DATA AND PLOTTING
plot 'all_Kernel_Direct.dat' using 1:2 with lines ls 1 title 'GPU','all_Kernel_Direct.dat' using 1:4 with lines ls 2 title 'Multi', 'all_Kernel_Direct.dat' using 1:6 with lines ls 3 title 'Serial'