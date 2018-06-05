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
    g++ -o 4_1_Hemmer 4_1_Tavlin.cpp -Wall;

    echo "execute exercise 4...";
    echo "";
    time ./4_1_Tavlin;


fi

if [[ "$1" == *-*5* ]]; then
    echo "start compiling exercise 5 No. 1... "
    g++ -o 5_1_Hemmer 5_1_Tavlin.cpp -Wall -std=c++11;

    echo "execute exercise 5 No.1 ...";
    echo "";
    time ./5_1_Tavlin;


fi
