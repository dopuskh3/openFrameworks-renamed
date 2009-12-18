==============
OpenFrameworks
==============

.. contents:: Table of Contents
   :depth: 2


This is an **unofficial** mirror of openFrameworks source code. The following repository aims at providing patches and a easy build system for
openFramework framework. 

Added cmake files to build openframeworks as a shared library and mac os x frameworks

**Any comment, help or suggestions are wellcome f.visconte@gmail.com**

What differs from official release 
----------------------------------

The following patch have been applied
* Patched ofSoundStream.cpp to be compatible with the last RtAudio (>0.4) API (see [#]_).
* Patched to use Gstreamer API for video capture (see this topic [#]_ on OF forum)

Tested on:
 * Snow Leopard
 * Ubuntu Linux 9.10
 * Debian Squeeze

Todo List
---------

* check for build-time defines and compile time options. Add them to cmake variable (eg. data/ path etc...)
* add OF examples to reposotory
* make a debian package (need to package unpackaged dependencies too). Licence problem for fmodex ? 
* add a sample project and addon with the cmake file to build them.
* test, test , test

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

Install the following dependencies (on Ubuntu Karmic, debian Squeez)::
 
 apt-get install libxi-dev libxmu-dev pkg-config libgstreamer-plugins-base0.10-dev \
                  libgstreamer0.10-dev libavformat-dev libswscale-dev libraw1394-dev \
                  libhal-dev libavcodec-dev, libavutil-dev, libasound2-dev, libxv-dev \
                  x11proto-video-dev 

Install unicap library if you chose to use unicap for video capture::
 
 apt-get install libunicap2-dev libunicap2


RtAudio
++++++++

::
  
  tar zxvf rtaudio-<version>.tar.gz
  cd rtaudio-<version>
  ./configure
  make 
  cp RtAudio.h RtError.h ./../libsLinux/include
  cp librtaudio.a ./../libsLinux/lib


Unicap
++++++


::
  
  ./configure --enable-static --disable-shared --prefix=/tmp/unicap --disable-unicapgtk ; make ; make install
  cp -R /tmp/unicap/lib/ ./../libsLinux/lib
  cp -R /tmp/unicap/include ./../libsLinux/include



glfw
++++

::
  
  apt-get install libglfw-dev libglfw2

glut
++++

::
  
  apt-get install libglut3 libglut3-dev

freetype
++++++++

::
  
  apt-get install libfreetype6 libfreetype6-dev

FreeImage
+++++++++

::
  
  cd FreeImage
  make
  sudo cp Dist/FreeImage.h /usr/local/include
  sudo cp Dist/libfreeimage.a /usr/local/lib

GLee
++++

::
  
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

You have to compile all dependencies in i386 architecture. If  you are on Snow Leopard you may need to add -m32, -arch i386 
or others compile flags (see bellow). On OS X Leopard those compile flags may not be necessary.

Set the following variables to avoid typing thoses variables each time you compile/install a library::
  
  export OFX_LIBS=/opt/openFrameworks/
  sudo mkdir $OFX_LIBS
  sudo mkdir $OFX_LIBS/include
  sudo mkdir $OFX_LIBS/lib

GLee
++++

::
  
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

::
  
  tar zxvf ./dist/rtaudio-4.0.6.tar.gz
  cd rtaudio-4.0.6
  ./configure --enable-static CXXFLAGS=-m32  # check in the makefile that -m32 was take
  make
  sudo cp librtaudio.a $OFX_LIBS/lib/libRtAudio.a
  sudo cp RtAudio.h RtError.h $OFX_LIBS/include/
  cd ..


FreeImage
+++++++++

::
  
  unzip ./dist/FreeImage3130.zip
  cd FreeImage


Edit Makefile.osx to change paths to SDK. For example on my 10.6 (snow leopard)::
  
  INCLUDE_PPC = -isysroot /Developer/SDKs/MacOSX10.6.sdk
  INCLUDE_I386 = -isysroot /Developer/SDKs/MacOSX10.6.sdk 

Compile and install::
  
  make 
  sudo cp Source/FreeImage.h $OFX_LIBS/include/
  sudo cp libfreeimage.a $OFX_LIBS/lib/libFreeImage.a


Poco
++++

Edit build configuration file into **build/config/Darwin** and modify the following lines:: 
  
  ...
  LINKMODE = STATIC
  ...
  CXXFLAGS        = -Wall -Wno-sign-compare -m32 -arch i386
  ...

You can compile the libraries with the following command::
  
  for i in CppUnit Foundation XML Net Util; do
      (cd $i ; make static_release)
  done 
  


And instal the libraries and includes files:: 
  
  mkdir -p $OFX_LIBS/include/Poco/
   
  for i in Foundation XML Net Util; do
     sudo cp -rf $i/include/* $OFX_LIBS/include/
  done
  sudo cp lib/Darwin/i386/lib*.a /opt/openFrameworks/lib



glfw
++++

::
  
  unzip dist/glfw-2.6.zip
  cd glfw
  cd lib/macosx

Edit **Makefile.macosx.gcc.universal** and adjust your SDK path::
  
  FATFLAGS     = -isysroot /Developer/SDKs/MacOSX10.6.sdk -arch ppc -arch i386

Then compile::
  
  make -f Makefile.macosx.gcc.universal
  sudo cp libglfw.a $OFX_LIBS/lib
  sudo cp ../../include/GL/glfw.h $OFX_LIBS/include


Freetype2
+++++++++

Freetype is already included in OS X with X11 package


FMODEX
++++++

Install the distributed package. The installer install files in /Developer/FMOD Programmers API Mac/.

Copy the libraries and includes in $OFX_LIB prefix::
  
  sudo cp /Developer/FMOD\ Programmers\ API\ Mac/api/inc/* $OFX_LIB/include
  sudo cp /Developer/FMOD\ Programmers\ API\ Mac/api/lib/* $OFX_LIB/lib       

Building
--------

OpenFrameworks use CMake [#]_ to configure OF code. CMake is able to generate Xcode, Eclipse, Codeblocks, GNU Makefiles, Visual Studio (?) project files.

To compile OF library or framework it may be easyer to use GNU Makefile generator which is (i think) the easyer unless you want to modify OF code.

The following cmake variables can be configured to change compile/install behavior:
 * **OPENFRAMEWORKS_INSTALL_PREFIX** : OF install prefix 
 * **OPENFRAMEWORKS_PKGCONFIG_DIR** : openFrameworks.pc install path (/usr/local/lib/pkgconfig)
 * **OPRENFRAMEWORKS_PREFIX** : openFrameworks dependencies prefix

Those variales can be configured as well be should be OK by default:
 * **POCO_INCLUDES**: poco include path
 * **POCO_LIBRARIES**: poco libraries path
 * **RTAUDIO_INCLUDES**: rtaudio include path
 * **RTAUDIO_LIBRARIES**: rtaudio libraries path
 * **FMODEX_INCLUDES**: fmodex include path
 * **FMODEX_LIBRARIES**: fmodex libraries path
 * **FREEIMAGE_INCLUDES**: freeimage include path
 * **FREEIMAGE_LIBRARIES**: freeimage libraries
 * **GLEE_INCLUDES**: GLee include path
 * **GLEE_LIBRARIES**: GLee libraries path 

On Linux
########


Configure the code with the following command::
 
 cmake .

If you want to override default install prefix, compile flags etc... you can use **cmake-gui** command and change variables default values.

Then compile and install::
 
 make
 make install

On OS X
#######

Build generate a standard Max OS X framework under OS X. 
Under Snow Leopard you have to pass **-m32** to **CFLAGS** to compile for i386 architecture.

::
 
 cmake -DCMAKE_CXX_FLAGS=-m32 . 
 make 
 make install


Links 
------
.. [#] http://www.openframeworks.cc/forum/viewtopic.php?f=7&t=2968
.. [#] http://www.openframeworks.cc/forum/viewtopic.php?f=5&t=2097
.. [#] http://www.cmake.org/

