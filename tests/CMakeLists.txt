# Здесь будут ваши тесты. Перед пулл реквестом желательно написать тест и добавить сюда следующите три строчки:
# add_executable(test_<шифр> <шифр>.cpp)
# target_link_libraries(test_<шифр> PRIVATE ciphers)
# add_test(NAME <название теста> COMMAND test_<шифр>)


add_executable(test_skel test_skel.cpp)
target_link_libraries(test_skel PRIVATE ciphers)
add_test(NAME Skel_encrypt_decrypt COMMAND test_skel)
target_include_directories(test_skel PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_executable(test_otp test_otp.cpp)
target_link_libraries(test_otp PRIVATE ciphers)
add_test(NAME OTP_basic_encrypt_decrypt COMMAND test_otp)
target_include_directories(test_otp PUBLIC ${PROJECT_SOURCE_DIR}/include)
