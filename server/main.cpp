#include "SharedService.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using namespace  ::thrifts;

class SharedServiceHandler : virtual public SharedServiceIf {
public:
    SharedServiceHandler() {
    }

    bool putPair(const int64_t key, const std::string& value) override {
        bool result = map_.emplace(key, value).second;
        printf("putPair(%" PRIu64 ", \"%s\") --> %s;\n", key, value.c_str(), result ? "true" : "false");
        return result;
    }

    void replacePair(const int64_t key, const std::string& value) override {
        printf("replacePair(%" PRIu64 ", \"%s\");\n", key, value.c_str());
        map_[key] = value;
        printf("replacePair\n");
    }

    void getStruct(SharedStruct& _return, const int64_t key) override {
        auto it = map_.find(key);
        if (map_.end() == it) {
            printf("getStruct(%" PRIu64 ") --> (not found);\n", key);
        } else {
            _return.__set_key(it->first);
            _return.__set_value(it->second);
            printf("getStruct(%" PRIu64 ") --> {%" PRIu64 ", \"%s\"};\n", key, key, it->second.c_str());
        }
    }

    std::map<int64_t, std::string> map_;
};

int main(int argc, char **argv) {
  int port = 9090;
  std::shared_ptr<SharedServiceHandler> handler(new SharedServiceHandler());
  std::shared_ptr<TProcessor> processor(new SharedServiceProcessor(handler));
  std::shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  std::shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  std::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  server.serve();
  return 0;
}

