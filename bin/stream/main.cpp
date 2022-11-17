#include <fstream>
#include <iostream>
#include <memory>
#include <regex>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

/**-----------------------------------------------------------------------------
 * [Logh3 description]
 *----------------------------------------------------------------------------*/

namespace Utils {
void Logh3(const std::string& msg) {
  std::cout << "---> " << msg << std::endl;
  //
}

void Logh4(const std::string& msg) {
  std::cout << "---> " << msg << std::endl;
  //
}

}  // namespace Utils

/**-----------------------------------------------------------------------------
 * Config
 *----------------------------------------------------------------------------*/

struct TConfig {
  TConfig(const std::string app_name, int eth_idx)
      : app_name(app_name), eth_idx(eth_idx) {}
  std::string app_name;
  int eth_idx;
  void debug() {
    std::cout << "[name,idx](" << app_name << ", " << eth_idx << ")"
              << std::endl;
  }
};

void LoadConfig(const std::string path) {
  Utils::Logh3("LoadConfig()");
  std::ifstream ifs(path);
  std::string line;
  std::vector<TConfig> configs;

  while (std::getline(ifs, line)) {
    std::regex pattern{"\\[(.*?)\\]\\((\\d*?)\\)"};
    std::smatch matches;
    auto found = std::regex_match(line, matches, pattern);
    if (found) {
      TConfig config{matches[1].str(), stoi(matches[2])};
      configs.push_back(config);
    }
  }

  for (auto& config : configs) {
    config.debug();
  }
}

/**-----------------------------------------------------------------------------
 * Utils
 *----------------------------------------------------------------------------*/

/**-----------------------------------------------------------------------------
 * Filter
 *----------------------------------------------------------------------------*/

class BaseProxy {
 public:
  virtual void Start() = 0;
  virtual void Stop() = 0;
  virtual void Inbound() = 0;
  virtual void Outbound() = 0;

 private:
  std::string filter;
  std::thread tid;
};

/**-----------------------------------------------------------------------------
 * TCP
 *----------------------------------------------------------------------------*/

class TcpProxy : public BaseProxy {
 public:
  TcpProxy() = default;
  void Start();
  void Stop();
  void Inbound();
  void Outbound();
};

void TcpProxy::Start() {}

void TcpProxy::Stop() {}

void TcpProxy::Inbound() {}

void TcpProxy::Outbound() {}

/**-----------------------------------------------------------------------------
 * TCP
 *----------------------------------------------------------------------------*/

class UdpProxy : public BaseProxy {
 public:
  void Start();
  void Stop();
  void Inbound();
  void Outbound();
};

class IcmpProxy : public BaseProxy {
 public:
  void Start();
  void Stop();
  void Inbound();
  void Outbound();
};

/**-----------------------------------------------------------------------------
 * Divert
 *----------------------------------------------------------------------------*/

class Divert {
 public:
  Divert(const std::string& path);

 private:
  std::vector<TConfig> configs;
  std::vector<std::shared_ptr<BaseProxy>> proxies;
};

Divert::Divert(const std::string& path) {
  Utils::Logh3("Divert::Divert");
  LoadConfig(path);
  //
}

/**-----------------------------------------------------------------------------
 * main
 *----------------------------------------------------------------------------*/

int main() {
  Divert("/home/pxhoang/pxhoang/dev/test/cmake/bin/stream/config.cfg");

  return 0;
}
