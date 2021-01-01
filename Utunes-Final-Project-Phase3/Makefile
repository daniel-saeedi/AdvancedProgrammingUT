CC_EXEC=g++ 
CC=${CC_EXEC} -std=c++11 -Wall -pedantic 

BUILD_DIR=build
SRC_DIR=src
EXCEPTION_DIR=${SRC_DIR}/Exception
WEB_DIR=${SRC_DIR}/web

all: utunes.out

utunes.out: ${BUILD_DIR}/main.o ${BUILD_DIR}/CommandHandler.o ${BUILD_DIR}/Utunes.o ${BUILD_DIR}/RecommendationSystem.o ${BUILD_DIR}/AuthenticationSystem.o ${BUILD_DIR}/Session.o ${BUILD_DIR}/User.o ${BUILD_DIR}/XOREncryption.o ${BUILD_DIR}/Song.o ${BUILD_DIR}/Criteria.o ${BUILD_DIR}/PublishYearCriteria.o ${BUILD_DIR}/ArtistCriteria.o ${BUILD_DIR}/LikesCriteria.o ${BUILD_DIR}/AndCriteria.o ${BUILD_DIR}/LikeSystem.o ${BUILD_DIR}/CommentSystem.o ${BUILD_DIR}/PlaylistSystem.o ${BUILD_DIR}/Playlist.o ${BUILD_DIR}/Like.o ${BUILD_DIR}/Comment.o ${BUILD_DIR}/BadRequestException.o ${BUILD_DIR}/PermissionDeniedException.o ${BUILD_DIR}/NotFoundException.o ${BUILD_DIR}/EmptyException.o $(BUILD_DIR)/template_parser.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o ${BUILD_DIR}/RouteHandler.o ${BUILD_DIR}/UtunesServer.o
	${CC}	${BUILD_DIR}/main.o ${BUILD_DIR}/CommandHandler.o ${BUILD_DIR}/Utunes.o ${BUILD_DIR}/RecommendationSystem.o ${BUILD_DIR}/AuthenticationSystem.o ${BUILD_DIR}/Session.o ${BUILD_DIR}/User.o ${BUILD_DIR}/XOREncryption.o ${BUILD_DIR}/Song.o ${BUILD_DIR}/Criteria.o ${BUILD_DIR}/PublishYearCriteria.o ${BUILD_DIR}/ArtistCriteria.o ${BUILD_DIR}/LikesCriteria.o ${BUILD_DIR}/AndCriteria.o ${BUILD_DIR}/LikeSystem.o ${BUILD_DIR}/CommentSystem.o ${BUILD_DIR}/PlaylistSystem.o ${BUILD_DIR}/Playlist.o ${BUILD_DIR}/Like.o ${BUILD_DIR}/Comment.o ${BUILD_DIR}/BadRequestException.o ${BUILD_DIR}/PermissionDeniedException.o ${BUILD_DIR}/NotFoundException.o ${BUILD_DIR}/EmptyException.o $(BUILD_DIR)/template_parser.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o ${BUILD_DIR}/RouteHandler.o ${BUILD_DIR}/UtunesServer.o -o utunes.out

${BUILD_DIR}/main.o: main.cpp ${SRC_DIR}/CommandHandler.hpp ${SRC_DIR}/Utunes.hpp ${WEB_DIR}/RouteHandler.hpp
	${CC} -c main.cpp -o ${BUILD_DIR}/main.o

${BUILD_DIR}/CommandHandler.o: ${SRC_DIR}/CommandHandler.cpp ${SRC_DIR}/Utunes.hpp ${SRC_DIR}/Song.hpp
	${CC} -c ${SRC_DIR}/CommandHandler.cpp -o ${BUILD_DIR}/CommandHandler.o

${BUILD_DIR}/Utunes.o: ${SRC_DIR}/Utunes.cpp ${SRC_DIR}/AuthenticationSystem.hpp ${SRC_DIR}/RecommendationSystem.hpp ${SRC_DIR}/XOREncryption.hpp ${SRC_DIR}/Song.hpp ${SRC_DIR}/User.hpp ${SRC_DIR}/PlaylistSystem.hpp ${SRC_DIR}/Session.hpp ${SRC_DIR}/SortFunctions.hpp ${EXCEPTION_DIR}/BadRequestException.hpp ${EXCEPTION_DIR}/NotFoundException.hpp ${EXCEPTION_DIR}/PermissionDeniedException.hpp ${EXCEPTION_DIR}/EmptyException.hpp
	${CC} -c ${SRC_DIR}/Utunes.cpp -o ${BUILD_DIR}/Utunes.o

${BUILD_DIR}/RecommendationSystem.o: ${SRC_DIR}/RecommendationSystem.cpp ${SRC_DIR}/User.hpp ${SRC_DIR}/Song.hpp
	${CC} -c ${SRC_DIR}/RecommendationSystem.cpp -o ${BUILD_DIR}/RecommendationSystem.o

${BUILD_DIR}/AuthenticationSystem.o: ${SRC_DIR}/AuthenticationSystem.cpp ${SRC_DIR}/Session.hpp ${SRC_DIR}/User.hpp ${EXCEPTION_DIR}/BadRequestException.hpp ${EXCEPTION_DIR}/PermissionDeniedException.hpp
	${CC} -c ${SRC_DIR}/AuthenticationSystem.cpp -o ${BUILD_DIR}/AuthenticationSystem.o

${BUILD_DIR}/Session.o: ${SRC_DIR}/Session.cpp ${SRC_DIR}/User.hpp ${SRC_DIR}/Song.hpp ${SRC_DIR}/Criteria.hpp ${SRC_DIR}/ArtistCriteria.hpp ${SRC_DIR}/PublishYearCriteria.hpp ${SRC_DIR}/LikesCriteria.hpp ${SRC_DIR}/AndCriteria.hpp
	${CC} -c ${SRC_DIR}/Session.cpp -o ${BUILD_DIR}/Session.o

${BUILD_DIR}/User.o: ${SRC_DIR}/User.cpp
	${CC} -c ${SRC_DIR}/User.cpp -o ${BUILD_DIR}/User.o

${BUILD_DIR}/XOREncryption.o: ${SRC_DIR}/XOREncryption.cpp
	${CC} -c ${SRC_DIR}/XOREncryption.cpp -o ${BUILD_DIR}/XOREncryption.o

${BUILD_DIR}/Song.o: ${SRC_DIR}/Song.cpp ${SRC_DIR}/LikeSystem.hpp ${SRC_DIR}/CommentSystem.hpp ${SRC_DIR}/User.hpp
	${CC} -c ${SRC_DIR}/Song.cpp -o ${BUILD_DIR}/Song.o

${BUILD_DIR}/LikeSystem.o: ${SRC_DIR}/LikeSystem.cpp ${SRC_DIR}/Like.hpp ${SRC_DIR}/User.hpp ${EXCEPTION_DIR}/BadRequestException.hpp
	${CC} -c ${SRC_DIR}/LikeSystem.cpp -o ${BUILD_DIR}/LikeSystem.o

${BUILD_DIR}/Like.o: ${SRC_DIR}/Like.cpp ${SRC_DIR}/User.hpp
	${CC} -c ${SRC_DIR}/Like.cpp -o ${BUILD_DIR}/Like.o

${BUILD_DIR}/CommentSystem.o: ${SRC_DIR}/CommentSystem.cpp ${SRC_DIR}/User.hpp ${SRC_DIR}/Comment.hpp
	${CC} -c ${SRC_DIR}/CommentSystem.cpp -o ${BUILD_DIR}/CommentSystem.o

${BUILD_DIR}/Comment.o: ${SRC_DIR}/Comment.cpp ${SRC_DIR}/User.hpp
	${CC} -c ${SRC_DIR}/Comment.cpp -o ${BUILD_DIR}/Comment.o

${BUILD_DIR}/PlaylistSystem.o: ${SRC_DIR}/PlaylistSystem.cpp ${SRC_DIR}/Song.hpp ${SRC_DIR}/User.hpp ${SRC_DIR}/Playlist.hpp ${EXCEPTION_DIR}/EmptyException.hpp
	${CC} -c ${SRC_DIR}/PlaylistSystem.cpp -o  ${BUILD_DIR}/PlaylistSystem.o

${BUILD_DIR}/Playlist.o: ${SRC_DIR}/Playlist.cpp ${SRC_DIR}/Song.hpp ${SRC_DIR}/User.hpp ${EXCEPTION_DIR}/PermissionDeniedException.hpp ${EXCEPTION_DIR}/BadRequestException.hpp ${EXCEPTION_DIR}/PermissionDeniedException.hpp
	${CC} -c ${SRC_DIR}/Playlist.cpp -o ${BUILD_DIR}/Playlist.o

${BUILD_DIR}/Criteria.o: ${SRC_DIR}/Criteria.cpp ${SRC_DIR}/Song.hpp 
	${CC} -c ${SRC_DIR}/Criteria.cpp -o ${BUILD_DIR}/Criteria.o

${BUILD_DIR}/ArtistCriteria.o: ${SRC_DIR}/ArtistCriteria.cpp ${SRC_DIR}/Song.hpp ${SRC_DIR}/Criteria.hpp
	${CC} -c ${SRC_DIR}/ArtistCriteria.cpp -o ${BUILD_DIR}/ArtistCriteria.o

${BUILD_DIR}/PublishYearCriteria.o: ${SRC_DIR}/PublishYearCriteria.cpp ${SRC_DIR}/Song.hpp ${SRC_DIR}/Criteria.hpp
	${CC} -c ${SRC_DIR}/PublishYearCriteria.cpp -o ${BUILD_DIR}/PublishYearCriteria.o

${BUILD_DIR}/LikesCriteria.o: ${SRC_DIR}/LikesCriteria.cpp ${SRC_DIR}/Song.hpp ${SRC_DIR}/Criteria.hpp
	${CC} -c ${SRC_DIR}/LikesCriteria.cpp -o ${BUILD_DIR}/LikesCriteria.o

${BUILD_DIR}/AndCriteria.o: ${SRC_DIR}/AndCriteria.cpp ${SRC_DIR}/Song.hpp ${SRC_DIR}/Criteria.hpp
	${CC} -c ${SRC_DIR}/AndCriteria.cpp -o ${BUILD_DIR}/AndCriteria.o

${BUILD_DIR}/SortFunctions.o: ${SRC_DIR}/SortFunctions.cpp ${SRC_DIR}/Song.hpp ${SRC_DIR}/User.hpp
	${CC} -c ${SRC_DIR}/SortFunctions.cpp -o ${BUILD_DIR}/SortFunctions.o

${BUILD_DIR}/BadRequestException.o: ${EXCEPTION_DIR}/BadRequestException.cpp
	${CC} -c ${EXCEPTION_DIR}/BadRequestException.cpp -o ${BUILD_DIR}/BadRequestException.o

${BUILD_DIR}/PermissionDeniedException.o: ${EXCEPTION_DIR}/PermissionDeniedException.cpp
	${CC} -c ${EXCEPTION_DIR}/PermissionDeniedException.cpp -o  ${BUILD_DIR}/PermissionDeniedException.o

${BUILD_DIR}/NotFoundException.o: ${EXCEPTION_DIR}/NotFoundException.cpp
	${CC} -c ${EXCEPTION_DIR}/NotFoundException.cpp -o ${BUILD_DIR}/NotFoundException.o

${BUILD_DIR}/EmptyException.o: ${EXCEPTION_DIR}/EmptyException.cpp
	${CC} -c ${EXCEPTION_DIR}/EmptyException.cpp -o ${BUILD_DIR}/EmptyException.o

#Web

$(BUILD_DIR)/template_parser.o: ${WEB_DIR}/APHTTP/utils/template_parser.cpp ${WEB_DIR}/APHTTP/utils/template_parser.hpp ${WEB_DIR}/APHTTP/utils/request.cpp ${WEB_DIR}/APHTTP/utils/request.hpp ${WEB_DIR}/APHTTP/utils/utilities.hpp ${WEB_DIR}/APHTTP/utils/utilities.cpp
	$(CC) $(CF) -c ${WEB_DIR}/APHTTP/utils/template_parser.cpp -o $(BUILD_DIR)/template_parser.o

$(BUILD_DIR)/response.o: ${WEB_DIR}/APHTTP/utils/response.cpp ${WEB_DIR}/APHTTP/utils/response.hpp ${WEB_DIR}/APHTTP/utils/include.hpp
	$(CC) $(CF) -c ${WEB_DIR}/APHTTP/utils/response.cpp -o $(BUILD_DIR)/response.o

$(BUILD_DIR)/request.o: ${WEB_DIR}/APHTTP/utils/request.cpp ${WEB_DIR}/APHTTP/utils/request.hpp ${WEB_DIR}/APHTTP/utils/include.hpp ${WEB_DIR}/APHTTP/utils/utilities.hpp
	$(CC) $(CF) -c ${WEB_DIR}/APHTTP/utils/request.cpp -o $(BUILD_DIR)/request.o

$(BUILD_DIR)/utilities.o: ${WEB_DIR}/APHTTP/utils/utilities.cpp ${WEB_DIR}/APHTTP/utils/utilities.hpp
	$(CC) $(CF) -c ${WEB_DIR}/APHTTP/utils/utilities.cpp -o $(BUILD_DIR)/utilities.o

$(BUILD_DIR)/server.o: ${WEB_DIR}/APHTTP/server/server.cpp ${WEB_DIR}/APHTTP/server/server.hpp ${WEB_DIR}/APHTTP/server/route.hpp ${WEB_DIR}/APHTTP/utils/utilities.hpp ${WEB_DIR}/APHTTP/utils/response.hpp ${WEB_DIR}/APHTTP/utils/request.hpp ${WEB_DIR}/APHTTP/utils/include.hpp ${WEB_DIR}/APHTTP/utils/template_parser.hpp ${WEB_DIR}/APHTTP/utils/template_parser.cpp
	$(CC) $(CF) -c ${WEB_DIR}/APHTTP/server/server.cpp -o $(BUILD_DIR)/server.o

$(BUILD_DIR)/route.o: ${WEB_DIR}/APHTTP/server/route.cpp ${WEB_DIR}/APHTTP/server/route.hpp ${WEB_DIR}/APHTTP/utils/utilities.hpp ${WEB_DIR}/APHTTP/utils/response.hpp ${WEB_DIR}/APHTTP/utils/request.hpp ${WEB_DIR}/APHTTP/utils/include.hpp
	$(CC) $(CF) -c ${WEB_DIR}/APHTTP/server/route.cpp -o $(BUILD_DIR)/route.o

${BUILD_DIR}/RouteHandler.o: ${WEB_DIR}/RouteHandler.cpp ${WEB_DIR}/UtunesServer.hpp
	${CC} -c ${WEB_DIR}/RouteHandler.cpp -o ${BUILD_DIR}/RouteHandler.o

${BUILD_DIR}/UtunesServer.o: ${WEB_DIR}/UtunesServer.cpp ${WEB_DIR}/APHTTP/server/server.hpp
	${CC} -c ${WEB_DIR}/UtunesServer.cpp -o ${BUILD_DIR}/UtunesServer.o

clean:
	rm -rf ${BUILD_DIR} && mkdir -p ${BUILD_DIR}
	rm utunes.out