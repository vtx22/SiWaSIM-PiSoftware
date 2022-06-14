CXX=g++
RM=rm -f

CPPFLAGS=-std=c++17 -Wall -w -I/usr/include/python3.9

LDLIBS=-pthread -lpigpio -lpython3.9

SRC=siwasim.cpp Configuration.cpp GPIO.cpp I2C.cpp IABoard.cpp MaterialFlow.cpp Modbus.cpp PCB.cpp Simulator.cpp SIWAREX.cpp UART.cpp utility.cpp 
OBJ=$(SRC:.cpp=.o)

all:	siwasim clean

depend: .depend

.depend: $(SRCS)
	$(RM) ./.depend
	$(CXX) $(CPPFLAGS) -MM $^>>./.depend;

siwasim:	$(OBJ)
	$Q echo [Link]
	$Q $(CXX) -o $@ $(OBJ) $(LDLIBS)

clean:
	$(RM) $(OBJ)

distclean: clean
	$(RM) *~ .depend

include .depend