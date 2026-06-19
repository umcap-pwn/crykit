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

add_executable(test_otp_keygen test_otp_keygen.cpp)
target_link_libraries(test_otp_keygen PRIVATE ciphers)
add_test(NAME OTP_keygen_auto    COMMAND test_otp_keygen auto)
add_test(NAME OTP_keygen_urandom COMMAND test_otp_keygen urandom)
add_test(NAME OTP_keygen_mt19937 COMMAND test_otp_keygen mt19937)
add_test(NAME OTP_keygen_allones COMMAND test_otp_keygen allones)
add_test(NAME OTP_keygen_ssl     COMMAND test_otp_keygen ssl)

add_executable(test_rc4 test_rc4.cpp)
target_link_libraries(test_rc4 PRIVATE ciphers)
add_test(NAME RC4_encrypt_decrypt COMMAND test_rc4)

target_include_directories(test_otp_keygen PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_executable(test_hill test_hill.cpp)
target_link_libraries(test_hill PRIVATE ciphers)
add_test(NAME Hill_encrypt_decrypt COMMAND test_hill)
target_include_directories(test_hill PUBLIC ${PROJECT_SOURCE_DIR}/include)
