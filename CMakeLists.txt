add_executable(playball KApplication.cpp KEventLoop.cpp KKeyListener.cpp KMutex.cpp KObject.cpp KThread.cpp playball.cpp KApplication.h KEvent.h KEventLoop.h KKeyEvent.h KKeyListener.h KMutex.h KObject.h KPaintEvent.h KThread.h)
TARGET_LINK_LIBRARIES(playball libcurses.so libpthread.so)
