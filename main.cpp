#include <stdio.h>
#include <string.h>
#include <iostream>
#include <mrss.h>

//build command
//g++ -I/usr/include main.cpp -o"hello_libmrss.exe" -lmrss -lnxml -lcurl -L/usr/lib

int main() {
    mrss_t *data;
    mrss_error_t ret;
    mrss_item_t *item;
    CURLcode code;

    const char *url = "https://boingboing.net/feed";

    std::cout << "Hello libmrss, attempting to download and parse " << url <<std::endl;

    ret = mrss_parse_url_with_options_and_error ((char*)url, &data, NULL, &code);

    if (ret != MRSS_OK) {
        if (ret == MRSS_ERR_DOWNLOAD) {
            std::cout << "error:" << mrss_curl_strerror (code) << std::endl;
        } else {
            std::cout << "error:" << mrss_strerror (ret) << std::endl;
        }
        return 1;
    }

    for (item = data->item; item; item = item->next) {
        std::cout << "item title: " << item->title << std::endl;
        std::cout << "item description: " << item->description << std::endl;
    }

    return 0;
}
