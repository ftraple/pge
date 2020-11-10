set(THIS ${PROJECT_NAME}-controller)

add_executable(${THIS} controller-example.c)

target_include_directories(${THIS} PRIVATE ${PROJECT_SOURCE_DIR}/pge/include/public)

target_link_libraries(${THIS} PRIVATE pge)
