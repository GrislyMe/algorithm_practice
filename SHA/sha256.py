#!/usr/bin/env python3

from bitarray import bitarray
import random, time

def rotateRight(string: bitarray, num: int):
    return string[len(string) - num :] + string[: len(string) - num]

def add(*x: bitarray):
    tmp = 0
    for i in x:
        tmp += int(i.to01(), 2)
    return bitarray(f"{tmp:032b}")[-32:]

def sha256(string: str):
    binary = bitarray("".join([f"{i:08b}" for i in list(map(ord, string))]))
    length = bitarray("".join(f"{len(binary):064b}"))
    binary.append(1)
    for i in range(448 - (len(binary) % 448)):
        binary.append(0)
    binary += length

    h = [0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 0x510e527f, 0x9b05688c , 0x1f83d9ab, 0x5be0cd19]
    h = [bitarray(f"{i:032b}") for i in h]

    k = [0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
         0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
         0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
         0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
         0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
         0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
         0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
         0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2]
    k = [bitarray(f"{i:032b}") for i in k]

    w = [binary[i - 32: i] for i in range(32, 513, 32)] + [bitarray("0" * 32)] * 48
    for i in range(16, 64):
        s0 = rotateRight(w[i - 15], 7) ^ rotateRight(w[i - 15], 18) ^ (w[i - 15] >> 3)
        s1 = rotateRight(w[i - 2], 17) ^ rotateRight(w[i - 2], 19)  ^ (w[i - 2] >> 10)
        w[i] = add(w[i - 16], s0, w[i - 7], s1)

    t = h.copy()
    for i in range(0, 64):
        s0 = rotateRight(t[0], 2) ^ rotateRight(t[0], 13) ^ rotateRight(t[0], 22)
        maj = (t[0] & t[1]) ^ (t[0] & t[2]) ^ (t[1] & t[2])
        tmp2 = add(s0, maj)

        s1 = rotateRight(t[4], 6) ^ rotateRight(t[4], 11) ^ rotateRight(t[4], 25)
        ch = (t[4] & t[5]) ^ (~t[4] & t[6])
        tmp1 = add(t[7], s1, ch, k[i], w[i])

        t[7] = t[6]
        t[6] = t[5]
        t[5] = t[4]
        t[4] = add(t[3], tmp1)
        t[3] = t[2]
        t[2] = t[1]
        t[1] = t[0]
        t[0] = add(tmp1, tmp2)

    digit = bitarray()
    for i in range(8):
        digit += add(h[i], t[i])

    tmp = [0] * 66
    ans = str(hex(int(digit.to01(), 2)))
    while 0 in tmp:
        print("\r", end = "", flush = True)
        for n, i in enumerate(tmp):
            if random.randint(1, 3) > 2:
                tmp[n] = 1
            if i: print(ans[n], end = "")
            else: print(" ", end = "")
        time.sleep(0.2)
    print("\r" + hex(int(digit.to01(), 2)), flush = True)

if __name__ == "__main__":
    sha256(input())
