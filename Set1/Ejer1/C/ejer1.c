// Función hextobytes basado en: https://stackoverflow.com/questions/3408706/hexadecimal-string-to-byte-array-in-c
//Función base64Encoder basado en el ejemplo de GeeksforGeeks para codificar una cadena ASCII en formato Base64 (https://www.geeksforgeeks.org/encode-ascii-string-base-64-format/), adaptado para convertir una cadena hexadecimal a Base64.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 1000

// Convierte una cadena hexadecimal a un arreglo de bytes
void hexToBytes(const char *hex, unsigned char *output) {
    int len = strlen(hex);
    for (int i = 0; i < len / 2; i++) {
        sscanf(hex + 2 * i, "%2hhx", &output[i]);
    }
}

// Función para codificar una cadena de entrada en formato Base64
char* base64Encoder(unsigned char input_str[], int len_str) {
    char char_set[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";  // Conjunto de caracteres Base64
    char *res_str = (char *) malloc(SIZE * sizeof(char));  // Cadena resultante donde se almacenará la salida codificada
    
    int index, no_of_bits = 0, padding = 0, val = 0, count = 0, temp;
    int i, j, k = 0;
    
    // Bucle que toma 3 caracteres de entrada a la vez
    for (i = 0; i < len_str; i += 3) {
        val = 0, count = 0, no_of_bits = 0;

        // Almacena los 3 caracteres en la variable 'val'
        for (j = i; j < len_str && j <= i + 2; j++) {
            val = val << 8;
            val = val | input_str[j];
            count++;
        }

        no_of_bits = count * 8;  // Calcula cuántos bits hay en esta parte
        padding = no_of_bits % 3;  // Calcula el padding necesario

        // Extrae los bits de 6 en 6 y encuentra el valor de cada bloque
        while (no_of_bits != 0) {
            if (no_of_bits >= 6) {
                temp = no_of_bits - 6;
                index = (val >> temp) & 63;
                no_of_bits -= 6;         
            }
            else {
                temp = 6 - no_of_bits;
                index = (val << temp) & 63; 
                no_of_bits = 0;
            }
            res_str[k++] = char_set[index];  // Asigna el carácter correspondiente en el resultado
        }
    }

    // Agrega el padding (=) si es necesario
    for (i = 1; i <= padding; i++) {
        res_str[k++] = '=';
    }

    res_str[k] = '\0';  // Añade el carácter de terminación de cadena

    return res_str;
}

// Código principal
int main() {
    const char *hex_str = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";  // Cadena hexadecimal de entrada
    int len_str = strlen(hex_str) / 2;  // La longitud de la cadena de bytes (cada 2 caracteres hexadecimales representan 1 byte)

    // Convierte la cadena hexadecimal a bytes
    unsigned char raw_bytes[len_str];
    hexToBytes(hex_str, raw_bytes);

    // Imprime la cadena de entrada y la cadena codificada en Base64
    printf("Cadena de entrada en hexadecimal: %s\n", hex_str);
    printf("Cadena codificada en Base64: %s\n", base64Encoder(raw_bytes, len_str));

    return 0;
}


