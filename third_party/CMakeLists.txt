add_subdirectory(Clara)

# Catch2
# importing this way means the provided cmake scripts are available but doesn't get the whole cmake setup
add_library(catch2 INTERFACE)
target_include_directories(catch2 INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/Catch2/single_include/)
add_library(Catch2::Catch2 ALIAS catch2)

#Make the Catch provided modules available to the rest of the project
# provides CTest integration
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/Catch2/contrib/" PARENT_SCOPE)
