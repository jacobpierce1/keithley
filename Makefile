all: keithley.cpp
	g++ -std=c++11 -Wall -o run_keithley keithley.cpp

clean: 
	rm run_keithley
	rm *~
