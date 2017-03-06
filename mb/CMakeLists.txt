source_group(\\ FILES CMakeLists.txt)

set( MB_PUBLIC_HEADERS
  #cameras/Camera.hpp
  #cameras/PerspectiveCamera.hpp
  #cameras/OrthographicCamera.hpp

  constants/Constants.hpp

  core/BufferAttribute.hpp
  core/BufferAttribute.inl
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
  core/TransformFeedback.hpp
  core/VertexArray.hpp
  core/VertexBuffer.hpp
  core/VertexUBO.hpp
  core/Framebuffer2.hpp

  exceptions/Exception.hpp
  exceptions/FileNotFoundException.hpp
  exceptions/HasParentException.hpp
  exceptions/RuntimeException.hpp

  extras/CustomPingPong.hpp
  extras/CustomPingPong.inl
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
  maths/Clock.hpp
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
  maths/Spherical.hpp
  maths/Frustum.hpp


  models/Capsule.hpp
  models/Cone.hpp
  models/Cube.hpp
  models/Cylinder.hpp
  models/Disc.hpp
  models/Drawable.hpp
  models/Icosahedron.hpp
  models/Lathe.hpp
  models/Mesh.hpp
  models/Octahedron.hpp
  models/Polyhedron.hpp
  models/Prism.hpp
  models/Tetrahedron.hpp
  models/Torus.hpp
  models/Plane.hpp
  models/ParametricGeom.hpp
  models/Sphere.hpp
  models/KleinBottle.hpp
  models/MobiusStrip.hpp

  resources/MaterialCache.hpp
  resources/ObjParser.hpp
  resources/ResourceDrawable.hpp
  resources/ResourceManager.hpp
  resources/ResourceShader.hpp
  resources/TextureCache.hpp

  scene/Component.hpp
  scene/Engine.hpp
  scene/Fog.hpp
  scene/Group.hpp
  scene/MeshRenderer.hpp
  scene/MeshRendererTesselation.hpp
  scene/Node.hpp
  scene/Node.inl
  scene/Scene.hpp
  scene/Transform.hpp
  scene/NodeData.hpp
  scene/Group.hpp
  scene/Switch.hpp
  scene/LODNode.hpp
  scene/CameraComponent.hpp

  textures/RenderBuffer.hpp
  textures/RenderBufferMultisampleTexture.hpp
  textures/RenderBufferTexture.hpp
  textures/Texture.hpp
  textures/Texture1D.hpp
  textures/Texture2D.hpp
  textures/Texture2DArray.hpp
  textures/Texture3D.hpp

  utils/ArgumentParser.hpp
  utils/NonCopyable.hpp
  utils/any.hpp
  utils/macros.hpp
  utils/utils.hpp
  utils/iniReader.hpp
  utils/RTTI.hpp
  utils/StringUtils.hpp
  utils/Singleton.hpp

  Includes.hpp
  Helpers.hpp
  SimpleCamera.hpp


  core/os.hpp
  io/Mouse.hpp
  io/Keyboard.hpp
  io/Input.hpp
  io/Window.hpp
  io/GLFWWindow2.hpp

  #CameraComponent.hpp
  #Transform2.hpp
  models/IDrawable.hpp
  scene/RenderTarget.hpp
)

set( MB_HEADERS
)

set( MB_SOURCES
  #cameras/Camera.cpp
  #cameras/PerspectiveCamera.cpp
  #cameras/OrthographicCamera.cpp

  core/Color3.cpp
  core/Color4.cpp
  core/Framebuffer.cpp
  core/GLContext.cpp
  core/GlobalState.cpp
  #core/Input.cpp
  core/Layer.cpp
  core/Log.cpp
  core/PostProcess.cpp
  core/Program.cpp
  core/Query.cpp
  core/TransformFeedback.cpp
  core/VertexArray.cpp
  core/VertexBuffer.cpp
  core/VertexUBO.cpp
  core/Framebuffer2.cpp

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
  maths/Clock.cpp
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
  maths/Spherical.cpp
  maths/Frustum.cpp

  models/Capsule.cpp
  models/Cone.cpp
  models/Cube.cpp
  models/Cylinder.cpp
  models/Disc.cpp
  models/Drawable.cpp
  models/Icosahedron.cpp
  models/Lathe.cpp
  models/Mesh.cpp
  models/Octahedron.cpp
  models/Polyhedron.cpp
  models/Prism.cpp
  models/Tetrahedron.cpp
  models/Torus.cpp
  models/Plane.cpp
  models/ParametricGeom.cpp
  models/Sphere.cpp

  resources/MaterialCache.cpp
  resources/ObjParser.cpp
  resources/ResourceShader.cpp
  resources/ResourceDrawable.cpp
  resources/TextureCache.cpp

  scene/Component.cpp
  scene/Engine.cpp
  scene/MeshRenderer.cpp
  scene/MeshRendererTesselation.cpp
  scene/Node.cpp
  scene/NodeData.cpp
  scene/Scene.cpp
  scene/Transform.cpp
  scene/Group.cpp
  scene/Switch.cpp
  scene/CameraComponent.cpp

  textures/RenderBuffer.cpp
  textures/RenderBufferMultisampleTexture.cpp
  textures/RenderBufferTexture.cpp
  textures/Texture.cpp
  textures/Texture1D.cpp
  textures/Texture2D.cpp
  textures/Texture2DArray.cpp
  textures/Texture3D.cpp

  Helpers.cpp

  io/Mouse.cpp
  io/Input.cpp
  io/Keyboard.cpp
  io/Window.cpp
  io/GLFWWindow2.cpp


  utils/utils.cpp
  utils/ArgumentParser.cpp
  utils/iniReader.cpp


  #main.cpp
  scene/RenderTarget.cpp
)

set( MB_LINK_LIBRARIES
  ${OPENGL_LIBRARIES}
  ${GLEW_LIBRARIES}
  ${FREEIMAGE_LIBRARIES}
  ${RAPIDJSON_LIBRARIES}
  ${GLFW3_LIBRARIES}
)

common_library( mb )
