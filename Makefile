# Makefile for GLUT

CC = g++
WARN = -Wall

#LDLIBS =  -lglui -lglut -lGLU -lGL -lXmu -lXi -lXext -lX11 -lGLEW -lm -pthread

OBJ = \
	main.o \
	grid_map.o \
	path_plan.o \
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

main.o: common.h grid_map.h path_plan.h  
path_plan.o: path_plan.c path_plan.h
grid_map.o: grid_map.c grid_map.h
