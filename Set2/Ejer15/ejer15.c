#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Función que valida y elimina el relleno PKCS#7
int validar_y_eliminar_relleno(unsigned char *datos, int longitud) {
    int relleno = datos[longitud - 1];

    if (relleno < 1 || relleno > longitud) {
        return -1; // Relleno inválido
    }

    for (int i = longitud - relleno; i < longitud; i++) {
        if (datos[i] != relleno) { // \x04\x04\x04\x04
            return -1; // Relleno inválido
        }
    }

    datos[longitud - relleno] = '\0'; // Asegurar que acaba en \0
    return longitud - relleno;
}

int main() {
    unsigned char datos[][20] = {
        "ICE ICE BABY\x04\x04\x04\x04",  // Caso válido
        "ICE ICE BABY\x05\x05\x05\x05",  // Caso inválido
        "ICE ICE BABY\x01\x02\x03\x04"   // Caso inválido
    };

    int num_casos = sizeof(datos) / sizeof(datos[0]);

    for (int i = 0; i < num_casos; i++) {
        int longitud = strlen((char *)datos[i]); // Obtener longitud real del string

        int nueva_longitud = validar_y_eliminar_relleno(datos[i], longitud);

        printf("Caso %d: ", i + 1);
        if (nueva_longitud != -1) {
            printf("Relleno válido, resultado: %s\n", datos[i]);
        } else {
            printf("Relleno inválido\n");
        }
    }

    return 0;
}
