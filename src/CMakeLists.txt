file(GLOB_RECURSE sources CONFIGURE_DEPENDS "*.cc")
add_executable(rt ${sources})
target_link_libraries (rt Eigen3::Eigen)