CC_EXEC=g++ 
CC=${CC_EXEC} -std=c++11 

BUILD_DIR=build
SRC_DIR=src
EXCEPTION_DIR=${SRC_DIR}/Exception

all: utunes.out

utunes.out: ${BUILD_DIR}/main.o ${BUILD_DIR}/CommandHandler.o ${BUILD_DIR}/Utunes.o ${BUILD_DIR}/AuthenticationSystem.o ${BUILD_DIR}/Session.o ${BUILD_DIR}/User.o ${BUILD_DIR}/Song.o ${BUILD_DIR}/LikeSystem.o ${BUILD_DIR}/CommentSystem.o ${BUILD_DIR}/Playlist.o ${BUILD_DIR}/Like.o ${BUILD_DIR}/Comment.o ${BUILD_DIR}/BadRequestException.o ${BUILD_DIR}/PermissionDeniedException.o ${BUILD_DIR}/NotFoundException.o ${BUILD_DIR}/EmptyException.o
	${CC}	${BUILD_DIR}/main.o ${BUILD_DIR}/CommandHandler.o ${BUILD_DIR}/Utunes.o ${BUILD_DIR}/AuthenticationSystem.o ${BUILD_DIR}/Session.o ${BUILD_DIR}/User.o ${BUILD_DIR}/Song.o ${BUILD_DIR}/LikeSystem.o ${BUILD_DIR}/CommentSystem.o ${BUILD_DIR}/Playlist.o ${BUILD_DIR}/Like.o ${BUILD_DIR}/Comment.o ${BUILD_DIR}/BadRequestException.o ${BUILD_DIR}/PermissionDeniedException.o ${BUILD_DIR}/NotFoundException.o ${BUILD_DIR}/EmptyException.o -o utunes.out

${BUILD_DIR}/main.o: main.cpp ${SRC_DIR}/CommandHandler.hpp
	${CC} -c main.cpp -o ${BUILD_DIR}/main.o

${BUILD_DIR}/CommandHandler.o: ${SRC_DIR}/CommandHandler.cpp ${SRC_DIR}/Utunes.hpp ${SRC_DIR}/Song.hpp
	${CC} -c ${SRC_DIR}/CommandHandler.cpp -o ${BUILD_DIR}/CommandHandler.o

${BUILD_DIR}/Utunes.o: ${SRC_DIR}/Utunes.cpp ${SRC_DIR}/AuthenticationSystem.hpp ${SRC_DIR}/Song.hpp ${SRC_DIR}/User.hpp ${SRC_DIR}/Session.hpp ${EXCEPTION_DIR}/BadRequestException.hpp ${EXCEPTION_DIR}/NotFoundException.hpp ${EXCEPTION_DIR}/BadRequestException.hpp
	${CC} -c ${SRC_DIR}/Utunes.cpp -o ${BUILD_DIR}/Utunes.o

${BUILD_DIR}/AuthenticationSystem.o: ${SRC_DIR}/AuthenticationSystem.cpp ${SRC_DIR}/Session.hpp ${SRC_DIR}/User.hpp ${EXCEPTION_DIR}/BadRequestException.hpp ${EXCEPTION_DIR}/PermissionDeniedException.hpp
	${CC} -c ${SRC_DIR}/AuthenticationSystem.cpp -o ${BUILD_DIR}/AuthenticationSystem.o

${BUILD_DIR}/Session.o: ${SRC_DIR}/Session.cpp ${SRC_DIR}/User.hpp ${SRC_DIR}/Song.hpp
	${CC} -c ${SRC_DIR}/Session.cpp -o ${BUILD_DIR}/Session.o

${BUILD_DIR}/User.o: ${SRC_DIR}/User.cpp ${SRC_DIR}/Playlist.hpp
	${CC} -c ${SRC_DIR}/User.cpp -o ${BUILD_DIR}/User.o

${BUILD_DIR}/Song.o: ${SRC_DIR}/Song.cpp ${SRC_DIR}/LikeSystem.hpp ${SRC_DIR}/User.hpp
	${CC} -c ${SRC_DIR}/Song.cpp -o ${BUILD_DIR}/Song.o

${BUILD_DIR}/LikeSystem.o: ${SRC_DIR}/LikeSystem.cpp ${SRC_DIR}/Like.hpp ${SRC_DIR}/User.hpp ${EXCEPTION_DIR}/BadRequestException.hpp
	${CC} -c ${SRC_DIR}/LikeSystem.cpp -o ${BUILD_DIR}/LikeSystem.o

${BUILD_DIR}/Like.o: ${SRC_DIR}/Like.cpp ${SRC_DIR}/User.hpp
	${CC} -c ${SRC_DIR}/Like.cpp -o ${BUILD_DIR}/Like.o

${BUILD_DIR}/CommentSystem.o: ${SRC_DIR}/CommentSystem.cpp
	${CC} -c ${SRC_DIR}/CommentSystem.cpp -o ${BUILD_DIR}/CommentSystem.o

${BUILD_DIR}/Comment.o: ${SRC_DIR}/Comment.cpp
	${CC} -c ${SRC_DIR}/Comment.cpp -o ${BUILD_DIR}/Comment.o

${BUILD_DIR}/Playlist.o: ${SRC_DIR}/Playlist.cpp ${SRC_DIR}/Song.hpp
	${CC} -c ${SRC_DIR}/Playlist.cpp -o ${BUILD_DIR}/Playlist.o

${BUILD_DIR}/BadRequestException.o: ${EXCEPTION_DIR}/BadRequestException.cpp
	${CC} -c ${EXCEPTION_DIR}/BadRequestException.cpp -o ${BUILD_DIR}/BadRequestException.o

${BUILD_DIR}/PermissionDeniedException.o: ${EXCEPTION_DIR}/PermissionDeniedException.cpp
	${CC} -c ${EXCEPTION_DIR}/PermissionDeniedException.cpp -o  ${BUILD_DIR}/PermissionDeniedException.o

${BUILD_DIR}/NotFoundException.o: ${EXCEPTION_DIR}/NotFoundException.cpp
	${CC} -c ${EXCEPTION_DIR}/NotFoundException.cpp -o ${BUILD_DIR}/NotFoundException.o

${BUILD_DIR}/EmptyException.o: ${EXCEPTION_DIR}/EmptyException.cpp
	${CC} -c ${EXCEPTION_DIR}/EmptyException.cpp -o ${BUILD_DIR}/EmptyException.o

clean:
	rm -rf ${BUILD_DIR} && mkdir -p ${BUILD_DIR}