Para compilar y ejecutar este programa, se requiere tener instaladas las siguientes bibliotecas:

OpenSSL (incluyendo las bibliotecas libssl y libcrypto).

Para compilar el archivo ejer17.c y generar el ejecutable ejer17, utiliza el siguiente comando:

gcc -o ejer17 ejer17.c -lssl -lcrypto -Wno-deprecated-declarations