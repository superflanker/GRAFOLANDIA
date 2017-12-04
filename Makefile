CC = gcc
CFLAGS  = -lm -g -Wall
CFILES = grafolandia.c grafolib.c
# typing 'make' will invoke the first target entry in the file 
# (in this case the default target entry)
# you can name this target entry anything, but "default" or "all"
# are the most commonly used names by convention
#
default: GRAFOLANDIA

# To create the executable file count we need the object files
# countwords.o, counter.o, and scanner.o:
#
GRAFOLANDIA: grafolib.h grafolib.c 
	$(CC) ${CFILES} $(CFLAGS) -o GRAFOLANDIA

clean: 
	$(RM) GRAFOLANDIA
