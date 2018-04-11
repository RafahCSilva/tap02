#!/bin/bash

cd src/
g++ rafaelcardoso_tap02.cpp -o rafaelcardoso_tap02.exe -std=c++11
./rafaelcardoso_tap02.exe < ../scripts/in/file94 > eae.txt 2> vish.txt

#g++ rafaelcardoso_tap02.cpp -o ../scripts/rafaelcardoso_tap02.exe -std=c++11
#cd ../scripts/
#chmod +x grade.bash
#./grade.bash ./rafaelcardoso_tap02.exe
#cd ..
