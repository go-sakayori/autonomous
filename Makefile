# Makefile for GLUT

CC = g++
WARN = -Wall -g

#LDLIBS =  -lglui -lglut -lGLU -lGL -lXmu -lXi -lXext -lX11 -lGLEW -lm -pthread

OBJ = \
	main.o \
	grid_map.o \
	path_plan.o \
	scan.o \
	#matrix.o #socket_gen.o
DEFINES =

CFLAGS = $(WARN) $(DEFINES) 

TARGET = run

$(TARGET) : $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)
.c.o :
	$(CC) $(CFLAGS) -o $@ -c $<

clean :
	-@rm -f $(OBJ) $(TARGET) run.*
ct :
	rm -rf *~

