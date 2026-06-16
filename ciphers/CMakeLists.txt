add_library(ciphers SHARED
        dummy.cpp
        skel.cpp
        otp.cpp
)

target_link_libraries(ciphers PRIVATE OpenSSL::SSL OpenSSL::Crypto)
target_include_directories(ciphers PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)
