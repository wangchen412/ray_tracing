add_subdirectory(core)
add_subdirectory(Hittables)
add_subdirectory(Materials)
set(libs "Hittables;Materials;core")

add_executable(rt main.cc)
target_link_libraries(rt ${libs})
target_link_libraries(rt Eigen3::Eigen OpenMP::OpenMP_CXX)