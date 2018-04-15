

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

