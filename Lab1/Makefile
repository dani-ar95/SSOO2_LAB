DIROBJ := obj/
DIREXE := exec/
DIRHEA := include/
DIRSRC := src/

CFLAGS := -I$(DIRHEA) -c -Wall -ansi -std=c99
LDLIBS := -lpthread -lrt
CC := gcc

all : dirs manager PA PB PC PD Daemon

dirs:
	mkdir -p $(DIROBJ) $(DIREXE)

manager: $(DIROBJ)manager.o 
	$(CC) -o $(DIREXE)$@ $^ $(LDLIBS)

PA: $(DIROBJ)PA.o 
	$(CC) -o $(DIREXE)$@ $^ $(LDLIBS)

PB: $(DIROBJ)PB.o 
	$(CC) -o $(DIREXE)$@ $^ $(LDLIBS)

PC: $(DIROBJ)PC.o 
	$(CC) -o $(DIREXE)$@ $^ $(LDLIBS)

PD: $(DIROBJ)PD.o 
	$(CC) -o $(DIREXE)$@ $^ $(LDLIBS)

Daemon: $(DIROBJ)Daemon.o 
	$(CC) -o $(DIREXE)$@ $^ $(LDLIBS)

$(DIROBJ)%.o: $(DIRSRC)%.c
	$(CC) $(CFLAGS) $^ -o $@

solution:
	./$(DIREXE)manager
	./$(DIREXE)Daemon

clean : 
	rm -rf *~ core $(DIROBJ) $(DIREXE) $(DIRHEA)*~ $(DIRSRC)*~ estudiantes backup log.txt
