OBJS	= Digital_Logic_Circuit_Simulator.o
SOURCE	= Digital_Logic_Circuit_Simulator.cpp
HEADER	= AndGate.h Circuit.h LogicGate.h Menu.h NandGate.h NorGate.h OrGate.h
OUT	= program.out
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

Digital_Logic_Circuit_Simulator.o: Digital_Logic_Circuit_Simulator.cpp
	$(CC) $(FLAGS) Digital_Logic_Circuit_Simulator.cpp 


clean:
	rm -f $(OBJS) $(OUT)
