file (GLOB GAME_SRCS ${PROJECT_SOURCE_DIR}/src/*.cc ${PROJECT_SOURCE_DIR}/src/*.h*)

add_executable (Jarvis ${GAME_SRCS})

install (
	TARGETS Jarvis
	DESTINATION ${INSTALL_DIR}
)
