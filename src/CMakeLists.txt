set( Name MonkeyBrushPlusPlus )
set( NAME MONKEYBRUSHPLUSPLUS )
set( namespace MonkeyBrushPlusPlus )
set( NAMESPACE MONKEYBRUSHPLUSPLUS )
set( INCLUDE_NAME MonkeyBrushPlusPlus )

set( MONKEYBRUSHPLUSPLUS_SOURCES
    core/GLContext.cpp
    core/Input.cpp
    core/Program.cpp

    scene/Component.cpp
    scene/MeshRenderer.cpp
    scene/Node.cpp
    scene/Transform.cpp
    scene/Engine.cpp
    scene/Scene.cpp

    textures/Texture.cpp
    textures/Texture2D.cpp
    textures/Texture2DArray.cpp
    textures/Texture3D.cpp

    main.cpp
)

set( MONKEYBRUSHPLUSPLUS_HEADERS
    constants/Constants.hpp

    core/Input.hpp
    core/Log.hpp
    core/Color3.hpp
    core/Color4.hpp
    core/GLContext.hpp
    core/Program.hpp
    core/VertexArray.hpp
    core/VertexBuffer.hpp
    core/GlobalState.hpp

    materials/Material.hpp
    models/Drawable.hpp

    maths/Vect2.hpp
    maths/Vect3.hpp
    maths/Vect4.hpp

    maths/Quat.hpp
    maths/EulerAngle.hpp

    maths/Mat2.hpp
    maths/Mat3.hpp
    maths/Mat4.hpp

    lights/Light.hpp
    lights/AmbientLight.hpp
    lights/DirectionalLight.hpp
    lights/HemisphericLight.hpp
    lights/PointLight.hpp
    lights/SpotLight.hpp
    
    scene/Component.hpp
    scene/MeshRenderer.hpp
    scene/Node.hpp
    scene/Transform.hpp
    scene/Engine.hpp
    scene/Scene.hpp

    textures/Texture.hpp
    textures/Texture2D.hpp
    textures/Texture2DArray.hpp
    textures/Texture3D.hpp
)

include_directories( 
    ${CMAKE_CURRENT_BINARY_DIR}
)

#add_subdirectory(core)
#add_subdirectory(scene)
#add_subdirectory(textures)

set( MONKEYBRUSHPLUSPLUS_LINK_LIBRARIES
    ${GLEW_LIBRARIES}
    glfw
)

common_application( MonkeyBrushPlusPlus )
