import sys
from src.translator.translator import Translator

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Nie podano nazwy pliku wejściowego!")
        exit(-1)

    Translator.translate(sys.argv[1])
    print("\nSUKCES: udalo wygenerowac sie plik!")
