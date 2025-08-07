import sys

def cesar(text, shift):
    result = []
    for c in text:
        if c.isalpha():
            base = ord('a') if c.islower() else ord('A')
            result.append(chr((ord(c) - base + shift) % 26 + base))
        elif c.isdigit():
            result.append(chr((ord(c) - ord('0') + (shift % 10 + 10) % 10) % 10 + ord('0')))
        else:
            result.append(c)
    return ''.join(result)

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print(f"Uso: {sys.argv[0]} <arquivo_entrada.txt>")
        sys.exit(1)
    with open(sys.argv[1], "r") as f:
        text = f.read()
    chave = 3

    cript = cesar(text, chave)
    print("Criptografado:")
    print(cript)

    decript = cesar(cript, 26 - (chave % 26))
    print("Decriptografado:")
    print(decript)