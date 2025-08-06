from Crypto.Cipher import Blowfish
from math import ceil

key = b'kkkkeeeeyyyy....'  # 16 bytes igual ao AES
iv = b'\x12\x34\x56\x78\x9A\xBC\xDE\xF0'  # 8 bytes

with open('text.txt', 'rb') as f:
    plaintext = f.read()

# Padding para múltiplo de 8 bytes
padded_len = ceil(len(plaintext) / 8) * 8
plaintext_padded = plaintext.ljust(padded_len, b'\0')

cipher = Blowfish.new(key, Blowfish.MODE_CBC, iv)
ciphertext = cipher.encrypt(plaintext_padded)

decipher = Blowfish.new(key, Blowfish.MODE_CBC, iv)
decrypted = decipher.decrypt(ciphertext)

print('Texto original (hex):')
for i in range(0, padded_len, 8):
    print(' '.join(f'{b:02X}' for b in plaintext_padded[i:i+8]))
print('\nCriptografado (hex):')
for i in range(0, padded_len, 8):
    print(' '.join(f'{b:02X}' for b in ciphertext[i:i+8]))
print('\nDescriptografado:')
print(decrypted[:len(plaintext)].decode(errors='replace'))