#include <cstdio>

#include <thrift/protocol/TBase64Utils.h>
#include <thrift/protocol/TBinaryProtocol.h>

int main(int argc, char* argv[])
{
    char buf1[10] = "\0\0\0\0\0";
    char buf2[10] = "_________";
    apache::thrift::protocol::base64_encode((uint8_t*)buf1, 3, (uint8_t*)buf2);

    printf("base64_encode result: %s\n", buf2);
    return 0;
}
