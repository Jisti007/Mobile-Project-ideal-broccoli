cmake_minimum_required(VERSION 3.4.1)
# set targetPlatform, will be passed in from gradle when this sample is completed
# openGL Supportability
# platform         status
#   (0 12)           ES2/ES3 not supported
#   [12, 18)         ES2 only, for ES3, app do dynamic load
#   [18, 24)         ES2 & ES3
#   [24, infinite)   ES2 & ES3 & Vulkan

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall") # -fno-rtti -fno-exceptions

if (${ANDROID_PLATFORM_LEVEL} LESS 12)
    message(FATAL_ERROR "OpenGL 2 is not supported before API level 11 (currently using ${ANDROID_PLATFORM_LEVEL}).")
    return()
elseif (${ANDROID_PLATFORM_LEVEL} LESS 18)
    add_definitions("-DDYNAMIC_ES3")
    set(OPENGL_LIB GLESv2)
else ()
    set(OPENGL_LIB GLESv3)
endif (${ANDROID_PLATFORM_LEVEL} LESS 11)

add_library(
	gles3jni SHARED
	gl3stub_wrapper.c
	gles3jni.cpp
	game/AssetManager.cpp
	game/Biome.cpp
	game/Buff.cpp
	game/Building.cpp
	game/BuildingType.cpp
	game/Camera.cpp
	game/Campaign.cpp
	game/DamageType.cpp
	game/Faction.cpp
	game/FileHelper.cpp
	game/Font.cpp
	game/Game.cpp
	game/GameMap.cpp
	game/HexType.cpp
	game/MapHex.cpp
	game/MapObject.cpp
	game/MapRegion.cpp
	game/Mesh.cpp
	game/Pipeline.cpp
	game/Point.cpp
	game/Random.cpp
	game/Rectangle.cpp
	game/Resource.cpp
	game/Scenario.cpp
	game/Skill.cpp
	game/Sprite.cpp
	game/Texture.cpp
	game/Transform2D.cpp
	game/Unit.cpp
	game/UnitType.cpp
	game/WeightedList.cpp

	game/events/Attack.cpp
	game/events/ScenarioEvent.cpp
	game/events/Movement.cpp

	game/pathing/Agent.cpp
	game/pathing/BinaryHeap.cpp
	game/pathing/Comparable.cpp
	game/pathing/Link.cpp
	game/pathing/MovementLink.cpp
	game/pathing/Node.cpp
	game/pathing/Path.cpp

	game/scenes/Actor.cpp
	game/scenes/ActorVisibilityAnimation.cpp
	game/scenes/Animation.cpp
	game/scenes/DeathAnimation.cpp
	game/scenes/MovementAnimation.cpp
	game/scenes/RecoloredActor.cpp
	game/scenes/Scene.cpp

	game/states/AnimationGameState.cpp
	game/states/BuildingInfoGameState.cpp
	game/states/BuildingSelectedGameState.cpp
	game/states/ComputerGameState.cpp
	game/states/GameState.cpp
	game/states/IdleGameState.cpp
	game/states/MainMenuGameState.cpp
	game/states/MapGameState.cpp
	game/states/PlayerAnimationGameState.cpp
	game/states/PlayerGameState.cpp
	game/states/PathSelectedGameState.cpp
	game/states/TargetSelectedGameState.cpp
	game/states/UnitInfoGameState.cpp
	game/states/UnitSelectedGameState.cpp

	game/ui/Button.cpp
	game/ui/InfoPanel.cpp
	game/ui/Label.cpp
	game/ui/RecoloredUISprite.cpp
	game/ui/ResourcePanel.cpp
	game/ui/UIObject.cpp
	game/ui/UISprite.cpp
	game/ui/UITexture.cpp
)

# Include libraries needed for gles3jni lib
target_link_libraries(
	gles3jni
	${OPENGL_LIB}
	android
	EGL
	log
	m
)
