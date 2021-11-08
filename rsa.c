#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

int * encrypt(char *message, int e, int n) {
    
    size_t string_len = strlen(message);
    printf("String size: %ld\n", string_len);
    int *encoded = malloc((string_len * sizeof(int))); // 12 * 4B = 48B
    printf("Encoding size: %ld\n", string_len * sizeof(int));

    for(int i = 0; i < string_len; ++i) {
        int char_val = message[i];
        int encoded_val = (int) pow((int) char_val, e) % n;
        encoded[i] = encoded_val;
        printf("%c %d -> %d\n", message[i], char_val, encoded_val);
    }

    printf("Encoded size: %ld\n", sizeof(encoded));
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
        int n = rand() % 50;
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

int generate_e(int p, int q) {
    int r;
    int phi_pq = (p - 1) * (q - 1);
    int e = 3;
    int g = 0;
    
    while(g != 1 && e > 3 && e < 65539) {
        e = (rand() % 6) + 1;
        g = gcd(e, phi_pq);
        // printf("e=%d, gcd=%d\n", e, g);
    }
    
    return abs(e);
}

int mod_inv(int e, int m)
{
    for (int x = 1; x < m; x++)
        if (((e % m) * (x % m)) % m == 1)
            return x;
}

int main(int argc, char **argv) {
    printf("Starting custom RSA implementation\n");
    srand(time(0));

    int p;
    int q;
    int n = pq_key(&p, &q);
    printf("p=%d, q=%d, n=%d\n", p, q, n);
    
    int e = generate_e(p, q);
    int secret_key = mod_inv(e, n);
    printf("e=%d, secret_key=%d\n", e, secret_key);
    
    char *string = "Hello, World";
    int *encoded_data = encrypt(string, e, n);

    size_t encoded_len = sizeof(encoded_data);
    printf("SIZE IS %ld\n", encoded_len);
    for(int i = 0; i < encoded_len; ++i) {
        // printf("ENCODED: %d\n", encoded_data[i]);
    }
    // printf("\n");

    return 0;
}