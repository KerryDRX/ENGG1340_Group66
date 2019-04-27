main.o:main.cpp printed_messages.h functionalities.h
	g++ -c main.cpp

printed_messages.o:printed_messages.h printed_messages.cpp
	g++ -c printed_messages.cpp

functionalities.o:functionalities.h functionalities.cpp printed_messages.h
	g++ -c functionalities.cpp

main:main.o printed_messages.o functionalities.o
	g++ main.o printed_messages.o functionalities.o -o main
