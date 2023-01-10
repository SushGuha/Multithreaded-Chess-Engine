all: compile link

compile: 
	g++ -c -pthread -std=c++11 ./thc.cpp frontend.cpp -IC:\SFML-2.5.1\include

link: 
	g++ thc.o frontend.o -o frontend -LC:\SFML-2.5.1\lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -lsfml-audio
