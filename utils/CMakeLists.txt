add_library(utils SHARED
    gfutils.cpp
    utils.cpp
)

target_include_directories(utils PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)
