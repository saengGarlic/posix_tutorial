TARGET = matrix
OBJ = main.o matrix_scaled.o
LFLAGS = -pthread -lpthread
CFLAGS = -D_REENTRANT

all: $(OBJ)
	gcc -o $(TARGET) $(LFLAGS) $(OBJ) -lm

main.o: main.c
	gcc -c $(CFLAGS) main.c

matrix.o: matrix.c
	gcc -c $(CFLAGS) matrix_scaled.c

clean:
	rm -r *.o $(TARGET)
