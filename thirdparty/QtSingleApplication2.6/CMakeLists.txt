
include_directories (src)

SET( QT_USE_QTNETWORK TRUE )
find_package(Qt4 REQUIRED) 
include(${QT_USE_FILE})

set( SOURCE_FILES
     src/qtsingleapplication.cpp
     src/qtlockedfile.cpp
     src/qtlockedfile_unix.cpp
     src/qtsinglecoreapplication.cpp
     src/qtlocalpeer.cpp
)
set( HEADER_FILES
     src/qtsingleapplication.h
     src/qtsinglecoreapplication.h
     src/qtlocalpeer.h
)
# Generate moc files
QT4_WRAP_CPP( MOC_SOURCE_FILES ${HEADER_FILES} )

add_library(qtsingleapp STATIC
	    ${SOURCE_FILES}
	    ${MOC_SOURCE_FILES}
            )

