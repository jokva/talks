set terminal png

set xlabel "n"
set ylabel "operations"

f(x) = 0.01 * x**3 + 10 * x + 5
g(x) = 2000 * x**2 + 10

plot [0:ARG1] \
    f(x) title "O(n³)", \
    g(x) title "O(n²)"
