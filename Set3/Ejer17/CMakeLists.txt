cmake_minimum_required(VERSION 3.10)
project(Ejer17)

add_compile_options(-Wno-deprecated-declarations) # opcional, para ocultar warnings de funciones obsoletas

add_executable(ejer17 ejer17.c)

# librerias necesarias equivalente a: gcc -o ejer17 ejer17.c -lssl -lcrypto -Wno-deprecated-declarations
find_package(OpenSSL REQUIRED)
target_link_libraries(ejer17 OpenSSL::SSL OpenSSL::Crypto)

# Test con GTest
find_package(GTest REQUIRED)
add_executable(test test.cpp)
target_link_libraries(test GTest::GTest pthread OpenSSL::SSL OpenSSL::Crypto)


