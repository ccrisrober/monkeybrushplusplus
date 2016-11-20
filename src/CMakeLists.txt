set( Name MonkeyBrushPlusPlus )
set( NAME MONKEYBRUSHPLUSPLUS )
set( namespace MonkeyBrushPlusPlus )
set( NAMESPACE MONKEYBRUSHPLUSPLUS )
set( INCLUDE_NAME MonkeyBrushPlusPlus )

set( MONKEYBRUSHPLUSPLUS_SOURCES
    core/BufferAttribute.cpp
    core/Color3.cpp
    core/Color4.cpp
    core/Framebuffer.cpp
    core/GLContext.cpp
    core/Input.cpp
    core/Log.cpp
    core/PostProcess.cpp
    core/Program.cpp
    core/VertexArray.cpp
    core/VertexBuffer.cpp
    core/VertexUBO.cpp

    extras/CustomPingPong.cpp
    extras/Easing.cpp
    extras/Ray.cpp

    lights/AmbientLight.cpp
    lights/DirectionalLight.cpp
    lights/HemisphericLight.cpp
    lights/Light.cpp
    lights/PointLight.cpp
    lights/SpotLight.cpp

    materials/Material.cpp
    materials/NormalMaterial.cpp
    materials/PostProcessMaterial.cpp
    materials/ShaderMaterial.cpp
    materials/SimpleShadingMaterial.cpp
    materials/Uniform.cpp

    maths/Box2D.cpp
    maths/Box3D.cpp
    maths/Curves.cpp
    maths/EulerAngle.cpp
    maths/Interpolation.cpp
    maths/Mat2.cpp
    maths/Mat3.cpp
    maths/Mat4.cpp
    maths/Mathf.cpp
    maths/Quat.cpp
    maths/Sphere2D.cpp
    maths/Sphere3D.cpp
    maths/Spline.cpp
    maths/Vect2.cpp
    maths/Vect3.cpp
    maths/Vect4.cpp

    others/Exception.cpp
    
    resources/ResourceShader.cpp
    resources/ResourceDrawable.cpp

    scene/Component.cpp
    scene/Engine.cpp
    scene/MeshRenderer.cpp
    scene/Node.cpp
    scene/Scene.cpp
    scene/Transform.cpp

    textures/RenderBuffer.cpp
    textures/RenderBufferMultisampleTexture.cpp
    textures/RenderBufferTexture.cpp
    textures/Texture.cpp
    textures/Texture2D.cpp
    textures/Texture2DArray.cpp
    textures/Texture3D.cpp

    main.cpp
)

set( MONKEYBRUSHPLUSPLUS_HEADERS
    Includes.hpp
    Helpers.hpp
    SimpleCamera.hpp

    cameras/Camera.hpp
    cameras/PerspectiveCamera.hpp
    cameras/OrthographicCamera.hpp

    constants/Constants.hpp

    core/BufferAttribute.hpp
    core/Color3.hpp
    core/Color4.hpp
    core/Framebuffer.hpp
    core/GeometryFunctions.hpp
    core/GLContext.hpp
    core/GlobalState.hpp
    core/Input.hpp
    core/Log.hpp
    core/PostProcess.hpp
    core/Program.hpp
    core/Query.hpp
    core/VertexArray.hpp
    core/VertexBuffer.hpp
    core/VertexUBO.hpp

    extras/CustomPingPong.hpp
    extras/Easing.hpp
    extras/EventDispatcher.hpp
    extras/Ray.hpp

    lights/AmbientLight.hpp
    lights/DirectionalLight.hpp
    lights/HemisphericLight.hpp
    lights/Light.hpp
    lights/PointLight.hpp
    lights/SpotLight.hpp

    materials/Material.hpp
    materials/NormalMaterial.hpp
    materials/PostProcessMaterial.hpp
    materials/ShaderMaterial.hpp
    materials/SimpleShadingMaterial.hpp
    materials/Uniform.hpp

    maths/Box2D.hpp
    maths/Box3D.hpp
    maths/Curves.hpp
    maths/EulerAngle.hpp
    maths/Interpolation.hpp
    maths/Mat2.hpp
    maths/Mat3.hpp
    maths/Mat4.hpp
    maths/Mathf.hpp
    maths/Quat.hpp
    maths/Sphere2D.hpp
    maths/Sphere3D.hpp
    maths/Spline.hpp
    maths/Vect2.hpp
    maths/Vect3.hpp
    maths/Vect4.hpp

    models/Capsule.hpp
    models/Cone.hpp
    models/Cube.hpp
    models/Cylinder.hpp
    models/Disc.hpp
    models/Drawable.hpp
    models/Prism.hpp
    models/Torus.hpp

    others/Exception.hpp

    resources/ResourceDrawable.hpp
    resources/ResourceShader.hpp

    scene/Component.hpp
    scene/Engine.hpp
    scene/Group.hpp
    scene/MeshRenderer.hpp
    scene/Node.hpp
    scene/Scene.hpp
    scene/Transform.hpp

    textures/RenderBuffer.hpp
    textures/RenderBufferMultisampleTexture.hpp
    textures/RenderBufferTexture.hpp
    textures/Texture.hpp
    textures/Texture2D.hpp
    textures/Texture2DArray.hpp
    textures/Texture3D.hpp

    utils/any.hpp
)

include_directories( 
    ${CMAKE_CURRENT_BINARY_DIR}
)

#add_subdirectory(core)
#add_subdirectory(scene)
#add_subdirectory(textures)

set( MONKEYBRUSHPLUSPLUS_LINK_LIBRARIES
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARIES}
    glfw
)

common_application( MonkeyBrushPlusPlus )
