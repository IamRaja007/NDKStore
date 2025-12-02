cmake_minimum_required(VERSION 3.10.2)
project("ndkstore")

add_library( # name of the native library
        native-lib

        # library type: shared so System.loadLibrary works
        SHARED

        # source file path here
        src/main/cpp/native-lib.cpp

        #----- add other .cpp files if present -----
)


