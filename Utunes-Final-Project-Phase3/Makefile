CC_EXEC=g++ 
CC=${CC_EXEC} -std=c++11 -Wall -pedantic 

BUILD_DIR=build
SRC_DIR=src
EXCEPTION_DIR=${SRC_DIR}/Exception
WEB_DIR=${SRC_DIR}/web

all: utunes.out

utunes.out: ${BUILD_DIR}/main.o ${BUILD_DIR}/CommandHandler.o ${BUILD_DIR}/Utunes.o ${BUILD_DIR}/RecommendationSystem.o ${BUILD_DIR}/AuthenticationSystem.o ${BUILD_DIR}/Session.o ${BUILD_DIR}/User.o ${BUILD_DIR}/XOREncryption.o ${BUILD_DIR}/Song.o ${BUILD_DIR}/Criteria.o ${BUILD_DIR}/PublishYearCriteria.o ${BUILD_DIR}/ArtistCriteria.o ${BUILD_DIR}/LikesCriteria.o ${BUILD_DIR}/AndCriteria.o ${BUILD_DIR}/LikeSystem.o ${BUILD_DIR}/CommentSystem.o ${BUILD_DIR}/PlaylistSystem.o ${BUILD_DIR}/Playlist.o ${BUILD_DIR}/Like.o ${BUILD_DIR}/Comment.o ${BUILD_DIR}/BadRequestException.o ${BUILD_DIR}/PermissionDeniedException.o ${BUILD_DIR}/NotFoundException.o ${BUILD_DIR}/EmptyException.o $(BUILD_DIR)/template_parser.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o ${BUILD_DIR}/RouteHandler.o ${BUILD_DIR}/UtunesServer.o ${BUILD_DIR}/HomeController.o ${BUILD_DIR}/SignupController.o ${BUILD_DIR}/SignupHandler.o ${BUILD_DIR}/LogoutHandler.o ${BUILD_DIR}/LoginController.o ${BUILD_DIR}/LoginHandler.o ${BUILD_DIR}/SongController.o ${BUILD_DIR}/LikeHandler.o ${BUILD_DIR}/LikedSongController.o ${BUILD_DIR}/PlaylistsController.o ${BUILD_DIR}/NewPlaylistHandler.o ${BUILD_DIR}/PlaylistController.o ${BUILD_DIR}/AddSongHandler.o ${BUILD_DIR}/RemoveSongHandler.o 
	${CC}	${BUILD_DIR}/main.o ${BUILD_DIR}/CommandHandler.o ${BUILD_DIR}/Utunes.o ${BUILD_DIR}/RecommendationSystem.o ${BUILD_DIR}/AuthenticationSystem.o ${BUILD_DIR}/Session.o ${BUILD_DIR}/User.o ${BUILD_DIR}/XOREncryption.o ${BUILD_DIR}/Song.o ${BUILD_DIR}/Criteria.o ${BUILD_DIR}/PublishYearCriteria.o ${BUILD_DIR}/ArtistCriteria.o ${BUILD_DIR}/LikesCriteria.o ${BUILD_DIR}/AndCriteria.o ${BUILD_DIR}/LikeSystem.o ${BUILD_DIR}/CommentSystem.o ${BUILD_DIR}/PlaylistSystem.o ${BUILD_DIR}/Playlist.o ${BUILD_DIR}/Like.o ${BUILD_DIR}/Comment.o ${BUILD_DIR}/BadRequestException.o ${BUILD_DIR}/PermissionDeniedException.o ${BUILD_DIR}/NotFoundException.o ${BUILD_DIR}/EmptyException.o $(BUILD_DIR)/template_parser.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o ${BUILD_DIR}/RouteHandler.o ${BUILD_DIR}/UtunesServer.o ${BUILD_DIR}/HomeController.o ${BUILD_DIR}/SignupController.o ${BUILD_DIR}/SignupHandler.o ${BUILD_DIR}/LogoutHandler.o ${BUILD_DIR}/LoginController.o ${BUILD_DIR}/LoginHandler.o ${BUILD_DIR}/SongController.o ${BUILD_DIR}/LikeHandler.o ${BUILD_DIR}/LikedSongController.o ${BUILD_DIR}/PlaylistsController.o ${BUILD_DIR}/NewPlaylistHandler.o ${BUILD_DIR}/PlaylistController.o ${BUILD_DIR}/AddSongHandler.o ${BUILD_DIR}/RemoveSongHandler.o -o utunes.out

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

$(BUILD_DIR)/template_parser.o: utils/template_parser.cpp utils/template_parser.hpp utils/request.cpp utils/request.hpp utils/utilities.hpp utils/utilities.cpp
	$(CC) $(CF) -c utils/template_parser.cpp -o $(BUILD_DIR)/template_parser.o

$(BUILD_DIR)/response.o: utils/response.cpp utils/response.hpp utils/include.hpp
	$(CC) $(CF) -c utils/response.cpp -o $(BUILD_DIR)/response.o

$(BUILD_DIR)/request.o: utils/request.cpp utils/request.hpp utils/include.hpp utils/utilities.hpp
	$(CC) $(CF) -c utils/request.cpp -o $(BUILD_DIR)/request.o

$(BUILD_DIR)/utilities.o: utils/utilities.cpp
	$(CC) $(CF) -c utils/utilities.cpp -o $(BUILD_DIR)/utilities.o

$(BUILD_DIR)/server.o: server/server.cpp server/server.hpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp utils/template_parser.hpp utils/template_parser.cpp
	$(CC) $(CF) -c server/server.cpp -o $(BUILD_DIR)/server.o

$(BUILD_DIR)/route.o: server/route.cpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c server/route.cpp -o $(BUILD_DIR)/route.o

${BUILD_DIR}/RouteHandler.o: ${WEB_DIR}/RouteHandler.cpp ${WEB_DIR}/UtunesServer.hpp ${WEB_DIR}/controllers/HomeController.hpp ${WEB_DIR}/controllers/SignupController.hpp ${WEB_DIR}/controllers/SignupHandler.hpp ${WEB_DIR}/controllers/LogoutHandler.hpp ${WEB_DIR}/controllers/LoginController.cpp  ${WEB_DIR}/controllers/LoginHandler.hpp ${WEB_DIR}/controllers/LikeHandler.hpp ${WEB_DIR}/controllers/LikedSongController.cpp ${WEB_DIR}/controllers/PlaylistsController.hpp  ${WEB_DIR}/controllers/NewPlaylistHandler.hpp ${WEB_DIR}/controllers/AddSongHandler.hpp ${WEB_DIR}/controllers/RemoveSongHandler.hpp
	${CC} -c ${WEB_DIR}/RouteHandler.cpp -o ${BUILD_DIR}/RouteHandler.o

${BUILD_DIR}/UtunesServer.o: ${WEB_DIR}/UtunesServer.cpp server/server.hpp
	${CC} -c ${WEB_DIR}/UtunesServer.cpp -o ${BUILD_DIR}/UtunesServer.o

#Controllers

${BUILD_DIR}/HomeController.o: ${WEB_DIR}/controllers/HomeController.cpp server/server.hpp ${SRC_DIR}/Song.hpp 
	${CC} -c ${WEB_DIR}/controllers/HomeController.cpp -o ${BUILD_DIR}/HomeController.o

${BUILD_DIR}/SignupController.o: ${WEB_DIR}/controllers/SignupController.cpp server/server.hpp ${SRC_DIR}/User.hpp ${SRC_DIR}/Utunes.hpp
	${CC} -c ${WEB_DIR}/controllers/SignupController.cpp -o ${BUILD_DIR}/SignupController.o

${BUILD_DIR}/SignupHandler.o: ${WEB_DIR}/controllers/SignupHandler.cpp server/server.hpp ${SRC_DIR}/User.hpp ${SRC_DIR}/Utunes.hpp
	${CC} -c ${WEB_DIR}/controllers/SignupHandler.cpp -o ${BUILD_DIR}/SignupHandler.o

${BUILD_DIR}/LogoutHandler.o: ${WEB_DIR}/controllers/LogoutHandler.cpp server/server.hpp ${SRC_DIR}/Utunes.hpp
	${CC} -c ${WEB_DIR}/controllers/LogoutHandler.cpp -o ${BUILD_DIR}/LogoutHandler.o

${BUILD_DIR}/LoginController.o: ${WEB_DIR}/controllers/LoginController.cpp server/server.hpp
	${CC} -c ${WEB_DIR}/controllers/LoginController.cpp -o ${BUILD_DIR}/LoginController.o

${BUILD_DIR}/LoginHandler.o: ${WEB_DIR}/controllers/LoginHandler.cpp server/server.hpp ${SRC_DIR}/Utunes.hpp
	${CC} -c ${WEB_DIR}/controllers/LoginHandler.cpp -o ${BUILD_DIR}/LoginHandler.o

${BUILD_DIR}/SongController.o: ${WEB_DIR}/controllers/SongController.cpp server/server.hpp ${SRC_DIR}/Utunes.hpp ${SRC_DIR}/Song.hpp
	${CC} -c ${WEB_DIR}/controllers/SongController.cpp -o ${BUILD_DIR}/SongController.o

${BUILD_DIR}/LikeHandler.o: ${WEB_DIR}/controllers/LikeHandler.cpp server/server.hpp ${SRC_DIR}/Utunes.hpp ${SRC_DIR}/Song.hpp
	${CC} -c ${WEB_DIR}/controllers/LikeHandler.cpp -o ${BUILD_DIR}/LikeHandler.o

${BUILD_DIR}/LikedSongController.o: ${WEB_DIR}/controllers/LikedSongController.cpp server/server.hpp ${SRC_DIR}/Utunes.hpp ${SRC_DIR}/Song.hpp
	${CC} -c ${WEB_DIR}/controllers/LikedSongController.cpp -o ${BUILD_DIR}/LikedSongController.o

${BUILD_DIR}/PlaylistsController.o: ${WEB_DIR}/controllers/PlaylistsController.cpp server/server.hpp ${SRC_DIR}/Utunes.hpp ${SRC_DIR}/Song.hpp
	${CC} -c ${WEB_DIR}/controllers/PlaylistsController.cpp -o ${BUILD_DIR}/PlaylistsController.o

${BUILD_DIR}/NewPlaylistHandler.o: ${WEB_DIR}/controllers/NewPlaylistHandler.cpp server/server.hpp ${SRC_DIR}/Utunes.hpp ${SRC_DIR}/Song.hpp
	${CC} -c ${WEB_DIR}/controllers/NewPlaylistHandler.cpp -o ${BUILD_DIR}/NewPlaylistHandler.o

${BUILD_DIR}/PlaylistController.o: ${WEB_DIR}/controllers/PlaylistController.cpp server/server.hpp ${SRC_DIR}/Utunes.hpp ${SRC_DIR}/Song.hpp
	${CC} -c ${WEB_DIR}/controllers/PlaylistController.cpp -o ${BUILD_DIR}/PlaylistController.o

${BUILD_DIR}/AddSongHandler.o: ${WEB_DIR}/controllers/AddSongHandler.cpp server/server.hpp ${SRC_DIR}/Utunes.hpp ${SRC_DIR}/Song.hpp
	${CC} -c ${WEB_DIR}/controllers/AddSongHandler.cpp -o ${BUILD_DIR}/AddSongHandler.o

${BUILD_DIR}/RemoveSongHandler.o: ${WEB_DIR}/controllers/RemoveSongHandler.cpp server/server.hpp ${SRC_DIR}/Utunes.hpp ${SRC_DIR}/Song.hpp
	${CC} -c ${WEB_DIR}/controllers/RemoveSongHandler.cpp -o ${BUILD_DIR}/RemoveSongHandler.o

clean:
	rm -rf ${BUILD_DIR} && mkdir -p ${BUILD_DIR}
	rm utunes.out