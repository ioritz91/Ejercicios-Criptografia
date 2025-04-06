#include <stdio.h>
#include <string.h>

void pkcs7_pad(char *data, int block_size) {
    int data_len = strlen(data);
    int padding_len = block_size - (data_len % block_size); //20 - (16 % 20) = 4, 16 - 16 % 16 = 0

    // Agregar el padding
    if (padding_len != block_size){
    for (int i = 0; i < padding_len; i++) {
        data[data_len + i] =  padding_len; //<- aquí se usa el valor 4 como byte, NO como carácter '4'
    }

    // Asegurar que el texto esté terminado con un \0
    data[data_len + padding_len] = '\0';
    }
}

void print_text_with_padding(char *data) {
    for (int i = 0; i < strlen(data); i++) {
        if (data[i] >= 32 && data[i] <= 126) { // ASCII imprimibles
            // Si el carácter es imprimible, lo imprimimos directamente
            printf("%c", data[i]);
        } else {
            // Si no es imprimible, mostramos como \xNN
            printf("\\x%02x", (unsigned char) data[i]); //imprimir en el formato del ejemplo
        }
    }
}

void main() {
    char data[256];  // para almacenar el texto
    int block_size;

    // Solicitar texto y tamaño del bloque
    printf("Introduce el texto: ");
    fgets(data, sizeof(data), stdin);  // Lee toda la línea incluyendo espacios
    data[strlen(data) - 1] = '\0';     // Eliminar el salto de línea (\n) al final

    printf("Introduce el tamaño del bloque (en bytes): ");
    scanf("%d", &block_size);

    // Llamar a la función de padding
    pkcs7_pad(data, block_size);

    // Mostrar el resultado con padding en el formato esperado
    printf("Texto con padding: ");
    print_text_with_padding(data);
    printf("\n");
}

