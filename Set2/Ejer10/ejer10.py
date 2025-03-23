from Cryptodome.Cipher import AES
import base64

# parecido a la funcion utilizada en el ejercicio 5
def xor_bytes(a, b):
    result = []
    for i in range(len(a)): # len a y len b iguales
        result.append(a[i] ^ b[i])
    return bytes(result)

# https://stackoverflow.com/questions/70557969/decrypt-aes-ecb-using-python
# la funcion del ejercicio 7
def aes_ecb_decrypt(ciphertext, key):
    cipher = AES.new(key, AES.MODE_ECB)
    return cipher.decrypt(ciphertext)

def cbc_decrypt(ciphertext, key, iv):
    block_size = 16  # Tamaño del bloque de AES
    plaintext = b''  # Aquí se almacena el texto plano resultante
    
    # Dividimos el ciphertext en bloques de 16 bytes
    blocks = [ciphertext[i:i + block_size] for i in range(0, len(ciphertext), block_size)]
    
    previous_block = iv  # El bloque anterior inicial es el IV (vector de inicialización), como se dice en el enunciado
    for block in blocks: # Iterar sobre cada bloque de texto cifrado
        decrypted_block = aes_ecb_decrypt(block, key)  # Desciframos el bloque usando AES en ECB
        plaintext += xor_bytes(decrypted_block, previous_block)  # XOR con el bloque anterior
        previous_block = block  # El bloque cifrado actual pasa a ser el siguiente IV
    
    return plaintext

# Leer el texto cifrado en Base64 desde un archivo, usado en ejercicio 7
with open("codigo_encriptado.txt", "r") as file:
    encrypted_data = file.read().strip()

# Decodificar desde Base64, usado en ejercicio 7
decoded_data = base64.b64decode(encrypted_data)

# Definir la clave y el IV
key = b"YELLOW SUBMARINE"  # Clave utilizada para el cifrado
iv = b'\x00' * 16  # El IV está compuesto por 16 ceros ASCII (0x00)

# Descifrar los datos
plaintext = cbc_decrypt(decoded_data, key, iv)

# Mostrar el resultado, usado en ejercicio 7
print(plaintext.decode('utf-8'))

