all:
	gcc -o bonzim bonzim.c -lcurl

clean:
	rm -f bonzim