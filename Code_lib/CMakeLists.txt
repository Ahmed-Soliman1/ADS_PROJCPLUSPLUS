project(Code_lib)

set(HEADER_FILES
        expressiontree.h
)

set(SOURCE_FILES
        expressiontree.cpp
        TreeNode.h
        Stackt.cpp
        Stackt.h
)

add_library(Code_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})