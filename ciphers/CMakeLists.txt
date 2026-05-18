add_library(ciphers_lib
    dummy.cpp
)

target_include_directories(ciphers_lib PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)
