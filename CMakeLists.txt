cmake_minimum_required(VERSION 2.8  FATAL_ERROR)

add_definitions( -std=c++11 -g )

ADD_SUBDIRECTORY(test)

SET(LIB_TARGET thread_pool)

SET(LIB_SRC 
    CThread.cpp  
    CThreadPool.cpp  
    )

SET(DEPEND_LIBS 
    pthread
    
    )

add_library(${LIB_TARGET} SHARED ${LIB_SRC} )
target_link_libraries(${LIB_TARGET} ${DEPEND_LIBS} )

