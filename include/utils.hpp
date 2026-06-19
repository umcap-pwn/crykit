#include <string>

namespace utils{
    std::string pad(const std::string& data, size_t block_size);
    std::string depad(const std::string& data);
}
