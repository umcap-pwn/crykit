#include <string>

namespace utils{
    std::string pad(std::string& data, size_t block_size);
    std::string depad(std::string& data);
}
