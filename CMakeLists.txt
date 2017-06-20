add_executable(playball KApplication.h KEvent.h KEventLoop.h KKeyEvent.h KMutex.h KObject.h KPaintEvent.h KThread.h KApplication.cpp KEventLoop.cpp KMutex.cpp KObject.cpp KThread.cpp playball.cpp)
TARGET_LINK_LIBRARIES(playball libcurses.so libpthread.so)
