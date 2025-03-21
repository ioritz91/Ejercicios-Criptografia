#include <stdio.h>
#include <string.h>

// Función para cifrar con XOR de clave repetitiva
void repeatingKeyXOR(const char *text, const char *key, char *encriptado) {
    int textLen = strlen(text);
    int keyLen = strlen(key);

    for (int i = 0; i < textLen; i++) {
        encriptado[i] = text[i] ^ key[i % keyLen]; // XOR con la clave en bucle
    }
}

// Función para imprimir en formato hexadecimal
void imprimirHex(const char *dato, int len) {
    for (int i = 0; i < len; i++) {
        printf("%02x", (unsigned char)dato[i]); // Imprime en hexadecimal
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
    imprimirHex(encriptado, textLen);

    return 0;
}
