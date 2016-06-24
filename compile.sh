#!/bin/bash

echo "Compiling..."
echo " "
cd src/

g++ -c main.cpp Walls.cpp Snake.cpp StartMenu.cpp HighScores.cpp -I/Documents/SFML/SFML_SRC/include 


echo "Linking..."
echo " "

if [ -e main.cpp~ ];
then
    rm main.cpp~
fi

mv *.o ../linkers
cd ../linkers

g++ main.o Walls.o Snake.o StartMenu.o HighScores.o -o slither -L/Documents/SFML/SFML_SRC/lib -lsfml-graphics -lsfml-window -lsfml-system

mv slither ../
cd ../

if [ -e compile.sh~ ] ;
then 
    rm compile.sh~ 
fi

cd include/
if [ -e *.hh~ ];
then
    rm *.hh~
fi

cd ..
echo "Executing..."
echo " "
./slither

