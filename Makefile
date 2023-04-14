CC = g++

CFLAGS = -Wall -g

INCLUDES =

LFLAGS = 

LIBS =

SRCS = TP2.cpp

OBJS = $(SRCS:.cpp=.o)

MAIN = TP2

all: $(MAIN)

$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)