

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
