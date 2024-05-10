cmake_minimum_required(VERSION 3.6)
project(Amugen)

set(TARGET_NAME Amugen)
set(TARGET_PARAM WIN32)

Set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/EngineFiles)

# list source files here
Set(ENGINE_SOURCE_FILES
  "${SOURCE_DIR}/Base/Scene.cpp"
  "${SOURCE_DIR}/Base/Amugen.cpp"
  "${SOURCE_DIR}/Base/GameObject.cpp"
  "${SOURCE_DIR}/Base/Subject.h"
  "${SOURCE_DIR}/Base/Observer.h"

  "${SOURCE_DIR}/Components/TransformComponent.cpp"
  "${SOURCE_DIR}/Components/TextComponent.cpp"
  "${SOURCE_DIR}/Components/RenderComponent.cpp"

  "${SOURCE_DIR}/Commands/Command.h"
  "${SOURCE_DIR}/Commands/GameObjectCommands.h" 

  "${SOURCE_DIR}/Singletons/Singleton.h"
  "${SOURCE_DIR}/Singletons/GameTime.cpp"
  "${SOURCE_DIR}/Singletons/Renderer.cpp"
  "${SOURCE_DIR}/Singletons/InputManager.cpp"
  "${SOURCE_DIR}/Singletons/ResourceManager.cpp"
  "${SOURCE_DIR}/Singletons/SceneManager.cpp"
  "${SOURCE_DIR}/Singletons/SoundSystem.cpp"
  "${SOURCE_DIR}/Singletons/ServiceLocator.cpp"

  "${SOURCE_DIR}/Wrappers/Texture2D.cpp"
  "${SOURCE_DIR}/Wrappers/Font.cpp"
  "${SOURCE_DIR}/Wrappers/Controller.cpp"
  "${SOURCE_DIR}/Wrappers/Sound.cpp"
  )

add_library(${TARGET_NAME} STATIC
    ${ENGINE_SOURCE_FILES}
 )

target_link_libraries(${TARGET_NAME} PUBLIC XInput)

target_include_directories(${TARGET_NAME} PUBLIC
    ${SOURCE_DIR}/Base
    ${SOURCE_DIR}/Commands
    ${SOURCE_DIR}/Singletons
    ${SOURCE_DIR}/Wrappers
    ${SOURCE_DIR}/Components

    ${CMAKE_CURRENT_SOURCE_DIR}/3rdParty
)

# enable c++20 features
target_compile_features(${TARGET_NAME} PUBLIC cxx_std_20)
# compile at max warning level + treat warnings as errors
target_compile_options(${TARGET_NAME} PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror -Wno-volatile>
)
set_property(TARGET ${TARGET_NAME} PROPERTY
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED TRUE
    CXX_EXTENSIONS FALSE
)

include(FetchContent)
# add glm
FetchContent_Declare(
  glm
  URL https://github.com/g-truc/glm/releases/download/0.9.9.8/glm-0.9.9.8.zip
  DOWNLOAD_NO_PROGRESS ON
  DOWNLOAD_DIR ${CMAKE_BINARY_DIR}/downloads
)
FetchContent_MakeAvailable(glm)
target_link_libraries(${TARGET_NAME} PUBLIC glm::glm)

FetchContent_GetProperties(glm)
if(NOT glm_POPULATED)
  FetchContent_Populate(glm)
endif()

# add sdl libraries
if (WIN32)
  FetchContent_Declare  (
    SDL2
    URL https://www.libsdl.org/release/SDL2-devel-2.28.5-VC.zip 
    DOWNLOAD_NO_PROGRESS ON
    DOWNLOAD_DIR ${CMAKE_BINARY_DIR}/downloads 
  )
  FetchContent_GetProperties(SDL2)
  if(NOT SDL2_POPULATED)
      FetchContent_Populate(SDL2)
      set(SDL2_INCLUDE_DIR ${sdl2_SOURCE_DIR}/include)
    if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
        set(SDL2_LIBRARIES "${sdl2_SOURCE_DIR}/lib/x64/SDL2.lib;${sdl2_SOURCE_DIR}/lib/x64/SDL2main.lib")
        set(SDL2_LIBRARY_DLL "${sdl2_SOURCE_DIR}/lib/x64/SDL2.dll")
    else()
        set(SDL2_LIBRARIES "${sdl2_SOURCE_DIR}/lib/x86/SDL2.lib;${sdl2_SOURCE_DIR}/lib/x86/SDL2main.lib")
        set(SDL2_LIBRARY_DLL "${sdl2_SOURCE_DIR}/lib/x86/SDL2.dll")
    endif()
  endif()

  # add SDL2_image
  FetchContent_Declare(
    SDL2_image
    URL https://www.libsdl.org/projects/SDL_image/release/SDL2_image-devel-2.8.2-VC.zip 
    DOWNLOAD_NO_PROGRESS ON
    DOWNLOAD_DIR ${CMAKE_BINARY_DIR}/downloads
  )
  FetchContent_GetProperties(SDL2_image)
  if(NOT SDL2_image_POPULATED)
        FetchContent_Populate(SDL2_image)
        set(SDL2_IMAGE_INCLUDE_DIR ${sdl2_image_SOURCE_DIR}/include)
    if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
        set(SDL2_IMAGE_LIBRARIES "${sdl2_image_SOURCE_DIR}/lib/x64/SDL2_image.lib")
        set(SDL2_IMAGE_LIBRARY_DLL "${sdl2_image_SOURCE_DIR}/lib/x64/SDL2_image.dll")
    else()
    set(SDL2_IMAGE_LIBRARIES "${sdl2_image_SOURCE_DIR}/lib/x86/SDL2_image.lib")
    set(SDL2_IMAGE_LIBRARY_DLL "${sdl2_image_SOURCE_DIR}/lib/x86/SDL2_image.dll")
    endif()
  endif()

  # add SDL2_ttf
  FetchContent_Declare(
    SDL2_ttf
    URL https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-devel-2.20.2-VC.zip
    DOWNLOAD_NO_PROGRESS ON
    DOWNLOAD_DIR ${CMAKE_BINARY_DIR}/downloads
  )
  FetchContent_GetProperties(SDL2_ttf)
  if(NOT SDL2_TTF_POPULATED)
        FetchContent_Populate(SDL2_ttf)
        set(SDL2_TTF_INCLUDE_DIR ${sdl2_ttf_SOURCE_DIR}/include)
    if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
        set(SDL2_TTF_LIBRARIES ${sdl2_ttf_SOURCE_DIR}/lib/x64/SDL2_ttf.lib)
        set(SDL2_TTF_LIBRARY_DLL "${sdl2_ttf_SOURCE_DIR}/lib/x64/SDL2_ttf.dll")
    else()
        set(SDL2_TTF_LIBRARIES ${sdl2_ttf_SOURCE_DIR}/lib/x86/SDL2_ttf.lib)
        set(SDL2_TTF_LIBRARY_DLL "${sdl2_ttf_SOURCE_DIR}/lib/x86/SDL2_ttf.dll")
    endif()
  endif()

  # add SDL2_mixer
  FetchContent_Declare(
    SDL2_mixer
    URL https://github.com/libsdl-org/SDL_mixer/releases/download/release-2.8.0/SDL2_mixer-devel-2.8.0-VC.zip
    DOWNLOAD_NO_PROGRESS ON
    DOWNLOAD_DIR ${CMAKE_BINARY_DIR}/downloads
  )

  FetchContent_GetProperties(SDL2_mixer)
  if(NOT SDL2_MIXER_POPULATED)
        FetchContent_Populate(SDL2_mixer)
        set(SDL2_MIXER_INCLUDE_DIR ${sdl2_mixer_SOURCE_DIR}/include)
    if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
        set(SDL2_MIXER_LIBRARIES ${sdl2_mixer_SOURCE_DIR}/lib/x64/SDL2_mixer.lib)
        set(SDL2_MIXER_LIBRARY_DLL "${sdl2_mixer_SOURCE_DIR}/lib/x64/SDL2_mixer.dll")
    else()       
        set(SDL2_MIXER_LIBRARIES ${sdl2_mixer_SOURCE_DIR}/lib/x86/SDL2_mixer.lib)
        set(SDL2_MIXER_LIBRARY_DLL "${sdl2_mixer_SOURCE_DIR}/lib/x86/SDL2_mixer.dll")
    endif()
  endif()

  set(VLD_DIR "$ENV{ProgramFiles\(x86\)}/Visual Leak Detector")
  IF(EXISTS ${VLD_DIR})
    set(VLD_INCLUDE_DIR "${VLD_DIR}/include")
    if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
        set(VLD_LIBRARY "${VLD_DIR}/lib/Win64/vld.lib")
    else()
        set(VLD_LIBRARY "${VLD_DIR}/lib/Win32/vld.lib")
    endif()
  endif()

  # set all include directories
  target_include_directories(${TARGET_NAME} PRIVATE
    ${VLD_INCLUDE_DIR}
    ${SDL2_INCLUDE_DIR} 
    ${SDL2_IMAGE_INCLUDE_DIR} 
    ${SDL2_TTF_INCLUDE_DIR}
    ${SDL2_MIXER_INCLUDE_DIR}
  )
      
  # set libraries to link with
  target_link_libraries(${TARGET_NAME} PUBLIC
    ${VLD_LIBRARY}
    ${SDL2_LIBRARIES} 
    ${SDL2_IMAGE_LIBRARIES} 
    ${SDL2_TTF_LIBRARIES} 
    ${SDL2_MIXER_LIBRARIES}
  )
endif()

#copy resources directory
add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E copy_directory "${CMAKE_SOURCE_DIR}/Resources" "${CMAKE_BINARY_DIR}/Resources"
	)

# add post build commands for dlls
add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E copy "${SDL2_LIBRARY_DLL}" ${CMAKE_BINARY_DIR}
)
add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E copy "${SDL2_IMAGE_LIBRARY_DLL}" ${CMAKE_BINARY_DIR}
)
add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E copy "${SDL2_TTF_LIBRARY_DLL}" ${CMAKE_BINARY_DIR}
)
add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E copy "${SDL2_MIXER_LIBRARY_DLL}" ${CMAKE_BINARY_DIR}
)
