# dft.plt

reset
set terminal pngcairo size 350,262 enhanced font 'Verdana,10' 
datafile = 'dft.dat'

set xrange[0:10]
set yrange[-2:2]

realigraph(n) = sprintf("case #%d real input",n)
imagigraph(n) = sprintf("case #%d imaginary input",n)
realograph(n) = sprintf("case #%d real output",n)
imagograph(n) = sprintf("case #%d imaginary output",n)

set style line 1 lc rgb '#000066' lt 1 lw 2 pt 7 ps 1.5 #blue
set style line 2 lc rgb '#800000' lt 1 lw 2 pt 5 ps 1.5 #red
set style line 3 lc rgb '#006600' lt 1 lw 2 pt 5 ps 1.5 #green
set style line 4 lc rgb '#660033' lt 1 lw 2 pt 5 ps 1.5 #purple

do for [IDX=0:9] {
    outfile = sprintf('dft-images/dft-case%d-input.png',IDX)
    set output outfile
    plot datafile i IDX u 1:2 t realigraph(IDX) w l ls 1,\
    '' i IDX u 1:3 t imagigraph(IDX) w l ls 2

    outfile = sprintf('dft-images/dft-case%d-output.png',IDX)
    set output outfile
    plot datafile i IDX u 1:4 t realograph(IDX) w l ls 3,\
    '' i IDX u 1:5 t imagograph(IDX) w l ls 4
}
