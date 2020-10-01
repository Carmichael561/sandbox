#HELLO WORLD JUST FOR LINKING GAME:
#1.		If you want to just override a few functions in a library, but keep
#		the rest of the library, you can enter the names of overriding
#2.		libraries (.o files) in /etc/ld.so.preload;
#		Build libsctp.so with debug info
#		sudo touch /etc/ld.so.preload
#		echo ${HOME}projects/lk_network/lksctp-tools/src/lib/.libs/libsctp.so > /etc/ld.so.preload
#		[17600][cos.sin: sctp]$ ldd server_1_to_1
#       linux-vdso.so.1 =>  (0x00007fffa7dc8000)
#       /home/cos/projects/lk_network/lksctp-tools/src/lib/.libs/libsctp.so (0x00007fa0f828f000)
#       libpthread.so.0 => /lib/x86_64-linux-gnu/libpthread.so.0 (0x00007fa0f804a000)
#       libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007fa0f7c85000)
#       /lib64/ld-linux-x86-64.so.2 (0x00007fa0f8495000)

#2.		LD_LIBRARY_PATH is a colon-separated set of directories where libraries should be searched for first


#3.		LD_PRELOAD lists shared libraries with functions that override the standard set
#		export LD_PRELOAD=${HOME}/projects/lk_network/lksctp-tools/src/lib/.libs/libsctp.so
#		export LD_PRELOAD=""

#4.		ldopen and use needed symbols for debug

#5.		for simple program just for test use:
#		ln -s ${HOME}/projects/glibc-build/libc.a  libc.a
#		gcc -g -static-libgcc -L. -lc main.c

TARGET = main
LIBTEST = libtest.so
OBJ = $(TARGET).o
SRC = $(TARGET).c
CC = gcc
CFLAGS = -g
LDFLAGS = -nostdlib -nostartfiles -static
GLIBCDIR = /home/cos/projects/glibc-build
GLIBCDIR_CRTN = /home/cos/projects/glibc-build/nptl
# libc-start.c result = main (argc, argv, __environ MAIN_AUXVEC_PARAM);
GLIBCDIR_CSU = /home/cos/projects/glibc-build/csu
STARTFILES = $(GLIBCDIR_CSU)/crt1.o $(GLIBCDIR_CSU)/crti.o `gcc --print-file-name=crtbegin.o`
ENDFILES = `gcc --print-file-name=crtend.o` $(GLIBCDIR_CRTN)/crtn.o
LIBGROUP = -Wl,--start-group $(GLIBCDIR)/libc.a -lgcc -lgcc_eh -Wl,--end-group

TARGET_HELLO = hello

TARGET_EMBD=embedding_txt_to_object.o

ALL: $(LIBTEST) $(OBJ) $(TARGET) test main_static main_ld $(TARGET_HELLO) $(TARGET_EMBD)

###############################################################################
# test advanced static linking and get additional info
###############################################################################
$(TARGET): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $(STARTFILES) $^ $(LIBGROUP) $(ENDFILES)
	wc -c $(TARGET)
	objdump -t $(TARGET)

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c $^ -L. -ltest

$(LIBTEST): libtest.c
	$(CC) -shared -fPIC libtest.c -o $@
###############################################################################


#sources -> preprocessing -> compilation -> assembly -> object
test:
	gcc main.c -E -o main.i    #Stop after the preprocessing stage; do not run the compiler proper.
	gcc main.c -S -o main.s    #Stop after the stage of compilation proper; do not assemble.
	gcc main.c -c -v -o main.o # -### will show verbose output
	gcc main.i -c -o main_prp_to_obj.o
	gcc main.s -c --help=optimizers -o main_asm_to_obj.o
	gcc main.c -c -O3 --help=optimizers > ./O3-opts

###############################################################################
#ln -s on libc and gcc with -static-libgcc
###############################################################################
main_static:
#	ln -s ${HOME}/projects/glibc-build/libc.a  libc.a
	gcc -g -static-libgcc -L. -lc main.c -o main_static
# test2
# ln -s `gcc -print-file-name=libc.a` #make symbolik link in current directory to libc.a
# or
# ln -s /home/cos/projects/glibc-build/libc.a  libc.a
# gcc -g -static-libgcc -L. -lc main.c
###############################################################################


###############################################################################
#ld
###############################################################################
main_ld:
	ld -o main_ld main.o -lc
###############################################################################


###############################################################################
#investigate internals
###############################################################################
TARGET_HELLO_LNFLAGS = -nostdlib #do not use stdlib.o and crt1.o c_run_time.o
CRT1_LIB = `gcc -print-file-name=crt1.o`
$(TARGET_HELLO):
	$(CC) $(TARGET_HELLO_LNFLAGS) -o $@ $(TARGET_HELLO).c
	wc -c $(TARGET_HELLO)
	objdump -t $(TARGET_HELLO)
	$(CC) -Os -c $(TARGET_HELLO).c
#	ld $(CRT1_LIB) -o hello1 $(TARGET_HELLO).o
	$(CC) -g -nostdlib sstart.S -o hello2 hello.o

###############################################################################


###############################################################################
#Get section name and embedded txt file to executable:
#
#embedding_txt_to_object_txt.o:     file format elf32-i386
# SYMBOL TABLE:
# 00000000 l    d  .data  00000000 .data
# 00000000 g       .data  00000000 _binary_embedding_txt_to_object_txt_start
# 0000002e g       .data  00000000 _binary_embedding_txt_to_object_txt_end
# 0000002e g       *ABS*  00000000 _binary_embedding_txt_to_object_txt_size
#
# sudo apt-get install g++-multilib libc6-dev-i386
# gcc -m32 -m64
###############################################################################
CFLAGS = -g -m32
LDFLAGS = -m32 -L/usr/lib32

$(TARGET_EMBD):
	gcc -c embedding_txt_to_object.c
	objcopy --input binary --output elf32-i386 --binary-architecture i386 embedding_txt_to_object.txt embedding_txt_to_object_txt.o

#	ld -o embedding_txt_to_object embedding_txt_to_object_txt.o embedding_txt_to_object.o -lc
#	hexdump -C embedding_txt_to_object_txt.o


###############################################################################
clean:
	rm -f *.i *.s *.o *.so *~  *.~ $(TARGET) a.out main_static
	rm -f $(TARGET_HELLO) $(TARGET_HELLO).o
	rm -rf O3-opts main_ld hello2 
