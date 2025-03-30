#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Función que valida y elimina el relleno PKCS#7
int validar_y_eliminar_relleno(unsigned char *datos, int longitud) {
    // Obtener el valor del último byte, que indica el tamaño del relleno
    int relleno = datos[longitud - 1];
    
    // Verificar si el relleno es válido: debe ser mayor que 0 y no mayor que la longitud de los datos
    if (relleno < 1 || relleno > longitud) {
        printf("Relleno inválido\n");
        return -1; // Si el relleno no es válido, retorna -1
    }

    // Verificar que todos los bytes del relleno tengan el valor esperado
    for (int i = longitud - relleno; i < longitud; i++) {
        if (datos[i] != relleno) {
            printf("Relleno inválido\n");
            return -1; // Si algún byte no coincide, el relleno es inválido
        }
    }

    // Eliminar el relleno, sustituyendo el último byte de relleno por el carácter nulo
    datos[longitud - relleno] = '\0';
    
    // Retornar la nueva longitud de los datos sin el relleno
    return longitud - relleno;
}

int main() {
    // Ejemplo con un mensaje válido y un relleno válido
    unsigned char datos_validos[] = "ICE ICE BABY\x04\x04\x04\x04"; // Mensaje con relleno PKCS#7 válido
    int longitud = sizeof(datos_validos) - 1; // Obtener la longitud total de los datos (sin contar el '\0')
    
    // Llamar a la función para validar y eliminar el relleno
    int nueva_longitud = validar_y_eliminar_relleno(datos_validos, longitud);

    // Si la longitud nueva es válida, mostrar el mensaje sin relleno
    if (nueva_longitud != -1) {
        printf("Relleno válido, resultado: %s\n", datos_validos);
    }

    // Ejemplo con un mensaje que tiene un relleno inválido
    unsigned char datos_invalidos[] = "ICE ICE BABY\x05\x05\x05\x05"; // Mensaje con relleno PKCS#7 inválido
    longitud = sizeof(datos_invalidos) - 1; // Obtener la longitud total de los datos (sin contar el '\0')
    
    // Llamar a la función para validar y eliminar el relleno
    nueva_longitud = validar_y_eliminar_relleno(datos_invalidos, longitud);

    unsigned char datos_invalidos2[] = "ICE ICE BABY\x01\x02\x03\x04"; // Mensaje con relleno PKCS#7 inválido
    longitud = sizeof(datos_invalidos2) - 1; // Obtener la longitud total de los datos (sin contar el '\0')
    
    // Llamar a la función para validar y eliminar el relleno
    nueva_longitud = validar_y_eliminar_relleno(datos_invalidos2, longitud);


    return 0;
}
