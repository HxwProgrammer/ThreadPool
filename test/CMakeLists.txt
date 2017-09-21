cmake_minimum_required(VERSION 2.8  FATAL_ERROR)

add_definitions( -std=c++11 -g )
SET(TARGET test)

SET(SRC 
    main.cpp  
    Runable.cpp
    )

SET(DEPEND_LIBS 
    pthread
    thread_pool
    )


add_executable(${TARGET} ${SRC})
target_link_libraries(${TARGET} ${DEPEND_LIBS} )

