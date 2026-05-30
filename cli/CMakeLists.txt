add_executable ( crykit
    main.cpp
)

target_link_libraries(crykit  PRIVATE 
        ciphers
)

target_include_directories(crykit PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)
