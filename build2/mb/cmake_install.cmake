# Install script for directory: /home/crodriguez/Desktop/monkeybrushplusplus/mb

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "lib")
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libmb.so.1.9.2"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libmb.so.1"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libmb.so"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHECK
           FILE "${file}"
           RPATH "")
    endif()
  endforeach()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY MESSAGE_LAZY FILES
    "/home/crodriguez/Desktop/monkeybrushplusplus/build2/lib/libmb.so.1.9.2"
    "/home/crodriguez/Desktop/monkeybrushplusplus/build2/lib/libmb.so.1"
    "/home/crodriguez/Desktop/monkeybrushplusplus/build2/lib/libmb.so"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libmb.so.1.9.2"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libmb.so.1"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libmb.so"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/usr/bin/strip" "${file}")
      endif()
    endif()
  endforeach()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/build2/include/mb/api.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/build2/include/mb/mb.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/build2/include/mb/version.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/CameraComponent.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/Helpers.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/Includes.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/SimpleCamera.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/cameras" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/cameras/Camera.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/cameras" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/cameras/OrthographicCamera.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/cameras" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/cameras/PerspectiveCamera.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/constants" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/constants/Constants.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/core" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/core/BufferAttribute.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/core" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/core/BufferAttribute.inl")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/core" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/core/Color3.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/core" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/core/Color4.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/core" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/core/Framebuffer.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/core" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/core/Framebuffer2.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/core" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/core/GLContext.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/core" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/core/GeometryFunctions.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/core" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/core/GlobalState.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/core" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/core/Layer.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/core" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/core/Log.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/core" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/core/PostProcess.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/core" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/core/Program.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/core" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/core/Query.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/core" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/core/TransformFeedback.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/core" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/core/VertexArray.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/core" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/core/VertexBuffer.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/core" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/core/VertexUBO.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/core" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/core/os.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/extras" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/extras/CustomPingPong.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/extras" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/extras/CustomPingPong.inl")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/extras" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/extras/Easing.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/extras" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/extras/EventDispatcher.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/extras" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/extras/ParticleSystem.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/extras" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/extras/Ray.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/io" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/io/GLFWWindow2.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/io" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/io/Input.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/io" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/io/Keyboard.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/io" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/io/Mouse.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/io" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/io/Window.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/lights" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/lights/AmbientLight.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/lights" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/lights/DirectionalLight.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/lights" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/lights/HemisphericLight.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/lights" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/lights/Light.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/lights" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/lights/PointLight.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/lights" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/lights/SpotLight.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/materials" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/materials/Material.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/materials" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/materials/NormalMaterial.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/materials" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/materials/PostProcessMaterial.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/materials" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/materials/ShaderMaterial.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/materials" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/materials/SimpleShadingMaterial.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/materials" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/materials/Uniform.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/maths" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/maths/Box2D.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/maths" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/maths/Box3D.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/maths" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/maths/Clock.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/maths" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/maths/Curves.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/maths" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/maths/EulerAngle.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/maths" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/maths/Interpolation.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/maths" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/maths/Mat2.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/maths" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/maths/Mat3.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/maths" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/maths/Mat4.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/maths" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/maths/Mathf.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/maths" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/maths/Quat.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/maths" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/maths/Sphere2D.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/maths" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/maths/Sphere3D.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/maths" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/maths/Spherical.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/maths" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/maths/Spline.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/maths" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/maths/Vect2.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/maths" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/maths/Vect3.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/maths" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/maths/Vect4.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/models" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/models/Capsule.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/models" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/models/Cone.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/models" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/models/Cube.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/models" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/models/Cylinder.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/models" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/models/Disc.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/models" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/models/Drawable.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/models" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/models/IDrawable.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/models" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/models/Icosahedron.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/models" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/models/Lathe.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/models" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/models/Mesh.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/models" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/models/Octahedron.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/models" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/models/ParametricGeom.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/models" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/models/Plane.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/models" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/models/Polyhedron.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/models" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/models/Prism.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/models" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/models/Tetrahedron.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/models" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/models/Torus.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/others" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/others/Exception.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/resources" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/resources/MaterialCache.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/resources" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/resources/ObjParser.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/resources" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/resources/ResourceDrawable.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/resources" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/resources/ResourceManager.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/resources" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/resources/ResourceShader.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/resources" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/resources/TextureCache.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/scene" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/scene/Component.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/scene" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/scene/Engine.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/scene" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/scene/Fog.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/scene" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/scene/Group.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/scene" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/scene/MeshRenderer.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/scene" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/scene/MeshRendererTesselation.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/scene" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/scene/Node.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/scene" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/scene/Node.inl")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/scene" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/scene/NodeData.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/scene" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/scene/RenderTarget.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/scene" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/scene/Scene.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/scene" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/scene/Transform.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/textures" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/textures/RenderBuffer.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/textures" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/textures/RenderBufferMultisampleTexture.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/textures" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/textures/RenderBufferTexture.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/textures" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/textures/Texture.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/textures" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/textures/Texture1D.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/textures" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/textures/Texture2D.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/textures" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/textures/Texture2DArray.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/textures" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/textures/Texture3D.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/utils" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/utils/ArgumentParser.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/utils" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/utils/NonCopyable.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/utils" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/utils/RTTI.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/utils" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/utils/any.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/utils" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/utils/iniReader.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/utils" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/utils/macros.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/utils" TYPE FILE MESSAGE_LAZY FILES "/home/crodriguez/Desktop/monkeybrushplusplus/mb/utils/utils.hpp")
endif()

