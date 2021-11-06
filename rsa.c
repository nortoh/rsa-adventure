#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

char* encode(char *message) {
    printf("Encoding message: %s\n", message);

}

void decode() {

}

int is_prime(int prime) {
    if (prime <= 1) return 0;
 
    for (int i = 2; i <= sqrt(prime); i++)
        if (prime % i == 0)
            return 0;

    return 1;
}

int get_prime() {
    int prime;

    do {
        int n = rand() % 100;
        prime = pow(n, 2) + n + 41; 
    } while (!is_prime(prime));
    
    printf("Generarting prime: %d\n", prime);
    return prime;
}

int pq_key(int *p, int *q) {
    *p = get_prime();
    *q = get_prime();
    return *p * *q;
}


int main(int argc, char **argv) {
    printf("Starting custom RSA implementation\n");
    srand(time(NULL));

    if(is_prime(3)) {
        printf("This number is prime\n");
    }

    // printf("Generarting prime: %d\n", get_prime());

    int p;
    int q;
    int result = pq_key(&p, &q);

    printf("p=%d, q=%d, n=%d\n");


    char *message = "This is my secret message";
    char *secret_message = encode(message);
    return 0;
}