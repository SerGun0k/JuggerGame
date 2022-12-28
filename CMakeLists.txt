cmake_minimum_required(VERSION 3.15) # Проверка версии CMake.
SET(CMAKE_CONFIGURATION_TYPES "Release")
									 # Если версия установленой программы
									 # старее указаной, произайдёт аварийный выход.

set(PROJECT_NAME Project)				 # имя проекта		 
project("${PROJECT_NAME}")


set(CMAKE_CXX_STANDARD 17)			 # устанавливаем 17 стандарт языка
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)


add_definitions(-DSFML_STATIC)		 # дефайны

include_directories("SFML/include/")	# добавляем директории
include_directories("inc/")
link_directories("SFML/lib/")	

add_executable("${PROJECT_NAME}" FirstGame.cpp 
				 inc/map.h
				 inc/View.h
)
									
target_link_libraries("${PROJECT_NAME}" sfml-graphics-s
						  sfml-window-s
						  sfml-system-s
						  opengl32
						  freetype
						  winmm
						  gdi32
						  sfml-audio-s
						  openal32
						  flac
						  vorbisenc
						  vorbisfile
						  vorbis
						  ogg)
						  
file(COPY "Images" DESTINATION "/")
file(COPY "Audio" DESTINATION "/")
file(COPY "CyrilicOld.TTF" DESTINATION "/")	
file(COPY "openal32.dll" DESTINATION "/")					  