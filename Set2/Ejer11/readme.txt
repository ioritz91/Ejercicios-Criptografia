Para compilar este proyecto, es necesario instalar OpenSSL ejecutando el siguiente comando en la terminal:

sudo apt-get install libssl-dev

Para compilar el código fuente ejer11.c y generar el ejecutable, utiliza el siguiente comando:

gcc -o ejer11 ejer11.c -lssl -lcrypto -Wno-deprecated-declarations

Al crear el ejecutable salta un warning de que las funciones AES utilizadas estan descontinuadas, pero funciona correctamente. Para una versión futura se ha encontrado este ejemplo que utiliza las nuevas funciones que soporta OpenSSL 3.0 (EVP)

https://alinush.github.io/2012/08/25/AES-encrypt.html