all:
	gcc -O3 -o bonzim bonzim.c -lcurl

clean:
	rm -f bonzim