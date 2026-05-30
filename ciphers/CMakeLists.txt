add_library(ciphers
        dummy.cpp
        skel.cpp
)

target_include_directories(ciphers PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)
