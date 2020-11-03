find_package(GTest REQUIRED)

add_executable(Gmain Gmain.cxx)
target_link_libraries(Gmain ${GTEST_LIBRARIES} pthread)
