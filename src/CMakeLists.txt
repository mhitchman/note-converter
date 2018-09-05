add_library(notelib STATIC
	Note.cpp)

target_compile_options(notelib PRIVATE ${custom_compile_options})
target_include_directories(notelib PUBLIC
$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/>)

add_executable(noteconv main.cpp)
target_link_libraries(noteconv notelib)
set_property(TARGET noteconv PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET noteconv PROPERTY CXX_EXTENSIONS OFF)
target_compile_options(noteconv PRIVATE ${custom_compile_options})
install(TARGETS noteconv DESTINATION bin)
