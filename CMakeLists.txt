cmake_minimum_required (VERSION 3.8)

# Включение горячей перезагрузки для компиляторов MSVC, если поддерживается.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("SDLGame")

file(GLOB_RECURSE GAME_SRC CONFIGURE_DEPENDS "src/*.cpp" "src/*.hpp")

add_subdirectory(deps/SDL EXCLUDE_FROM_ALL)
add_subdirectory(deps/SDL_ttf EXCLUDE_FROM_ALL)
add_subdirectory(deps/tinyxml2)

if(ANDROID)
    add_library(main SHARED ${GAME_SRC})
    set(TARGET_NAME main)
else()
    add_executable(SDLGame ${GAME_SRC})
    set(TARGET_NAME SDLGame)
endif()

target_link_libraries(${TARGET_NAME} PRIVATE SDL3::SDL3 tinyxml2::tinyxml2 SDL3_ttf::SDL3_ttf)
if (WIN32)
add_custom_command(TARGET ${TARGET_NAME} POST_BUILD COMMAND "${CMAKE_COMMAND}" -E copy $<TARGET_FILE:SDL3::SDL3-shared> $<TARGET_FILE_DIR:SDLGame> VERBATIM)
add_custom_command(TARGET ${TARGET_NAME} POST_BUILD COMMAND "${CMAKE_COMMAND}" -E copy $<TARGET_FILE:SDL3_ttf::SDL3_ttf-shared> $<TARGET_FILE_DIR:SDLGame> VERBATIM)
add_custom_command(TARGET ${TARGET_NAME} POST_BUILD COMMAND "${CMAKE_COMMAND}" -E copy $<TARGET_FILE:tinyxml2::tinyxml2> $<TARGET_FILE_DIR:SDLGame> VERBATIM)
endif()

add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/assets
            $<TARGET_FILE_DIR:${TARGET_NAME}>/assets
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${TARGET_NAME} PROPERTY CXX_STANDARD 20)
endif()

# судя по всему оно не работает при открытии cmakelists напрямую в visual studio
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT SDLGame)

