#to start and use first exercise
if [[ "$1" == *-*2* ]]; then
    echo "start compiling exercise... "
    g++ -o sheet_2 sheet_2.cpp -Wall;

    echo "execute exercise...";
    echo "";
    ./sheet_2;
fi


if [[ "$1" == *-*3* ]]; then
    echo "start compiling exercise... "
    g++ -o sheet_3 sheet_3.cpp -Wall;

    echo "execute exercise...";
    echo "";
    ./sheet_3;


fi
