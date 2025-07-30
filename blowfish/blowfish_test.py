from Crypto.Cipher import Blowfish
from Crypto.Util.Padding import pad, unpad

key = b'secretkey'  # chave de 4 a 56 bytes
cipher = Blowfish.new(key, Blowfish.MODE_ECB)

plaintext = b'hello123'  # precisa ser múltiplo de 8 bytes
ciphertext = cipher.encrypt(pad(plaintext, 8))
decrypted = unpad(cipher.decrypt(ciphertext), 8)

print('Cipher:', ciphertext.hex())
print('Decrypted:', decrypted.decode('utf-8'))