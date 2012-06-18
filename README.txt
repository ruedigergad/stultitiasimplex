This file is intended to give an overview of the software and technologies
used in StultitiaSimplex. Additionally, a list of licenses, copyrights, and 
trademarks is given. Though, no claim for completeness is made for this list.


####################
# StultitiaSimplex #
####################

Copyright 2010 Ruediger Gad

StultitiaSimplex is free software: you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the Free
Software Foundation, either version 3 of the License, or (at your option) any
later version.

StultitiaSimplex is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
details.

You should have received a copy of the GNU General Public License along with
StultitiaSimplex.  If not, see http://www.gnu.org/licenses/.


#############
# Libraries #
#############

Except of the standard C and C++ libraries, StultitiaSimplex makes use and 
hence is linked against the following libraries: libsndfile, PortAudio,
PulseAudio, and Qt.

libsndfile by Erik de Castro Lopo is licensed under the terms of the GNU Lesser 
General Public License (LGPL). See also: http://www.mega-nerd.com/libsndfile

PortAudio, Copyright (c) 1999-2000 Ross Bencina and Phil Burk, is licensed 
under the terms of a "plain MIT licence". See also: http://www.portaudio.com

The parts of PulseAudio as used by StultitiaSimplex are licensed under the terms 
of the LGPL. Note: the server component/part of PulseAudio is effectively 
licensed under the terms of the GPL. See also: http://www.pulseaudio.org

Qt, Copyright 2008-2010 by Nokia Corporation, is licensed under the terms of the LGPL
in version 2.1. See also: http://qt.nokia.com

The Windows version of StultitiaSimplex ships with libraries part of the MinGW
runtime. These libraries are public domain, and are not governed by copyright.
See also: http://www.mingw.org
Additionally, all libraries based on GNU tools are licensed under the terms of
the GPL.


################
# Header Files #
################

Additionally to above mentioned libraries the subversion repository of 
StultitiaSimplex contains unmodified header files of libsndfile and PortAudio.
For the detailed licenses etc. please see the respective header files.


#############
# Packaging #
#############

The Windows version ships with dynamic link libraries (DLLs) taken from libsndfile,
, MinGW, PortAudio, and Qt. The PortAudio DLL has been compiled from a
PortAudio v19 trunk snapshot dated 2010-10-28.

The Linux version does not ship with additional libraries. Please see your
respective distribution documentation on how to obtain the required libraries.


##############
# Trademarks #
##############

Linux is a registered trademark of Linus Torvalds.
Nokia, Qt and their respective logos are trademarks of Nokia Corporation in 
Finland and/or other countries worldwide. 
Windows is a registered trademark of Microsoft Corporation in the United States 
and other countries.
All other trademarks are property of their respective owners



