CC=arm-linux-gnueabi-gcc
CFLAGS=-I.

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

#rev_main: rev_main.o
#	$(CC) -o $@ $^ $(CFLAGS) -static

clean:
	rm -rf *.o rev_main *.so *~

run:
	qemu-arm ./rev_main
