#include <cstdio>

#include <thrift/protocol/TBase64Utils.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include "thrifts_types.h"

int main(int argc, char* argv[])
{
    thrifts::SharedStruct s1;
    s1.__set_key(1);
    s1.__set_value("test");
    thrifts::SharedStruct s2(s1);

    char buf1[10] = "\0\0\0\0\0";
    char buf2[10] = "_________";
    apache::thrift::protocol::base64_encode((uint8_t*)buf1, 3, (uint8_t*)buf2);

    printf("base64_encode result: %s\n", buf2);
    printf("s2.value: \"%s\"\n", s2.value.c_str());
    return 0;
}
