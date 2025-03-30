#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <openssl/aes.h>

#define BLOCK_SIZE 16 // Tamaño de bloque de AES en bytes (16 bytes = 128 bits)

// Genera bytes aleatorios y los almacena en el buffer proporcionado
void random_bytes(unsigned char *buf, int len) {
    for (int i = 0; i < len; i++) buf[i] = rand() % 256; // 0-255
}

// https://stackoverflow.com/questions/9889492/how-to-do-encryption-using-aes-in-openssl
// Cifra los datos en modo ECB 
void aes_ecb_encrypt(const unsigned char *in, unsigned char *out, const unsigned char *key, int len) {
    AES_KEY enc_key;
    AES_set_encrypt_key(key, 128, &enc_key); // Establece la clave de cifrado AES de 128 bits
    
    // Cifra la entrada en bloques de 16 bytes
    for (int i = 0; i < len; i = i + BLOCK_SIZE) {
        AES_encrypt(in + i, out + i, &enc_key); // Cifra bloque por bloque
    }
}

// Cifra los datos en modo CBC
void aes_cbc_encrypt(const unsigned char *in, unsigned char *out, const unsigned char *key, unsigned char *iv, int len) {
    AES_KEY enc_key;
    AES_set_encrypt_key(key, 128, &enc_key); // Establece la clave de cifrado AES de 128 bits

    // Procesa los datos en bloques de 16 bytes
    for (int i = 0; i < len; i = i + BLOCK_SIZE) {
        // Realiza XOR entre el IV y el bloque de entrada
        for (int j = 0; j < BLOCK_SIZE; j++) {
            iv[j] ^= in[i + j];
        }
        
        // Cifra el bloque con AES
        AES_encrypt(iv, out + i, &enc_key);
        
        // El bloque cifrado se convierte en el nuevo IV
        memcpy(iv, out + i, BLOCK_SIZE);
    }
}

// Detecta si el cifrado es ECB comparando bloques repetidos
int detect_ecb(const unsigned char *data, int len) {
    for (int i = 0; i < len - BLOCK_SIZE; i = i + BLOCK_SIZE) {
        for (int j = i + BLOCK_SIZE; j < len; j = j + BLOCK_SIZE) {
            if (!memcmp(data + i, data + j, BLOCK_SIZE)) return 1; // Si hay bloques iguales, es ECB
        }
    }
    return 0; // Si no hay bloques repetidos, es CBC
}

// Función que cifra los datos con una clave aleatoria y decide aleatoriamente entre ECB y CBC
void encryption_oracle(const unsigned char *input, int len) {
    unsigned char key[BLOCK_SIZE], iv[BLOCK_SIZE];
    int pad1 = 5 + rand() % 6, pad2 = 5 + rand() % 6; // Bytes aleatorios antes y después del mensaje
    int total = len + pad1 + pad2; // Longitud total del mensaje con padding

    unsigned char *padded = malloc(total);  // Asignar memoria dinámica para padded
    unsigned char *encrypted = malloc(total);  // Asignar memoria dinámica para encrypted

    random_bytes(key, BLOCK_SIZE); // Genera una clave aleatoria
    random_bytes(iv, BLOCK_SIZE); // Genera un IV aleatorio (para CBC)
    random_bytes(padded, pad1); // Agrega padding aleatorio al inicio
    memcpy(padded + pad1, input, len); // Copia el mensaje al centro del padding
    random_bytes(padded + pad1 + len, pad2); // Agrega padding aleatorio al final

    // Decide aleatoriamente si usar ECB o CBC
    if (rand() % 2) {
        printf("ECB usado\n");
        aes_ecb_encrypt(padded, encrypted, key, total);
    } else {
        printf("CBC usado\n");
        aes_cbc_encrypt(padded, encrypted, key, iv, total);
    }

    // Detecta y muestra qué modo de cifrado fue utilizado
    if (detect_ecb(encrypted, total)) {
        printf("Detectado: ECB\n");
    } else {
        printf("Detectado: CBC\n");
    }    

    // Liberar la memoria
    free(padded);
    free(encrypted);
}

int main() {
    srand(time(NULL)); // Inicializa la semilla para generar números aleatorios
    unsigned char input[] = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
    encryption_oracle(input, strlen(input)); // Ejecuta la función de cifrado
    return 0;
}

