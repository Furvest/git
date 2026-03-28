cmake_minimum_required (VERSION 3.20) # минимальная версия с офф. доков SDL3

project ("SDLGame")

file(GLOB_RECURSE GAME_SRC "src/*.cpp" "src/*.hpp")

if (UNIX)
  # взято с офф. доков SDL3, без него не билдится
  # я на эти 2 строчки убил целый день..........
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
endif()

add_subdirectory(deps/SDL EXCLUDE_FROM_ALL)
add_subdirectory(deps/tinyxml2)

add_executable (SDLGame ${GAME_SRC})

target_link_libraries(SDLGame PRIVATE SDL3::SDL3 tinyxml2::tinyxml2)
if (WIN32)
  if (POLICY CMP0141)
    # Включение горячей перезагрузки для компиляторов MSVC, если поддерживается.
    cmake_policy(SET CMP0141 NEW)
    set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
  endif()
  add_custom_command(TARGET SDLGame POST_BUILD COMMAND "${CMAKE_COMMAND}" -E copy $<TARGET_FILE:SDL3::SDL3-shared> $<TARGET_FILE_DIR:SDLGame> VERBATIM)
 
  # судя по всему оно не работает при открытии cmakelists напрямую в visual studio
  set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT SDLGame)
endif()

# т.к. версия cmake поднялась (3.8 -> 3.20) то можно поднять стандарты CXX
set_property(TARGET SDLGame PROPERTY CXX_STANDARD 20)
