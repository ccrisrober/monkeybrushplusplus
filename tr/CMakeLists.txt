source_group(\\ FILES CMakeLists.txt)

set( TR_PUBLIC_HEADERS
    iniReader.h
    picojson.h
)

set( TR_HEADERS )

set( TR_SOURCES
    iniReader.cpp
)

set( TR_LINK_LIBRARIES
)

common_library( tr )
