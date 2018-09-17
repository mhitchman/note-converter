add_library(notelib STATIC
	Note.cpp)

target_link_libraries(notelib PRIVATE project_warnings)
target_include_directories(notelib PUBLIC
$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/>)

add_executable(noteconv main.cpp)
target_link_libraries(noteconv PRIVATE project_warnings notelib Clara::Clara)
set_property(TARGET noteconv PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET noteconv PROPERTY CXX_EXTENSIONS OFF)
install(TARGETS noteconv DESTINATION bin)
