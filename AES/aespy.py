from Crypto.Cipher import AES
from Crypto.Random import get_random_bytes
from Crypto.Util.Padding import pad, unpad
import sys

if len(sys.argv) < 2:
    print(f"Uso: {sys.argv[0]} <arquivo_entrada.txt>")
    sys.exit(1)

input_file = sys.argv[1]
with open(input_file, 'rb') as f:
    plain = f.read()

# chave e IV aleatórios
key = get_random_bytes(16)
iv = get_random_bytes(16)

# cbc mode + padding pkcs7
cipher = AES.new(key, AES.MODE_CBC, iv)
ciphertext = cipher.encrypt(pad(plain, AES.block_size))

# formatar hex em pares de bytes
def format_hex(data):
    hexstr = data.hex()
    return ' '.join([hexstr[i:i+2] for i in range(0, len(hexstr), 2)])

print("\nCipher Key (hex):\n" + format_hex(key))
print("\nIV (hex):\n" + format_hex(iv))
print("\nPlaintext (hex):\n" + format_hex(plain))
print("\nCiphertext (hex):\n" + format_hex(ciphertext))

# decrypt
decipher = AES.new(key, AES.MODE_CBC, iv)
recovered = unpad(decipher.decrypt(ciphertext), AES.block_size)

print("\nDecrypted text (hex):\n" + format_hex(recovered))
print("\nDecrypted text (ASCII):\n" + recovered.decode(errors='replace'))
