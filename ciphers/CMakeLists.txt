# Добавить сюда имя файла с вашим шифром
add_library(ciphers SHARED
        skel.cpp
        otp.cpp
        rc4.cpp
        hill.cpp
)

target_link_libraries(ciphers PRIVATE
    OpenSSL::SSL OpenSSL::Crypto
    utils
)
target_include_directories(ciphers PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)
