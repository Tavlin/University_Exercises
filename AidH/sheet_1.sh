
echo ""; #for a new line, to look a bit smoother
echo "Welcome to the first exercise.";

#print out all lines with "hexe" in it
echo "";
echo "grep Hexe HaenselUndGretel:";
grep Hexe HaenselUndGretel; 
echo "";

# to see options for wc and what wc does
#not to be confused with the toilet!
man wc;

# using | to combine to commands
# wc -l counts the lines
echo "grep Hexe HaenselUndGretel | wc -l:";
grep  Hexe HaenselUndGretel | wc -l;
echo "";
echo "That's it alrdy";
