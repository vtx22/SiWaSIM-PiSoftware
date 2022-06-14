CPP	= g++
CPPFLAGS	= -std=c++17 -Wall -w -I/usr/include/python3.9 -pthread -lpigpio -lpython3.9

LDFLAGS	= -L$(DESTDIR)$(PREFIX)/lib
LDLIBS    = -pthread -lpigpio -lpython3.9

SRC	=	Configuration.cpp GPIO.cpp I2C.cpp IABoard.cpp MaterialFlow.cpp Modbus.cpp PCB.cpp Simulator.cpp SIWAREX.cpp UART.cpp utility.cpp 
OBJ	=	$(SRC:.cpp=.o)

all:	siwasim

siwasim:	$(OBJ) siwasim.cpp
	$Q echo [Link]
	$Q $(CC) -o $@ siwasim.o $(OBJ) $(LDFLAGS) $(LDLIBS)