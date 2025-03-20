# Importar la función para base64
from base64 import b64encode

# Hexadecimal a convertir
string_hexadecimal = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d"

# Convierte de hex a bytes (encode) y los bytes a base64 (decode)
b64_string = b64encode(bytes.fromhex(string_hexadecimal)).decode()

# Imprimir el resultado
print(b64_string)
