add_subdirectory(Materials)
set(libs "Materials")

file(GLOB_RECURSE sources CONFIGURE_DEPENDS "*.cc")
add_executable(rt ${sources})
target_link_libraries(rt ${libs})
target_link_libraries(rt Eigen3::Eigen OpenMP::OpenMP_CXX)