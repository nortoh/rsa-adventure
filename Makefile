main: rsa.c
	gcc -ggdb -o main rsa.c -lm

clean:
	rm -rf *.o main