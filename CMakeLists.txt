add_executable(playball playball.cpp KObject.h KObject.cpp KApplication.h KApplication.cpp KThread.h KThread.cpp)
TARGET_LINK_LIBRARIES(playball libcurses.so libpthread.so)
