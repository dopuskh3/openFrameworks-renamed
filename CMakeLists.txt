# vim:set ft=cmake:syn on
cmake_minimum_required(VERSION 2.6)
project(openFrameworks)
set(OPENFRAMEWORKS_VERSION "0.6")
set(OPENFRAMEWORKS_INSTALL_PREFIX "/usr/local")
get_filename_component(OPENFRAMEWORKS_INSTALL_PREFIX ${OPENFRAMEWORKS_INSTALL_PREFIX} ABSOLUTE)
set(OPENFRAMEWORKS_LIB_DIR "${OPENFRAMEWORKS_INSTALL_PREFIX}/lib")
set(OPENFRAMEWORKS_INCLUDE_DIR "${OPENFRAMEWORKS_INSTALL_PREFIX}/include")
set(OPENFRAMEWORKS_PKGCONFIG_DIR "${OPENFRAMEWORKS_INSTALL_PREFIX}/lib/pkgconfig")


# set (OPENFRAMEWORKS_PREFIX "/opt/openFrameworks")

include(openFrameworks.cmake)

set (OFX_SOURCE_FILES 
    app/ofAppGlutWindow.cpp
    events/ofEvents.h
    events/ofEventUtils.h
    utils/ofConstants.h
    utils/ofUtils.h
    utils/ofMath.cpp
    utils/ofTypes.h
    utils/ofUtils.cpp
    utils/ofMath.h
    ofMain.h
    graphics/ofImage.h
    graphics/ofGraphics.cpp
    graphics/ofGraphics.h
    graphics/ofBitmapFont.cpp
    graphics/ofBitmapFont.h
    graphics/ofTrueTypeFont.h
    graphics/ofTrueTypeFont.cpp
    graphics/ofTexture.cpp
    graphics/ofImage.cpp
    graphics/ofTexture.h
    communication/ofArduino.h
    communication/ofStandardFirmata.cpp
    communication/ofSerial.cpp
    communication/ofSerial.h
    communication/ofStandardFirmata.h
    communication/ofArduino.cpp
    video/ofUCUtils.h
    video/ofVideoGrabber.h
    video/ofVideoPlayer.h
    video/ofUCUtils.cpp
    video/ofQtUtils.cpp
    video/ofVideoPlayer.cpp
    video/ofQtUtils.h
    video/ofV4LUtils.h
    video/ofVideoGrabber.cpp
    sound/ofSoundStream.h
    sound/ofSoundStream.cpp
    sound/ofSoundPlayer.cpp
    sound/ofSoundPlayer.h
    app/ofBaseApp.h
    app/ofAppRunner.h
    app/ofAppRunner.cpp
    app/ofAppBaseWindow.h
    app/ofAppGlutWindow.h )



set(ofincludes       . 
                     app
                     communication
                     events
                     graphics
                     sound
                     utils
                     video)

set(ofincludes_files 
    events/ofEvents.h
    events/ofEventUtils.h
    utils/ofConstants.h
    utils/ofUtils.h
    utils/ofTypes.h
    utils/ofMath.h
    ofMain.h
    graphics/ofImage.h
    graphics/ofGraphics.h
    graphics/ofBitmapFont.h
    graphics/ofTrueTypeFont.h
    graphics/ofTexture.h
    communication/ofArduino.h
    communication/ofSerial.h
    communication/ofStandardFirmata.h
    video/ofUCUtils.h
    video/ofVideoGrabber.h
    video/ofVideoPlayer.h
    video/ofQtUtils.h
    video/ofV4LUtils.h
    sound/ofSoundStream.h
    sound/ofSoundPlayer.h
    app/ofBaseApp.h
    app/ofAppRunner.h
    app/ofAppBaseWindow.h
    app/ofAppGlutWindow.h)



include_directories( ${ofincludes} )
include_directories(${OPENFRAMEWORKS_INCLUDES})


##################################################################
## Configure library generation
add_library( openFrameworksShared SHARED ${OFX_SOURCE_FILES})
#add_library( openFrameworksStatic ${OFX_SOURCE_FILES})
#set_target_properties (openFrameworksStatic 
#                        PROPERTIES OUTPUT_NAME openFrameworks )

set_target_properties (openFrameworksShared 
                        PROPERTIES OUTPUT_NAME openFrameworks )

target_link_libraries(openFrameworksShared ${OPENFRAMEWORKS_LIBRARIES})
##################################################################
## Setup pkg-config file (openFrameworks.pc 
##################################################################

# other way to expand include dirs ?
foreach (dir ${OPENFRAMEWORKS_INCLUDES})
    set(inccmd "${inccmd} -I${dir}")    
endforeach()
set (inccmd "${inccmd} -I${OPENFRAMEWORKS_INCLUDE_DIR}/openFrameworks" )

#foreach(dir ${ofincludes})
#    set(inccmd "${inccmd} -I${OPENFRAMEWORKS_INSTALL_PREFIX}/${dir}")
#endforeach()
set ( prefix ${OPENFRAMEWORKS_INSTALL_PREFIX})
set ( libdir ${OPENFRAMEWORKS_LIB_DIR})
set ( includedir ${OPENFRAMEWORKS_INCLUDE_DIR}/openFrameworks )
# set 
set(flags "${inccmd}")
if ( APPLE ) 
    set(libs  "-framework OpenGL")
endif ()

configure_file("openFrameworks.pc.in" "openFrameworks.pc")


#################################################################
## Install things

# install library
install(FILES ${ofincludes_files}
        DESTINATION "${OPENFRAMEWORKS_INCLUDE_DIR}/openFrameworks")

install(TARGETS openFrameworksShared 
        DESTINATION ${OPENFRAMEWORKS_LIB_DIR})

install(FILES openFrameworks.pc
        DESTINATION ${OPENFRAMEWORKS_PKGCONFIG_DIR})
#target_link_libraries(openFrameworksStatic ${OPENFRAMEWORKS_LIBRARIES})
#if ( APPLE )
#    set_target_properties(openFrameworksShared
#            PROPERTIES    FRAMEWORK               TRUE
#            PROPERTIES OUTPUT_NAME openFrameworks 
#            LIBRARY             DESTINATION  "./lib"
#            # PUBLIC_HEADER           "${FLAT_HDRS}"
#            )
#    install(TARGETS openFrameworksShared
#            FRAMEWORK           DESTINATION framewk)
#
#endif()
