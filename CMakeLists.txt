add_executable(playball playball.cpp KKeyEvent.h KPaintEvent.h KEvent.h KObject.h KObject.cpp KApplication.h KApplication.cpp KThread.h KThread.cpp)
TARGET_LINK_LIBRARIES(playball libcurses.so libpthread.so)
