#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

int encrypt(char message, int e, int n) {
    printf("pow: %f\n", pow((int) message, e));
    return (int) pow((int) message, e) % n;
}

char *encode(char message[], int e, int n) {
    printf("Encoding message: %s\n", message);
    
    size_t message_size = strlen(message);
    char *encoded = malloc(message_size);

    for(int c = 0; c < message_size; c++) {
        // encoded[c] = 'a';
        // message[c] = encrypt(message[c], e, n);
        printf("%d ", encrypt(message[c], e, n));
    }
    printf("\n");

    return encoded;

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
        int n = 1;
        prime = pow(n, 2) + n + 41; 
    } while (!is_prime(prime));
    
    return prime;
}

int pq_key(int *p, int *q) {
    *p = get_prime();
    *q = get_prime();
    return abs(*p * *q);
}

int gcd(int a, int b) {
    while(a != b) {
        if(a > b)
            a -= b;
        else
            b -= a;
    }
    return a;
}

int e_key(int p, int q) {
    int r;
    int phi_pq = (p - 1) * (q - 1);
    int e;
    int g = 0;

    while(g != 1) {
        e = rand() & 50;
        g = gcd(e, phi_pq);
        printf("e=%d, gcd=%d\n", e, g);
    }
    
    return abs(e);
}

int mod_inv(int e, int m)
{
    for (int x = 1; x < m; x++)
        if (((e%m) * (x%m)) % m == 1)
            return x;
}

int main(int argc, char **argv) {
    printf("Starting custom RSA implementation\n");
    srand(time(0));

    int p;
    int q;

    int n = pq_key(&p, &q);
    int e = e_key(p, q);
    int secret_key = mod_inv(e, n);

    printf("[Receiver] p=%d, q=%d, n=%d, e=%d, secret_key=%d\n", p, q, n, e, secret_key);

    char message[] = "This is my secret message";
    char *secret_message = encode(message, e, n);
    printf("Encoded string: %s\n", secret_message);
    return 0;
}