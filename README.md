# bonzim

bonzim is a work in progress command-line program that simulates malicious behaviour.

It's NOT malicious. It's actually a good guy that creates a fake PE file
and sends a HTTP GET request to a URL so you can test monitoring solutions,
sandbox software, etc. It requires libcurl, so make you sure you have it
before compiling bonzim.

Let's say you want to monitor the library calls in a Linux box. You can do like:

    $ git clone https://github.com/merces/bonzim.git
    $ cd bonzim
    $ make
    $ ltrace ./bonzim
    fopen("/tmp/fake.exe", "wb")                                                                 = 0x55a3672090e0
    fwrite("MZ\220", 16, 1, 0x55a3672090e0)                                                      = 1
    fclose(0x55a3672090e0)                                                                       = 0
    printf("[+] Dropping a file...\t%s\n", "OK"[+] Dropping a file...	OK
    )                                                 = 26
    curl_global_init(3, 0, 0x7f55fc52b760, 0x7fffffe6)                                           = 0
    curl_easy_init(0, 0, 0, 0)                                                                   = 0x55a367223d80
    curl_easy_setopt(0x55a367223d80, 64, 0, 64)                                                  = 0
    curl_easy_setopt(0x55a367223d80, 81, 0, 81)                                                  = 0
    curl_easy_setopt(0x55a367223d80, 0x2712, 0x55a36621ed8b, 0x2712)                             = 0
    curl_easy_perform(0x55a367223d80, 0x55a36621ed8b, 17, 0)                                     = 0
    curl_easy_cleanup(0x55a367223d80, 0x7ffff7958420, 0, 0)                                      = 0
    curl_global_cleanup(13, 0x7ffff7958470, 0, 0x7f55fc1c315e)                                   = 0
    printf("[+] HTTP GETting C2...\t%s\n", "OK"[+] HTTP GETting C2...	OK
    )                                                 = 26

Or you can check specific syscalls using strace command (also in Linux):

    $ strace -e write,connect,sendto,recvfrom ./bonzim
    write(3, "MZ\220\0\3\0\0\0\4\0\0\0\377\377\0\0", 16) = 16
    write(1, "[+] Dropping a file...\tOK\n", 26[+] Dropping a file...	OK
    ) = 26
    connect(3, {sa_family=AF_INET, sin_port=htons(80), sin_addr=inet_addr("107.155.91.162")}, 16) = -1 EINPROGRESS (Operation now in progress)
    sendto(3, "GET / HTTP/1.1\r\nHost: menteb.in\r"..., 48, MSG_NOSIGNAL, NULL, 0) = 48
    recvfrom(3, "HTTP/1.1 302 Found\r\nDate: Fri, 0"..., 16384, 0, NULL, NULL) = 180
    write(1, "[+] HTTP GETting C2...\tOK\n", 26[+] HTTP GETting C2...	OK
    ) = 26

That's it. Be good. Be bonzim. :thumbsup: