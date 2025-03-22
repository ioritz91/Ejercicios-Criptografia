# Codigo adaptado de https://stackoverflow.com/questions/70557969/decrypt-aes-ecb-using-python

from Cryptodome.Cipher import AES  # con crypto.cypher no he conseguido que funcione
import base64  # Importar base64

key = b"YELLOW SUBMARINE" #tiene que ser en bytes

# Leer el texto cifrado en Base64 desde un archivo
with open("base64encoded.txt", "r") as file:
    ciphertext_base64 = file.read().strip()

# Decodificar el texto cifrado de Base64 a bytes
ciphertext = base64.b64decode(ciphertext_base64)

# Crear el descifrador y descifrar
cipher = AES.new(key, AES.MODE_ECB)
plaintext = cipher.decrypt(ciphertext)

# Mostrar el texto descifrado
print(plaintext.decode("utf-8"))

