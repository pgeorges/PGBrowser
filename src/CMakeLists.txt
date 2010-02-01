
include_directories (.)
Include_directories (${PGBROWSER_SOURCE_DIR}/thirdparty/QtSingleApplication2.6/src)

link_directories (${PGBROWSER_BINARY_DIR}/thirdparty/QtSingleApplication2.6) 

file(GLOB pgbrowser_HEADERS *.h network/*.h widgets/*.h bookmarks/*.h)
file(GLOB pgbrowser_SOURCES *.cpp network/*.cpp widgets/*.cpp bookmarks/*.cpp)

#message(source files:${pgbrowser_SOURCES} )


add_definitions( -Wall )
set( QT_USE_QTXML TRUE )
SET( QT_USE_QTNETWORK TRUE )
SET( QT_USE_QTWEBKIT TRUE )

# (QT_USE_FILE is defined by FIND_PACKAGE( Qt4 ) and contains a path to CMake script)
find_package( Qt4 REQUIRED )
include( ${QT_USE_FILE} )

# Generate moc files
QT4_WRAP_CPP( pgbrowser_MOC_SOURCES ${pgbrowser_HEADERS} )

add_executable(pgbrowser 
               ${pgbrowser_SOURCES} 
               ${pgbrowser_MOC_SOURCES})

target_link_libraries(pgbrowser 
		      qtsingleapp 
		      ${QT_LIBRARIES})
