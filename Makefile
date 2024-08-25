build: main.cpp
	clang++ -std=c++17 main.cpp circle.cpp -o a.out -I /Library/Frameworks/SDL2.framework/Headers -F /Library/Frameworks -framework SDL2 -rpath /Library/Frameworks