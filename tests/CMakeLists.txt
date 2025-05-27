cmake_minimum_required(VERSION 3.22)
project(banking_tests)

# Подключаем GoogleTest через FetchContent
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/release-1.12.1.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Добавляем исполняемый файл для тестов
add_executable(banking_tests
    test_account.cpp
    test_transaction.cpp
)

# Делаем include директории для доступа к banking/
target_include_directories(banking_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../banking
)

# Линкуем с библиотеками и GoogleTest
target_link_libraries(banking_tests
    banking             
    gtest
    gtest_main
    gmock
)

# Опции для покрытия (coverage)
if(CODE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(banking_tests PRIVATE --coverage -O0 -g)
    target_link_options(banking_tests PRIVATE --coverage)
endif()

# Автоматическое обнаружение тестов
include(GoogleTest)
gtest_discover_tests(banking_tests)