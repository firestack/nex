project (nex-system)

set (SRC_DIR ${NEX_SOURCE_DIR}/nex/system)
set (INC_DIR ${NEX_INCLUDE_DIR}/nex/system)

set (NEX_SYSTEM_HEADERS
    ${INC_DIR}/typedefs.h
    ${INC_DIR}/utf.h
    ${INC_DIR}/utf.inl
    ${INC_DIR}/string.h
    ${INC_DIR}/string.inl
    ${INC_DIR}/instream.h
    ${INC_DIR}/outstream.h
    ${INC_DIR}/memoryinputstream.h
    ${INC_DIR}/memoryoutputstream.h

    ${INC_DIR}/noncopyable.h
    ${INC_DIR}/logger.h
)

set (NEX_SYSTEM_SRC
    ${SRC_DIR}/string.cpp
    ${SRC_DIR}/instream.cpp
    ${SRC_DIR}/outstream.cpp
    ${SRC_DIR}/memoryinputstream.cpp
    ${SRC_DIR}/memoryoutputstream.cpp
    ${SRC_DIR}/logger.cpp
)

include_directories (${NEX_INCLUDE_DIR})
add_library (${NEX_SYSTEM_LIB} STATIC ${NEX_SYSTEM_HEADERS} ${NEX_SYSTEM_SRC})
