#include <filesystem>
#include <fstream>
#include <string>

std::string getHostProductName() {
  std::string pn;
  if (std::filesystem::exists("/sys/devices/virtual/dmi/id/product_name") &&
      std::filesystem::is_regular_file("/sys/devices/virtual/dmi/id/product_name")) {
    std::ifstream product_name("/sys/devices/virtual/dmi/id/product_name");
    std::getline(product_name, pn);
    return pn;
  }
  return "not found";
}

std::string host() {
  return getHostProductName();
}
