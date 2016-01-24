cmake_minimum_required(VERSION 3.3)
project(src)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    camera.cc
    camera.h
    constants.h
    coreEngine.cc
    coreEngine.h
    freeLook.cc
    freeLook.h
    freeMove.cc
    freeMove.h
    game.cc
    game.h
    gameComponent.cc
    gameComponent.h
    gameObject.cc
    gameObject.h
    input.cc
    input.h
    lighting.cc
    lighting.h
    main.cc
    material.cc
    material.h
    mesh.cc
    mesh.h
    meshRenderer.cc
    meshRenderer.h
    obj_loader.cc
    obj_loader.h
    phongShader.cc
    phongShader.h
    renderingEngine.cc
    renderingEngine.h
    shader.cc
    shader.h
    stb_image.c
    stb_image.h
    texture.cc
    texture.h
    transform.cc
    transform.h
    util.h
    window.cc
    window.h)

add_executable(src ${SOURCE_FILES})