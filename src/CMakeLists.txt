file (GLOB GAME_SRCS ${PROJECT_SOURCE_DIR}/src/*.cpp)

add_executable (Jarvis ${GAME_SRCS})

target_link_libraries (Jarvis ${ALL_LIBS}  )

install (
	TARGETS Jarvis
	DESTINATION ${INSTALL_DIR}
)
