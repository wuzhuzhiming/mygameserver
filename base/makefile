#==========project==========
BINDIR = ../bin/
PROJECT = base
TARGET = $(BINDIR)$(PROJECT).bin
CC = g++
#===========================


#==========config===========
CFLAGS = -g -Wall -Werror -I../include -D_DEBUG

LFLAGS = -L.

CPPS = $(shell find ./src -name *.cpp)
OBJS = $(CPPS:.cpp=.o)
#===========================


#==========compile==========

%.o : %.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

all : $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) $(LFLAGS)	$(OBJS) -o $(TARGET)

#.PHONY: clean
clean:
	rm -f $(OBJS)
	rm -f $(TARGET)
#===========================


#==========visual===========
TARGETTYPE :=APP
TARGETNAME :=base.bin
#===========================
