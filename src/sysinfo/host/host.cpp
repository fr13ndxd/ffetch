#include <filesystem>
#include <fstream>
#include <string>

std::string getHostProductName() {
  std::string pn;
  if (std::filesystem::exists("/sys/devices/virtual/dmi/id/product_name") &&
      std::filesystem::is_regular_file(
          "/sys/devices/virtual/dmi/id/product_name")) {
    std::ifstream product_name("/sys/devices/virtual/dmi/id/product_name");
    std::getline(product_name, pn);
    return pn;
  }
  return "not found";
}

std::string getHostProductVersion() {
  std::string pv;
  if (std::filesystem::exists("/sys/devices/virtual/dmi/id/product_version") &&
      std::filesystem::is_regular_file(
          "/sys/devices/virtual/dmi/id/product_version")) {
    std::ifstream product_name("/sys/devices/virtual/dmi/id/product_version");
    std::getline(product_name, pv);
    return pv;
  }
  return "";
}

std::string host() {
  std::string productName = getHostProductName();
  std::string productVersion = getHostProductVersion();

  if (!productVersion.empty()) {
    return productName + " (" + productVersion + ")";
  } else {
    return productName;
  }
}
