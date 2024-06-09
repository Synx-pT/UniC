import math
import random
from collections import defaultdict


# Implementierung der Hashfunktion
def hash_function(x, m):
    return (x % m) + math.floor((m / (x + 1)))

# Funktion zur Berechnung und Darstellung der Hashwerte
def demonstrate_hash_function(keys, m):
    hash_table = defaultdict(list)  # Verwenden eines defaultdicts,
    # um Kollisionen zu erfassen

    for key in keys:
        hash_value = hash_function(key, m)
        hash_table[hash_value].append(key)
        print(f"Key: {key} -> Hash: {hash_value}")

    # Anzeige der Hashwert-Verteilung
    print("\nVerteilung der Hashwerte:")
    for hash_value, keys in hash_table.items():
        print(f"Hashwert {hash_value}: {keys}")


# Beispiel: Demonstration der Hashfunktion mit einer Liste von Schlüsseln
keys = [i for i in range(0, 10)]
m = 15
demonstrate_hash_function(keys, m)
