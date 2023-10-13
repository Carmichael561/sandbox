#include <stdio.h>
#include <stdint.h>


#define BP8 "%c%c%c%c%c%c%c%c"

#define TO_BP8(i)    \
    (((i) & 0x80ll) ? '1' : '0'), \
    (((i) & 0x40ll) ? '1' : '0'), \
    (((i) & 0x20ll) ? '1' : '0'), \
    (((i) & 0x10ll) ? '1' : '0'), \
    (((i) & 0x08ll) ? '1' : '0'), \
    (((i) & 0x04ll) ? '1' : '0'), \
    (((i) & 0x02ll) ? '1' : '0'), \
    (((i) & 0x01ll) ? '1' : '0')

#define BP16 BP8 BP8
#define BP32 BP16 BP16
#define BP64 BP32 BP32

#define TO_BP16(i) TO_BP8((i) >> 8), TO_BP8(i)
#define TO_BP32(i) TO_BP16((i) >> 16), TO_BP16(i)
#define TO_BP64(i) TO_BP32((i) >> 32), TO_BP32(i)

uint64_t __crc_8(uint64_t data)
{
    uint64_t crc = data;
    uint64_t polinomial = (0b100000111ull << (63 - 8));
    int shift = 0;
    do {
        while (((1ull << 63) & crc) == 0 && (shift++ <= 63)) {
            printf("shift: " BP64 "\n", TO_BP64(crc));
            crc <<= 1;
        }
        printf("shift = %d\n", shift);
        printf("" BP64 "\n", TO_BP64(crc));
        printf("" BP64 "\n", TO_BP64(polinomial));
        if (shift > 63) break;
        crc ^= polinomial;
        printf("" BP64 "\n", TO_BP64(crc));
    } while (1);
    return (crc >> 56);
}



int main() {
    uint64_t data = 0xFFFFFFFFFFFFFFFF; // Example data
    uint64_t result = __crc_8(data);
    printf("CRC-8 for data 0x%llx is: 0x%x   %d\n", data, result, result);
}
