# This is an application
TEMPLATE=app

# The binary name
TARGET=myrcv

# This app uses Qtopia
CONFIG+=qtopia

# Build this app as a quicklauncher plugin
# You need to be using the QTOPIA_ADD_APPLICATION/QTOPIA_MAIN macros or this will not work!
#CONFIG+=quicklaunch

# Build this project into the singleexec binary
#CONFIG+=singleexec

# Specify the languages that make lupdate should produce .ts files for
STRING_LANGUAGE=en_US
LANGUAGES=en_US de

# Package information (used for qbuild packages)
pkg [
    name=myrcv
    desc="My Receive"
    license=Commercial
    version=1.0.0-1
    maintainer="QuietHeart"
]

# These are the source files that get built to create the application
#FORMS=\
#    examplebase.ui

HEADERS=\
    myrcv.h

SOURCES=\
    main.cpp\
    myrcv.cpp

# SXE information
#target [
#    hint=sxe
#    domain=untrusted
#]

# Install the launcher item. The metadata comes from the .desktop file
# and the path here.
desktop [
    hint=desktop nct
    files=myrcv.desktop
    path=/apps/Applications
    trtarget=myrcv-nct
]

# Install some pictures.
#pics [
#    hint=pics
#    files=pics/*
#    path=/pics/example
#]

# Install help files
#help [
#    hint=help
#    source=help
#    files=example.html
#]

