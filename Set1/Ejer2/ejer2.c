#include <stdio.h>
#include <string.h>

// Función para convertir una cadena hexadecimal a un arreglo de bytes (obtenida del ejercicio 1)
void hexToBytes(const char *hex, unsigned char *output) {
    int len = strlen(hex) / 2;  // La longitud de la cadena en bytes
    for (int i = 0; i < len; i++) {
        sscanf(hex + 2 * i, "%2hhx", &output[i]);  // Convertir cada par de caracteres hexadecimales a un byte
    }
}

// Función para realizar la operación XOR sobre dos cadenas hexadecimales
void funcion_xor(const char *hex1, const char *hex2) {
    
    int len = strlen(hex1) / 2;  // La longitud de la cadena en bytes (tiene que ser la misma para ambas cadenas)
    
    unsigned char bytes1[len];  // Arreglo estático para almacenar los bytes de la primera cadena
    unsigned char bytes2[len];  // Arreglo estático para almacenar los bytes de la segunda cadena
    unsigned char resultado[len];  // Arreglo estático para almacenar el resultado

    // Convertir las cadenas hexadecimales a bytes
    hexToBytes(hex1, bytes1);
    hexToBytes(hex2, bytes2);

    // Realizar la operación XOR byte a byte
    for (int i = 0; i < len; i++) {
        resultado[i] = bytes1[i] ^ bytes2[i];  // Operación XOR byte a byte
    }

    // Imprimir el resultado en formato hexadecimal
    for (int i = 0; i < len; i++) {
        printf("%02x", resultado[i]);  // Imprimir cada byte en formato hexadecimal
    }
    printf("\n");
}

// Función principal
int main() {
    const char *hex1 = "1c0111001f010100061a024b53535009181c";  // Cadena hexadecimal 1
    const char *hex2 = "686974207468652062756c6c277320657965";  // Cadena hexadecimal 2
    
    // Llamar a la función para realizar el XOR
    funcion_xor(hex1, hex2);

    return 0;
}
