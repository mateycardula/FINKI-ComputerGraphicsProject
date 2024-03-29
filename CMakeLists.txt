cmake_minimum_required(VERSION 3.10)
project(ProceduralGenerationFINKI)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(Include/glew/include)
include_directories(Include/glfw/include)
include_directories(Include/glm)

link_directories(Include/glew/lib/Release/x64)  # Adjust for your GLEW directory and architecture
link_directories(Include/glfw/lib-mingw-w64)  # Adjust for your GLFW directory

file(GLOB IMGUI_SOURCES Include/imgui/*.cpp)
include_directories(Include/imgui)

add_executable(${PROJECT_NAME} WIN32 main.cpp
        Include/imgui/imgui.cpp
        Include/imgui/imgui_draw.cpp
        Include/imgui/imgui_widgets.cpp
        Include/imgui/imgui_impl_glfw.cpp
        Include/imgui/imgui_impl_opengl3.cpp ${IMGUI_SOURCES}
        init.h
        init.cpp
        init.h
        Shapes/shapes.cpp
        Shapes/shapes.h
        Shaders/Shader.cpp
        Shaders/Shader.h
        Meshes/Mesh.cpp
        Meshes/Mesh.h
        Meshes/Types/ShapeType.h
        Camera/Camera.cpp
        Camera/Camera.h
        Input/InputManager.cpp
        Input/InputManager.h
        Meshes/Wall/Wall.cpp
        Meshes/Wall/Wall.h
        refactor.h
        Meshes/Factory/Produce/MeshBuilder.cpp
        Meshes/Factory/Produce/MeshBuilder.h
        Camera/UI/ImGuiManager.cpp
        Camera/UI/ImGuiManager.h
        Camera/UI/UI.cpp
        Camera/UI/UI.h
        Meshes/Floor/Floor.cpp
        Meshes/Floor/Floor.h
        DungeonGenerator/DungeonGenerator.cpp
        DungeonGenerator/DungeonGenerator.h
        Meshes/Texture.cpp
        Meshes/Texture.h
        Meshes/GeometryManager.cpp
        Meshes/GeometryManager.h
        Meshes/Doorway/Doorway.cpp
        Meshes/Doorway/Doorway.h
)

target_link_libraries(${PROJECT_NAME} glew32s glfw3 opengl32 glew32)

add_compile_definitions(GLEW_STATIC)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++ -static")


