cmake_minimum_required(VERSION 3.10)
project(test_parser C)

include(CTest)

set(CMAKE_C_STANDARD 11)

# required for fuzzing
set(CMAKE_C_COMPILER /usr/bin/clang)

enable_testing()

include_directories(include/ ../src)

add_library(brt
  ../src/brt/amount.c
  ../src/brt/amount.h
  ../src/brt/array.h
  ../src/brt/fields.c
  ../src/brt/fields.h
  ../src/brt/field_sort.c
  ../src/brt/field_sort.h
  ../src/brt/flags.c
  ../src/brt/flags.h
  ../src/brt/format.c
  ../src/brt/format.h
  ../src/brt/general.c
  ../src/brt/general.h
  ../src/brt/number_helpers.c
  ../src/brt/number_helpers.h
  ../src/brt/percentage.c
  ../src/brt/percentage.h
  ../src/brt/readers.c
  ../src/brt/readers.h
  ../src/brt/strings.c
  ../src/brt/strings.h
  ../src/brt/time.c
  ../src/brt/time.h
  ../src/brt/transaction_types.h
  ../src/brt/brt_helpers.c
  ../src/brt/brt_helpers.h
  ../src/brt/brt_parse.c
  ../src/brt/brt_parse.h
)

add_executable(test_printers
  src/test_printers.c
  src/cx.c
  include/bolos_target.h
  include/cx.h
  include/os.h
)

add_executable(test_swap
  src/test_swap.c
  src/cx.c
  ../src/swap/handle_check_address.h
  ../src/swap/swap_lib_calls.c
  ../src/swap/swap_lib_calls.h
  include/bolos_target.h
  include/cx.h
  include/os.h
  )

add_executable(test_tx
  src/test_tx.c
  src/cx.c
  include/bolos_target.h
  include/cx.h
  include/os.h
)

add_executable(fuzz_tx
  src/fuzz_tx.c
  src/cx.c
  include/bolos_target.h
  include/cx.h
  include/os.h
)

target_compile_options(fuzz_tx PRIVATE -Wall -fsanitize=fuzzer,address -g -ggdb2)
target_link_libraries(fuzz_tx PRIVATE cmocka crypto ssl brt -fsanitize=fuzzer,address)
target_link_libraries(test_printers PRIVATE cmocka crypto ssl brt)
target_link_libraries(test_swap PRIVATE cmocka crypto ssl brt)
target_link_libraries(test_tx PRIVATE cmocka crypto ssl brt)

add_test(test_printers test_printers)
add_test(test_swap test_swap)
add_test(test_tx test_tx)
