cmake_minimum_required(VERSION 3.10)
project(Ejer17)

# Buscar OpenSSL
find_package(OpenSSL REQUIRED)

# Añadir flags para suprimir advertencias de funciones obsoletas
add_compile_options(-Wno-deprecated-declarations)

add_executable(ejer17 ejer17.c)

# Vincular OpenSSL con el ejecutable
target_link_libraries(ejer17 OpenSSL::SSL OpenSSL::Crypto)

