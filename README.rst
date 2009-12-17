OpenFrameworks
==============

This is an *unofficial* mirror of openFrameworks source code. 
Added cmake files to build openframeworks as a shared library and mac os x frameworks

What differs from official release 
----------------------------------

* Patched ofSoundStream.cpp to be compatible with the last RtAudio (>0.4) API.
* Patched to use Gstreamer API for video capture (see this topic [#] on OF forum)

Tested on Snow Leopard and Ubuntu Linux 9.10

Any suggestions/bugs: f.visconte@gmail.con

Installing OpenFrameworks dependencies
--------------------------------------

Openframeworks use few cross-platform APIs to handle sound, video etc...

Openframeworks depends on;

+--------------+-----+------+-------+-------------------------------------------------------+
|              |Linux|MaxOsX|Windows| Homepage                                              |
+--------------+-----+------+-------+-------------------------------------------------------+
| RtAudio      |  X  |  X   |   ?   |   http://www.music.mcgill.ca/~gary/rtaudio/           |
+--------------+-----+------+-------+-------------------------------------------------------+
| Unicap       |  X  |  ?   |   ?   |   http://unicap-imaging.org/download.htm              |
+--------------+-----+------+-------+-------------------------------------------------------+
| videoInput   |     |      |   ?   |   http://muonics.net/school/spring05/videoInput/      |
+--------------+-----+------+-------+-------------------------------------------------------+
| poco         |  X  |  X   |   X   |   http://pocoproject.org/                             |
+--------------+-----+------+-------+-------------------------------------------------------+
| glfw         |  X  |  X   |   X   |   http://glfw.sourceforge.net/                        |
+--------------+-----+------+-------+-------------------------------------------------------+
| glut         |  X  |  X   |   X   |   http://www.opengl.org/resources/libraries/glut/     |
+--------------+-----+------+-------+-------------------------------------------------------+
| freetype     |  X  |  X   |   X   |   http://www.freetype.org/index2.html                 |
+--------------+-----+------+-------+-------------------------------------------------------+
| freeimage    |  X  |  X   |   X   |   http://freeimage.sourceforge.net/download.html      |
+--------------+-----+------+-------+-------------------------------------------------------+
| fmodex       |  X  |      |   X   |   http://www.fmod.org/                                |
+--------------+-----+------+-------+-------------------------------------------------------+
| GLee         |  X  |  X   |   X   |   http://www.opengl.org/sdk/libs/GLee/                |
+--------------+-----+------+-------+-------------------------------------------------------+


On Linux
########

RtAudio
++++++++

..
 tar zxvf rtaudio-<version>.tar.gz
 cd rtaudio-<version>
 ./configure
 make 
 cp RtAudio.h RtError.h ./../libsLinux/include
 cp librtaudio.a ./../libsLinux/lib

Unicap
++++++


..
 ./configure --enable-static --disable-shared --prefix=/tmp/unicap --disable-unicapgtk ; make ; make install
 cp -R /tmp/unicap/lib/ ./../libsLinux/lib
 cp -R /tmp/unicap/include ./../libsLinux/include


glfw
++++

..
 apt-get install libglfw-dev libglfw2

glut
++++

..
 apt-get install libglut3 libglut3-dev

freetype
++++++++

..
 apt-get install libfreetype6 libfreetype6-dev

FreeImage
+++++++++

..
 cd FreeImage
 make
 sudo cp Dist/FreeImage.h /usr/local/include
 sudo cp Dist/libfreeimage.a /usr/local/lib

GLee
++++

..
 mkdir GLee
 cd GLee
 tar zxvf GLee-5.4.0-src.tar.gz
 make
 sudo cp libGLee.so /usr/local/lib
 sudo cp GLee.h /usr/local/include

fmodex
++++++


On Mac OS X
###########

..
 export OFX_LIBS=/opt/openFrameworks/
 sudo mkdir $OFX_LIBS
 sudo mkdir $OFX_LIBS/include
 sudo mkdir $OFX_LIBS/lib

GLee
++++

..
 mkdir GLee
 cd GLee
 tar zxvf ../dist/GLee-5.4.0-src.tar.gz
 ./configure CXXFLAGS="-m32 -framework CoreFoundation -framework OpenGL" ; make
 make 
 sudo cp libGLee.so $OFX_LIBS/lib
 sudo cp GLee.h $OFX_LIBS/include
 cd ..


RtAudio
+++++++

..
 tar zxvf ./dist/rtaudio-4.0.6.tar.gz
 cd rtaudio-4.0.6
 ./configure --enable-static CXXFLAGS=-m32  # check in the makefile that -m32 was take
 make
 sudo cp librtaudio.a $OFX_LIBS/lib/libRtAudio.a
 sudo cp RtAudio.h RtError.h $OFX_LIBS/include/
 cd ..


FreeImage
+++++++++

..
 unzip ./dist/FreeImage3130.zip
 cd FreeImage
 # edit Makefile.osx to change paths to SDK. For example on my 10.6 (snow leopard):
 -------------------------------------
 INCLUDE_PPC = -isysroot /Developer/SDKs/MacOSX10.6.sdk
 INCLUDE_I386 = -isysroot /Developer/SDKs/MacOSX10.6.sdk 
 --------------------------------------
 make 
 sudo cp Source/FreeImage.h $OFX_LIBS/include/
 sudo cp libfreeimage.a $OFX_LIBS/lib/libFreeImage.a


Poco
++++

..
 -------------------------------------
 ...
 LINKMODE = STATIC
 ...
 CXXFLAGS        = -Wall -Wno-sign-compare -m32 -arch i386
 ...
 -------------------------------------
 for i in CppUnit Foundation XML Net Util; do
     (cd $i ; make static_release)
 done
 # install
 mkdir -p $OFX_LIBS/include/Poco/
 
 for i in Foundation XML Net Util; do
    sudo cp -rf $i/include/* $OFX_LIBS/include/
 done
 sudo cp lib/Darwin/i386/lib*.a /opt/openFrameworks/lib


glfw
++++

..
 unzip dist/glfw-2.6.zip
 cd glfw
 cd lib/macosx
 # edit Makefile.macosx.gcc.universal and adjust your SDK path:
 FATFLAGS     = -isysroot /Developer/SDKs/MacOSX10.6.sdk -arch ppc -arch i386
 make -f Makefile.macosx.gcc.universal
 sudo cp libglfw.a $OFX_LIBS/lib
 sudo cp ../../include/GL/glfw.h $OFX_LIBS/include


Freetype2
+++++++++

Freetype is already included in mac os x with X11 package


FMODEX
++++++

Install the distributed package. The installer install files in /Developer/FMOD Programmers API Mac/.
Copy the libraries and includes in $OFX_LIB prefix:

..
 sudo cp /Developer/FMOD\ Programmers\ API\ Mac/api/inc/* $OFX_LIB/include
 sudo cp /Developer/FMOD\ Programmers\ API\ Mac/api/lib/* $OFX_LIB/lib       

Links 
------

.. [#] http://www.openframeworks.cc/forum/viewtopic.php?f=5&t=2097

