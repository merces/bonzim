#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <stdbool.h>

bool drop_a_file(void) {
    const char buff[] = "MZ\x90\x00\x03\x00\x00\x00\x04\x00\x00\x00\xff\xff\x00\x00";

    FILE *fh = fopen("/tmp/fake.exe", "wb");
    if (!fh || fwrite(buff, 16, 1, fh) != 1)
        return false;

    fclose(fh);
    return true;
}

bool talk_to_c2(const char *url) {
    CURL *curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
    curl_easy_setopt(curl, CURLOPT_URL, url);
    res = curl_easy_perform(curl);

    if (res != CURLE_OK)
        return false;

    curl_easy_cleanup(curl);
    curl_global_cleanup();
    return true;
}

int main(void) {
    printf("[+] Dropping a file...\t%s\n", drop_a_file() ? "OK" : "FAILED");
    printf("[+] HTTP GETting C2...\t%s\n", talk_to_c2("http://menteb.in") ? "OK" : "FAILED");

    return 0;
}
