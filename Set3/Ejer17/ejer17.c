#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <openssl/aes.h>
#include <openssl/evp.h>

#define BLOCK_SIZE 16 // Tamaño de bloque de AES en bytes (16 bytes = 128 bits)
#define NUMERO_STRINGS 10 // Número de cadenas base64 predefinidas

unsigned char global_key[BLOCK_SIZE]; // La clave AES se guarda globalmente

// Función para generar bytes aleatorios ejer11
void random_bytes(unsigned char *buf, int len) {
    for (int i = 0; i < len; i++) buf[i] = rand() % 256; // Genera números aleatorios en el rango 0-255
}

// Función para agregar el relleno PKCS#7 adaptado de ejer9
void pkcs7_padding(unsigned char *data, int len, int *padded_len) {
    int padding = BLOCK_SIZE - (len % BLOCK_SIZE); // Calcula el número de bytes de relleno necesario
    for (int i = 0; i < padding; i++) {
        data[len + i] = padding; // Rellena los bytes con el valor del padding
    }
    *padded_len = len + padding; // Actualiza el tamaño de los datos con el relleno
}

// Función de cifrado AES en modo CBC ejer11
void aes_cbc_encrypt(const unsigned char *in, unsigned char *out, const unsigned char *key, unsigned char *iv, int len) {
    AES_KEY enc_key;
    AES_set_encrypt_key(key, 128, &enc_key); // Establece la clave de cifrado AES de 128 bits

    unsigned char local_iv[BLOCK_SIZE];
    memcpy(local_iv, iv, BLOCK_SIZE); // Copia el IV original para usarlo para desencriptar en el primer bloque

    for (int i = 0; i < len; i += BLOCK_SIZE) {
        for (int j = 0; j < BLOCK_SIZE; j++) {
            local_iv[j] ^= in[i + j]; // Realiza la operación XOR entre el IV y el bloque de texto plano
        }
        AES_encrypt(local_iv, out + i, &enc_key); // Realiza el cifrado del bloque
        memcpy(local_iv, out + i, BLOCK_SIZE); // Actualiza el IV con el resultado cifrado
    }
}

// Función de selección aleatoria de cadenas y cifrado CBC ejer15 + encriptar cbc
void encrypt_random_string(unsigned char *ciphertext, unsigned char *iv, int *ciphertext_len) {
    const char *strings[NUMERO_STRINGS] = {
        "MDAwMDAwTm93IHRoYXQgdGhlIHBhcnR5IGlzIGp1bXBpbmc=", 
        "MDAwMDAxV2l0aCB0aGUgYmFzcyBraWNrZWQgaW4gYW5kIHRoZSBWZWdhJ3MgYXJlIHB1bXBpbic=", 
        "MDAwMDAyUXVpY2sgdG8gdGhlIHBvaW50LCB0byB0aGUgcG9pbnQsIG5vIGZha2luZw==", 
        "MDAwMDAzQ29va2luZyBNQydzIGxpa2UgYSBwb3VuZCBvZiBiYWNvbg==", 
        "MDAwMDA0QnVybmluZyAnZW0sIGlmIHlvdSBhaW4ndCBxdWljayBhbmQgbmltYmxl", 
        "MDAwMDA1SSBnbyBjcmF6eSB3aGVuIEkgaGVhciBhIGN5bWJhbA==", 
        "MDAwMDA2QW5kIGEgaGlnaCBoYXQgd2l0aCBhIHNvdXBlZCB1cCB0ZW1wbw==", 
        "MDAwMDA3SSdtIG9uIGEgcm9sbCwgaXQncyB0aW1lIHRvIGdvIHNvbG8=", 
        "MDAwMDA4b2xsaW4nIGluIG15IGZpdmUgcG9pbnQgb2g=", 
        "MDAwMDA5aXRoIG15IHJhZy10b3AgZG93biBzbyBteSBoYWlyIGNhbiBibG93"
    };

    int index = rand() % NUMERO_STRINGS; // Elige una cadena aleatoria de las 10 disponibles
    unsigned char decoded[256];
    int len = strlen(strings[index]);
    int decoded_size = EVP_DecodeBlock(decoded, (unsigned char *)strings[index], len); // https://itoolkit.co/blog/2023/07/beginners-guide-to-base64-encoding-and-decoding-in-c-programming/

    int padded_size;
    pkcs7_padding(decoded, decoded_size, &padded_size); // Aplica el relleno PKCS#7 al texto decodificado

    if (global_key[0] == 0) {
        random_bytes(global_key, BLOCK_SIZE); // Si la clave global es 0, genera una clave aleatoria
    }

    random_bytes(iv, BLOCK_SIZE); // Genera un IV aleatorio
    aes_cbc_encrypt(decoded, ciphertext, global_key, iv, padded_size); // Cifra el texto usando AES en modo CBC
    *ciphertext_len = padded_size; // Devuelve el tamaño del texto cifrado
}

// Función de verificación del relleno y desencriptación CBC
int check_padding(unsigned char *ciphertext, int len, unsigned char *iv) {
    AES_KEY dec_key;
    AES_set_decrypt_key(global_key, 128, &dec_key); // Establece la clave de descifrado AES

    unsigned char decrypted[256];
    unsigned char local_iv[BLOCK_SIZE];
    memcpy(local_iv, iv, BLOCK_SIZE); // Copia el IV original para usarlo en el primer bloque

    for (int i = 0; i < len; i += BLOCK_SIZE) {
        AES_decrypt(ciphertext + i, decrypted + i, &dec_key); // Descifra el bloque
        for (int j = 0; j < BLOCK_SIZE; j++) {
            decrypted[i + j] ^= local_iv[j]; // Realiza la operación XOR entre el bloque descifrado y el IV
        }
        memcpy(local_iv, ciphertext + i, BLOCK_SIZE); // Actualiza el IV con el bloque cifrado actual
    }

    int padding = decrypted[len - 1]; // Verifica el relleno en el último byte
    if (padding <= 0 || padding > BLOCK_SIZE) return 0; // Si el relleno es inválido, retorna 0
    for (int i = len - padding; i < len; i++) {
        if (decrypted[i] != padding) return 0; // Si algún byte del relleno es incorrecto, retorna 0
    }
    return 1; // Si todo está bien, retorna 1
}

int main() {
    srand(time(NULL)); // Inicializa la semilla para los números aleatorios

    unsigned char ciphertext[256]; // Buffer para el texto cifrado
    unsigned char iv[BLOCK_SIZE];  // Buffer para el IV
    int ciphertext_len = 0;

    encrypt_random_string(ciphertext, iv, &ciphertext_len); // Cifra una cadena aleatoria y guarda el IV
    int valido = check_padding(ciphertext, ciphertext_len, iv); // Verifica si el relleno es válido

    if (valido) {
        printf("Relleno válido\n"); // Imprime si el relleno es válido
    } else {
        printf("Relleno inválido\n"); // Imprime si el relleno es inválido
    }

    return 0;
}

