include(FetchContent)

FetchContent_Declare(
  sfml
  GIT_REPOSITORY "https://github.com/SFML/SFML"
  GIT_TAG 5383d2b3948f805af55c9f8a4587ac72ec5981d1# 2.6.2
)
set(BUILD_SHARED_LIBS false)
add_subdirectory(sfml)
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)

add_subdirectory(json)