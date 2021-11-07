# main: myalloc.c
# 	gcc -ggdb -o main myalloc.c

# clean:
# 	rm -rf *.o main
	

main: rsa.c
	gcc -ggdb -o main rsa.c -lm

clean:
	rm -rf *.o main