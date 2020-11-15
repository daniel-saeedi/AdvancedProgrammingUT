CC_EXEC=g++ -std=c++11 
SDL_FLAGS = -l SDL2 -l SDL2_image -l SDL2_ttf -l SDL2_mixer

CC=${CC_EXEC}

BUILD_DIR=build

all: soccerStars.out

soccerStars.out: ${BUILD_DIR}/main.o ${BUILD_DIR}/functions.o  ${BUILD_DIR}/rsdl.o ${BUILD_DIR}/Game.o ${BUILD_DIR}/Team.o ${BUILD_DIR}/Stadium.o ${BUILD_DIR}/Player.o ${BUILD_DIR}/Ball.o ${BUILD_DIR}/Object.o
	${CC} ${BUILD_DIR}/main.o ${BUILD_DIR}/functions.o ${BUILD_DIR}/rsdl.o ${BUILD_DIR}/Game.o ${BUILD_DIR}/Team.o ${BUILD_DIR}/Stadium.o ${BUILD_DIR}/Player.o ${BUILD_DIR}/Ball.o ${BUILD_DIR}/Object.o ${SDL_FLAGS} -o ${BUILD_DIR}/soccerStars.out

${BUILD_DIR}/main.o: main.cpp Game.hpp
	${CC} -c main.cpp ${SDL_FLAGS} -o ${BUILD_DIR}/main.o

${BUILD_DIR}/Game.o: Game.cpp functions.o Stadium.hpp Player.hpp Ball.hpp Team.hpp rsdl.hpp
	${CC} -c Game.cpp ${SDL_FLAGS} -o ${BUILD_DIR}/Game.o

${BUILD_DIR}/Team.o: Team.cpp
	${CC} -c Team.cpp ${SDL_FLAGS} -o ${BUILD_DIR}/Team.o

${BUILD_DIR}/Stadium.o: Stadium.cpp Player.hpp Ball.hpp
	${CC} -c Stadium.cpp ${SDL_FLAGS} -o ${BUILD_DIR}/Stadium.o

${BUILD_DIR}/Object.o: Object.cpp 
	${CC} -c Object.cpp ${SDL_FLAGS} -o ${BUILD_DIR}/Object.o
	
${BUILD_DIR}/Player.o: Player.cpp Object.hpp
	${CC} -c Player.cpp ${SDL_FLAGS} -o ${BUILD_DIR}/Player.o

${BUILD_DIR}/Ball.o: Ball.cpp
	${CC} -c Ball.cpp ${SDL_FLAGS} -o ${BUILD_DIR}/Ball.o

${BUILD_DIR}/rsdl.o: rsdl.cpp
	${CC} -c rsdl.cpp ${SDL_FLAGS} -o ${BUILD_DIR}/rsdl.o

${BUILD_DIR}/functions.o: functions.cpp
	${CC} -c functions.cpp ${SDL_FLAGS} -o ${BUILD_DIR}/functions.o
clean:
	rm -rf ${BUILD_DIR} && mkdir -p ${BUILD_DIR}