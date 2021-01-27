/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
C#, VB, Perl, Swift, Prolog, Javascript, Pascal, HTML, CSS, JS
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <string.h>
#include <stdint.h>

#define BUFF_SIZE 8
#define ITEM_SIZE 2

typedef struct item_t
{
    uint8_t payload[ITEM_SIZE];
} item;

typedef struct ring_t
{
    int32_t read_cursor;
    int32_t write_cursor;
    uint8_t ring_section[BUFF_SIZE];
} __attribute__((packed, aligned(4))) ring;

ring buff;
static _Bool override = 0;
static _Bool empty = 1;
static _Bool rollover = 0;

void init_ring()
{
    buff.read_cursor = 0;
    buff.write_cursor = 0;
    memset(buff.ring_section, 0x0, BUFF_SIZE);
    override = 0;
    empty = 1;
    rollover = 0;
}

void write_item(item* it)
{
    int size1 = buff.write_cursor + ITEM_SIZE;

    if (size1 >= BUFF_SIZE)
        rollover = 1;
    
    if (size1 > BUFF_SIZE)
    {
        int size2 = size1 - BUFF_SIZE;
        size1 = ITEM_SIZE - size2;
        memcpy(&buff.ring_section[buff.write_cursor], it, size1);
        buff.write_cursor = 0;
        memcpy(&buff.ring_section[buff.write_cursor], (char*)it + size1, size2);
        buff.write_cursor += size2;
        buff.write_cursor %= BUFF_SIZE;
        empty = 0;
        return;
    }

    memcpy(&buff.ring_section[buff.write_cursor], it, ITEM_SIZE);
    buff.write_cursor += ITEM_SIZE;
    buff.write_cursor %= BUFF_SIZE;
    empty = 0;
}

void read_item(item* it)
{
    if (empty)
        return;

    if (buff.write_cursor > buff.read_cursor && rollover)
    {
        buff.read_cursor = buff.write_cursor;
        rollover = 0;
    }
    
    int size1 = buff.read_cursor + ITEM_SIZE;
    if (size1 > BUFF_SIZE)
    {
        int size2 = size1 - BUFF_SIZE;
        size1 = ITEM_SIZE - size2;
        memcpy(it, &buff.ring_section[buff.read_cursor], size1);
        buff.read_cursor = 0;
        memcpy((char*)it + size1, &buff.ring_section[buff.read_cursor], size2);
        buff.read_cursor += size2;
        buff.read_cursor %= BUFF_SIZE;
        return;
    }

    memcpy(it, &buff.ring_section[buff.read_cursor], ITEM_SIZE);
    buff.read_cursor += ITEM_SIZE;
    buff.read_cursor %= BUFF_SIZE;
    
    if (buff.read_cursor == buff.write_cursor)
        empty = 1;
}

int main()
{
    printf("Hello\n");
    for(int i = 0; i < BUFF_SIZE; i++)
        printf("%d \t", buff.ring_section[i]);
    printf("\n");

    item it1;
    int tmp = 1;
    int *p;
    for (int i = 0; i < 7; i++)
    {
        it1.payload[0] = tmp++;
        it1.payload[1] = tmp++;
        write_item(&it1);
    }
    for(int i = 0; i < BUFF_SIZE; i++)
        printf("%d \t", buff.ring_section[i]);
    printf("\nwrite=%d, read=%d\n", buff.write_cursor, buff.read_cursor);

    for (int i = 0; i < 9; i++)
    {
        it1.payload[0] = 0;
        it1.payload[1] = 0;
        read_item(&it1);
        printf("%d %d \n", it1.payload[0], it1.payload[1]);
    }
}
