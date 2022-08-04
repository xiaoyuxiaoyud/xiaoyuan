CC=gcc
BIN=edu.bin
OBJ=main.o admin.o process.o student.o teacher.o tools.o

all: main.o admin.o process.o student.o teacher.o tools.o
	$(CC) main.c admin.c process.c student.c teacher.c tools.c -o $(BIN)

main.o : main.c admin.h process.h student.h teacher.h tools.h mis.h
	$(CC) -c main.c
admin.o : admin.c admin.h process.h tools.h mis.h
	$(CC) -c admin.c
process.o : process.c process.h mis.h tools.h
	$(CC) -c process.c
student.o : student.c student.h mis.h tools.h
	$(CC) -c student.c
teacher.o : teacher.c teacher.h mis.h tools.h
	$(CC) -c teacher.c
tools.o : tools.c tools.h mis.h
	$(CC) -c tools.c

clean:
	rm -rf $(BIN) $(OBJ)
