import heapq
from collections import Counter
from itertools import count


class HuffmanNode:
    def __init__(self, freq, char=None, left=None, right=None):
        self.freq = freq
        self.char = char
        self.left = left
        self.right = right


def build_huffman_tree(freq_map):
    heap = []
    unique = count()

    for char, freq in freq_map.items():
        heapq.heappush(heap, (freq, next(unique), HuffmanNode(freq, char=char)))

    if len(heap) == 1:
        return heap[0][2]

    while len(heap) > 1:
        freq1, _, left = heapq.heappop(heap)
        freq2, _, right = heapq.heappop(heap)

        parent = HuffmanNode(freq1 + freq2, left=left, right=right)
        heapq.heappush(heap, (parent.freq, next(unique), parent))

    return heap[0][2]


def generate_huffman_codes(root):
    codes = {}

    def dfs(node, code):
        if node is None:
            return

        if node.char is not None:
            codes[node.char] = code if code else "0"
            return

        dfs(node.left, code + "0")
        dfs(node.right, code + "1")

    dfs(root, "")
    return codes


def huffman_encode(text):
    freq_map = Counter(text)
    root = build_huffman_tree(freq_map)
    codes = generate_huffman_codes(root)
    encoded_text = "".join(codes[ch] for ch in text)
    return encoded_text, codes, root


def huffman_decode(encoded_text, root):
    if root.left is None and root.right is None:
        return root.char * len(encoded_text)

    decoded = []
    current = root

    for bit in encoded_text:
        if bit == "0":
            current = current.left
        else:
            current = current.right

        if current.char is not None:
            decoded.append(current.char)
            current = root

    return "".join(decoded)

def huffman_from_freq(freq_map):
    root = build_huffman_tree(freq_map)
    return generate_huffman_codes(root)






text = "aaabbcdddd"

encoded_text, codes, root = huffman_encode(text)

print("Codes:")
for ch, code in codes.items():
    print(f"{ch}: {code}")

print("Encoded:", encoded_text)
print("Decoded:", huffman_decode(encoded_text, root))




freq_map = {
    'a': 5,
    'b': 9,
    'c': 12,
    'd': 13,
    'e': 16,
    'f': 45
}

codes = huffman_from_freq(freq_map)
print(codes)
