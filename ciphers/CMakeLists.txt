# Добавить сюда имя файла с вашим шифром
add_library(ciphers
        dummy.cpp
        skel.cpp
        otp.cpp
)

target_include_directories(ciphers PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)
