# Importar la función para base64 fuentes en fuentes.txt
from base64 import b64encode

# Hexadecimal a convertir
string_hexadecimal = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d"

# Convierte de hex a bytes (convirtiendo de hexadecimal a bytes) y luego los bytes a base64 (codificando en base64)
b64_bytes = b64encode(bytes.fromhex(string_hexadecimal))

# Convertir de bytes a una cadena de texto legible (decodificando de Base64 a una cadena)
b64_string = b64_bytes.decode()

# Imprimir el resultado
print(b64_string)



