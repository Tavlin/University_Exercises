#to start and use first exercise
if [[ "$1" == *-*2* ]]; then
    echo "start compiling exercise 2... "
    g++ -o sheet_2 sheet_2.cpp -Wall;

    echo "execute exercise 2...";
    echo "";
    ./sheet_2;
fi


if [[ "$1" == *-*3* ]]; then
    echo "start compiling exercise 3... "
    g++ -o sheet_3 sheet_3.cpp -Wall;

    echo "execute exercise 3...";
    echo "";
    ./sheet_3;

fi

if [[ "$1" == *-*4* ]]; then
    echo "start compiling exercise 4... "
    g++ -o 4_1_Hemmer 4_1_Hemmer.cpp -Wall;

    echo "execute exercise 4...";
    echo "";
    time ./4_1_Hemmer;


fi
