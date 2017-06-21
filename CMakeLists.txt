set(CMAKE_BUILD_TYPE Debug CACHE STRING "set build type to debug")  
add_executable(playball KApplication.h KEvent.h KEventLoop.h KFont.h KKeyEvent.h KKeyListener.h KMutex.h KObject.h KPainter.h KPaintEvent.h KQuitEvent.h KSemaphore.h KThread.h KWidget.h KApplication.cpp KEventLoop.cpp KFont.cpp KKeyListener.cpp KMutex.cpp KObject.cpp KPainter.cpp KSemaphore.cpp KThread.cpp KWidget.cpp playball.cpp)
TARGET_LINK_LIBRARIES(playball libcurses.so libpthread.so)
