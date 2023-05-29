memdump.so: memdump.c
	$(CC) -O2 -o memdump.so -shared -fPIC memdump.c -nostartfiles  -Wl,-soname,memdump.so

clean:
	rm -rf memdump.so