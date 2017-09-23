add_executable(12 main.cpp)

set(SFML_STATIC_LIBRARIES TRUE)

find_package(Freetype)
find_package(JPEG)
find_package(SFML 2 COMPONENTS window graphics system)

target_compile_features(12 PUBLIC cxx_std_17)
target_compile_definitions(12 PRIVATE SFML_STATIC)

target_link_libraries(12 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})