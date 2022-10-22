include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/e2239ee6043f73722e7aa812a459f54a28552929.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(Sources
    CardTests.cpp
    DeckTests.cpp
    VerifierTests.cpp
    ComparatorTests.cpp
    TableTests.cpp
    PlayerTests.cpp
    )

enable_testing()

add_executable(${PROJECT_NAME}-ut ${Sources})
target_link_libraries(${PROJECT_NAME}-ut gtest_main ${PROJECT_NAME}-lib)
target_compile_options(${PROJECT_NAME}-ut PUBLIC -Wall -Wextra -Werror -Wpedantic -Wconversion)
