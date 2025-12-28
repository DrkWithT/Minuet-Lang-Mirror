add_subdirectory(frontend)
add_subdirectory(semantics)
add_subdirectory(ir)
add_subdirectory(bcgen)
add_subdirectory(driver)
add_subdirectory(runtime)
add_subdirectory(mintrinsics)


add_executable(minuetm main.cpp)
target_include_directories(minuetm PUBLIC ${MINUET_LANG_SRC_DIR})

# For working around a regression within Homebrew LLVM 21.1.7 installs under Clang: (issue 235411)
if (APPLE AND LLVM_LIBRARY_DIR)
    target_link_directories(minuetm PUBLIC "${LLVM_LIBRARY_DIR}/c++" PUBLIC ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endif ()

target_link_libraries(minuetm PRIVATE driver PRIVATE frontend PRIVATE semantics PRIVATE ir PRIVATE bcgen PRIVATE runtime PRIVATE mintrinsics)
