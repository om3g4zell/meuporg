cmake_minimum_required(VERSION 3.5)
project(meuporg-royale-server)

set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -m64")

include_directories(source)
include_directories(source/Components)
include_directories(source/Database)
include_directories(source/InformationServer)
include_directories(source/Kantan-2)
include_directories(source/Kantan-2/Component)
include_directories(source/Kantan-2/Entity)
include_directories(source/Kantan-2/Event)
include_directories(source/Kantan-2/GUI)
include_directories(source/Kantan-2/ResourceHolder)
include_directories(source/Kantan-2/System)
include_directories(source/Kantan-2/Utils)
include_directories(source/LoginServer)
include_directories(source/MapLoader)
include_directories(source/RandomNumberGenerator)
include_directories(source/Server)
include_directories(source/Systems)
include_directories(source/Utils)
include_directories(source/World)
include_directories(source/sqlite)

include_directories(C:/mingw-w64/x86_64-7.3.0-win32-seh-rt_v5-rev0/mingw64/include)
include_directories(../SFML/include)
link_directories(C:/mingw-w64/x86_64-7.3.0-win32-seh-rt_v5-rev0/mingw64/lib)
link_directories(../SFML/lib)

add_executable(meuporg-royale-server
              source/main.cpp
              source/Components/BasicStatsComponent.cpp
              source/Components/BonusComponent.cpp
              source/Components/ClientLinkComponent.cpp
              source/Components/DamageComponent.cpp
              source/Components/LevelStatsComponent.cpp
              source/Components/LifetimeComponent.cpp
              source/Components/MonsterAIComponent.cpp
              source/Components/NameComponent.cpp
              source/Components/StaticMarkerComponent.cpp
              source/Components/TowerAIComponent.cpp
              source/Components/WeaponComponent.cpp
              source/Database/Database.cpp
              source/InformationServer/InformationServer.cpp
              source/Kantan-2/Component/AABBHitboxComponent.cpp
              source/Kantan-2/Component/AnimationComponent.cpp
              source/Kantan-2/Component/BatchedSpriteComponent.cpp
              source/Kantan-2/Component/Component.cpp
              source/Kantan-2/Component/DeletionMarkerComponent.cpp
              source/Kantan-2/Component/MovementComponent.cpp
              source/Kantan-2/Component/ParticleEffectComponent.cpp
              source/Kantan-2/Component/PolygonHitboxComponent.cpp
              source/Kantan-2/Component/RectShapeComponent.cpp
              source/Kantan-2/Component/RotationComponent.cpp
              source/Kantan-2/Component/SpriteComponent.cpp
              source/Kantan-2/Entity/Entity.cpp
              source/Kantan-2/Event/Event.cpp
              source/Kantan-2/GUI/GUIButtonPool.cpp
              source/Kantan-2/GUI/GUIGraph.cpp
              source/Kantan-2/GUI/GUITextInputPool.cpp
              source/Kantan-2/System/AABBCollisionSystem.cpp
              source/Kantan-2/System/AnimationSystem.cpp
              source/Kantan-2/System/BatchedSpriteRenderSystem.cpp
              source/Kantan-2/System/ParticleEffectRenderSystem.cpp
              source/Kantan-2/System/ParticleEffectUpdateSystem.cpp
              source/Kantan-2/System/PolygonCollisionSystem.cpp
              source/Kantan-2/System/RectShapeRenderSystem.cpp
              source/Kantan-2/System/RotationSystem.cpp
              source/Kantan-2/System/SpriteRenderSystem.cpp
              source/Kantan-2/System/SynchronizeBatchedSpriteSystem.cpp
              source/Kantan-2/System/SynchronizeRectShapeSystem.cpp
              source/Kantan-2/System/SynchronizeSpriteSystem.cpp
              source/Kantan-2/System/System.cpp
              source/Kantan-2/Utils/MathUtils.cpp
              source/Kantan-2/Utils/StringUtils.cpp
              source/LoginServer/LoginServer.cpp
              source/MapLoader/MapLoader.cpp
              source/RandomNumberGenerator/RandomNumberGenerator.cpp
              source/Server/Server.cpp
              source/Systems/ClientInputSystem.cpp
              source/Systems/LevelUpSystem.cpp
              source/Systems/LifetimeSystem.cpp
              source/Systems/MonsterAISystem.cpp
              source/Systems/TowerAISystem.cpp
              source/Systems/WeaponCooldownSystem.cpp
              source/Utils/SFMLPacketUtils.cpp
              source/World/World.cpp
              source/sqlite/sqlite3.c
              )
target_link_libraries(meuporg-royale-server sfml-system-d sfml-window-d sfml-graphics-d sfml-network-d sfml-audio-d pthread)

if(UNIX)
    target_link_libraries(meuporg-royale-server dl)
endif(UNIX)
