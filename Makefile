## -*- Makefile -*-
##
## User: Justine Dewilde
## Time: 4 mai 2015 12:56:27
## Makefile created by Oracle Solaris Studio.
##
## This file is generated automatically.
##


#### Compiler and tool definitions shared by all build targets #####
CCC = g++
CXX = g++
BASICOPTS = -g
CCFLAGS = $(BASICOPTS)
CXXFLAGS = $(BASICOPTS)
CCADMIN = 


# Define the target directories.
TARGETDIR_catapult.exe=GNU-amd64-Windows


all: $(TARGETDIR_catapult.exe)/catapult.exe

## Target: catapult.exe
OBJS_catapult.exe =  \
	$(TARGETDIR_catapult.exe)/catapult.o \
	$(TARGETDIR_catapult.exe)/main.o \
	$(TARGETDIR_catapult.exe)/utils.o
SYSLIBS_catapult.exe = -lm -lpthread 
USERLIBS_catapult.exe = $(SYSLIBS_catapult.exe) 
DEPLIBS_catapult.exe =  
LDLIBS_catapult.exe = $(USERLIBS_catapult.exe)


# Link or archive
$(TARGETDIR_catapult.exe)/catapult.exe: $(TARGETDIR_catapult.exe) $(OBJS_catapult.exe) $(DEPLIBS_catapult.exe)
	$(LINK.cc) $(CCFLAGS_catapult.exe) $(CPPFLAGS_catapult.exe) -o $@ $(OBJS_catapult.exe) $(LDLIBS_catapult.exe)


# Compile source files into .o files
$(TARGETDIR_catapult.exe)/catapult.o: $(TARGETDIR_catapult.exe) catapult.cpp
	$(COMPILE.cc) $(CCFLAGS_catapult.exe) $(CPPFLAGS_catapult.exe) -o $@ catapult.cpp

$(TARGETDIR_catapult.exe)/main.o: $(TARGETDIR_catapult.exe) main.cpp
	$(COMPILE.cc) $(CCFLAGS_catapult.exe) $(CPPFLAGS_catapult.exe) -o $@ main.cpp

$(TARGETDIR_catapult.exe)/utils.o: $(TARGETDIR_catapult.exe) utils.cpp
	$(COMPILE.cc) $(CCFLAGS_catapult.exe) $(CPPFLAGS_catapult.exe) -o $@ utils.cpp



#### Clean target deletes all generated files ####
clean:
	rm -f \
		$(TARGETDIR_catapult.exe)/catapult.exe \
		$(TARGETDIR_catapult.exe)/catapult.o \
		$(TARGETDIR_catapult.exe)/main.o \
		$(TARGETDIR_catapult.exe)/utils.o
	$(CCADMIN)
	rm -f -r $(TARGETDIR_catapult.exe)


# Create the target directory (if needed)
$(TARGETDIR_catapult.exe):
	mkdir -p $(TARGETDIR_catapult.exe)


# Enable dependency checking
.KEEP_STATE:
.KEEP_STATE_FILE:.make.state.GNU-amd64-Windows

