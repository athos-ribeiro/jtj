# !/bin/bash
# Author: Edson Alves - edsonalves@unb.br
# Date: 26/11/2010
# Changes made by Jack_The_Janitor authors(check AUTHORS file for more info)
# Date: 5/06/2013

# all
make clean
find . -name *~ -exec rm -f {} \;
find . -name Makefile.in -exec rm -f {} \;
find . -name Makefile -exec rm -f {} \;

# root directory
rm -f aclocal.m4 configure
#rm -f config.log config.status libtool
rm -f config.log config.status
rm -rf config autom4te.cache
#remove game screenshot
#rm screenshot.bmp

# include
cd include
rm -f config.h config.h.in stamp-h1
cd ..

# src
cd src
rm -f jackthejanitor *.o
rm -rf .deps .libs
cd ..

# root dir. JTJ version
rm -f config.h config.h.in depcomp install-sh missing stamp-h1
