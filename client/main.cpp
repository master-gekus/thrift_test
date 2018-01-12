#include "SharedService.h"

#include <cstdio>

#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TBufferTransports.h>

using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

using namespace ::thrifts;

int main(int argc, char* argv[])
{
    int port = 9090;
    stdcxx::shared_ptr<TTransport> socket(new TSocket("localhost", port));
    stdcxx::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
    stdcxx::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
    SharedServiceClient client(protocol);

    try {
        transport->open();

        bool res = client.putPair(1, "Test!");
        printf("1. res = %s\n", res ? "true" : "false");

        res = client.putPair(2, "Test 2");
        printf("2. res = %s\n", res ? "true" : "false");

        SharedStruct s;
        client.getStruct(s, 1);
        printf("3. s.value = \"%s\"\n", s.value.c_str());

        res = client.putPair(2, "Test New");
        printf("4. res = %s\n", res ? "true" : "false");

        client.getStruct(s, 2);
        printf("5. s.value = \"%s\"\n", s.value.c_str());

        client.replacePair(2, "Test New");
        printf("6. replacePair\n");

        client.getStruct(s, 2);
        printf("7. s.value = \"%s\"\n", s.value.c_str());

        printf("All testst finished!\n");
    } catch (TException& tx) {
        printf("ERROR: %s\n", tx.what());
        return 1;
    }
    return 0;
}
