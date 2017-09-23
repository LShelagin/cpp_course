add_executable(11 main.cpp)

set(SFML_STATIC_LIBRARIES TRUE)

find_package(Freetype)
find_package(JPEG)
find_package(SFML 2 COMPONENTS window graphics system)

target_compile_features(11 PUBLIC cxx_std_17)
target_compile_definitions(11 PRIVATE SFML_STATIC)

target_link_libraries(11 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})