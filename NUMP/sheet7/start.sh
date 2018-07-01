echo "start compiling"
echo ""
g++ -std=c++14 -c GetSolution.cxx
g++ -std=c++14 -c JacobiRotation.cxx
g++ -std=c++14 -o a JacobiRotation.o GetSolution.o main.cxx
echo ""
echo "stat working..."
echo ""
time ./a
time root -l -b -q plot.C\+\+\(\)
