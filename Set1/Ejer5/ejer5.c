#include <stdio.h>
#include <string.h>

// Función para cifrar con XOR de clave repetitiva
void repeatingKeyXOR(const char *text, const char *key, char *encriptado) {
    int textLen = strlen(text);
    int keyLen = strlen(key);

    for (int i = 0; i < textLen; i++) {
        encriptado[i] = text[i] ^ key[i % keyLen]; // XOR con la clave en bucle [0],[1],[2] [0],[1],[2]...
        printf("%02x", encriptado[i]); // Imprime en hexadecimal
    }
    printf("\n");
}


int main() {
    char text[] = "Burning 'em, if you ain't quick and nimble\n"
                  "I go crazy when I hear a cymbal";
    char key[] = "ICE";
    int textLen = strlen(text);
    char encriptado[textLen]; // Array para guardar el resultado

    repeatingKeyXOR(text, key, encriptado);    

    return 0;
}
