# CMakeList.txt: проект CMake для SDLGame; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

# Включение горячей перезагрузки для компиляторов MSVC, если поддерживается.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("SDLGame")

file(GLOB_RECURSE GAME_SRC "src/*.cpp" "src/*.hpp")

add_subdirectory(deps/SDL EXCLUDE_FROM_ALL)
add_subdirectory(deps/tinyxml2)

# Добавьте источник в исполняемый файл этого проекта.
add_executable (SDLGame ${GAME_SRC})

target_link_libraries(SDLGame PRIVATE SDL3::SDL3 tinyxml2::tinyxml2)
if (WIN32)
add_custom_command(TARGET SDLGame POST_BUILD COMMAND "${CMAKE_COMMAND}" -E copy $<TARGET_FILE:SDL3::SDL3-shared> $<TARGET_FILE_DIR:SDLGame> VERBATIM)
endif()

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET SDLGame PROPERTY CXX_STANDARD 20)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
