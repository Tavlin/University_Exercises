

#to start and use first exercise
if [[ "$1" == *-*1* ]]; then
    echo "start compiling exercise... "
    g++ -o sheet_1 sheet_1.cpp -Wall;

    echo "execute exercise...";
    echo "";
    ./sheet_1;

    #mkdir -p GoldenRatio
    #root -q -l -b goldenratio.C\+\(\)

fi

if [[ "$1" == *-*2* ]]; then

    rm -r Pendulum
    mkdir -p Pendulum

    echo "start compiling exercise... "
    root -l -b -q sheet_2_2.C\+\(\)

fi

if [[ "$1" == *-*3* ]]; then

    rm -r Kepler
    mkdir -p Kepler

    echo "start compiling exercise... "
    root -l -b -q sheet_3_1.C\+\(\)

fi

if [[ "$1" == *-*4* ]]; then

    # rm -r QM_with_Potential
    # mkdir -p QM_with_Potential

    echo "start compiling exercise... "
    root -l -b -q sheet_4_1.C\+\(\)

fi

if [[ "$1" == *-*5* ]]; then

    # rm -r QM_with_Potential
    # mkdir -p QM_with_Potential

    echo "start compiling exercise... "
    root -l -b -q sheet_5_1.C\+\(\)
    # g++ -o a sheet_5_1_2.cpp


fi


if [[ "$1" == *-*6* ]]; then

    echo "start compiling exercise... "
    g++ -std=c++14 -o a ConjGrad.cpp
    ./a
    root -l -q -b plot.C\+\(\)

fi
