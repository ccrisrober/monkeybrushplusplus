source_group(\\ FILES CMakeLists.txt)

set( MB_PUBLIC_HEADERS
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
    #core/Input.hpp
    core/Layer.hpp
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
    extras/ParticleSystem.hpp
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
    models/Icosahedron.hpp
    models/Mesh.hpp
    models/Octahedron.hpp
    models/Polyhedron.hpp
    models/Prism.hpp
    models/Tetrahedron.hpp
    models/Torus.hpp

    others/Exception.hpp

    resources/MaterialCache.hpp
    resources/ObjParser.hpp
    resources/ResourceDrawable.hpp
    resources/ResourceManager.hpp
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

    utils/NonCopyable.hpp
    utils/any.hpp
    utils/macros.hpp

    Includes.hpp
    Helpers.hpp
    SimpleCamera.hpp

    MB.hpp



    #core/os.hpp
    io/Mouse.hpp
    io/Keyboard.hpp
    io/Input2.hpp
    io/Window.hpp
)

set( MB_HEADERS )

set( MB_SOURCES
    cameras/Camera.cpp
    cameras/PerspectiveCamera.cpp
    cameras/OrthographicCamera.cpp

    core/BufferAttribute.cpp
    core/Color3.cpp
    core/Color4.cpp
    core/Framebuffer.cpp
    core/GLContext.cpp
    #core/Input.cpp
    core/Layer.cpp
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

    models/Capsule.cpp
    models/Cone.cpp
    models/Cube.cpp
    models/Cylinder.cpp
    models/Disc.cpp
    models/Drawable.cpp
    models/Icosahedron.cpp
    models/Mesh.cpp
    models/Octahedron.cpp
    models/Polyhedron.cpp
    models/Prism.cpp
    models/Tetrahedron.cpp
    models/Torus.cpp

    others/Exception.cpp
    
    resources/MaterialCache.cpp
    resources/ObjParser.cpp
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

    Helpers.cpp

    io/Mouse.cpp
    io/Input2.cpp
    io/Keyboard.cpp
    io/Window.cpp

    #main.cpp
)

set( MB_LINK_LIBRARIES
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARIES}
    ${FREEIMAGE_LIBRARIES}
    glfw
    #FreeImage
)

common_library( MB )
#common_application( MB )