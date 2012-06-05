# Arduino Makefile
# by Rowland O'Flaherty <rowlandoflaherty.com>
#
# This makefile allows you to build .cpp files for arduino from the command line
# on OS X without using the Arduino environment (or Java).  Also, you can
# facilitates the use of Xcode as a development environment in order to give the
# programmer professional editing features and a source code management client.
#
#
# Instructions for using the makefile:
#
#  1.	Make sure you have Arduino.app (version >= 1.0) installed.
#
#  2.   Navigate into the Arduino.app folder (right click, Show Package Contents)
#		then to /Contents/Resources/Java/libraries/Firmata. Inside this folder
#		there is file name "Boards.h". Open this file with your favorite text 
#		editor and comment out the lines 8, 10, 11, and 12. Should look like this:
#
#		//#if defined(ARDUINO) && ARDUINO >= 100
#		#include "Arduino.h"	// for digitalRead, digitalWrite, etc
#		//#else
#		//#include "WProgram.h"
#		//#endif
#
#		Save and close this file. Really stupid that the Arduino people didn't
#		include the "WProgram.h" file for backwards compatibility.
#
#  3.	Copy this "Makefile" into the folder with your main.cpp file.
#     
#  2.	Modify the enviroment variables below for your system.
#
#  3.	At the command line, change to the directory containing your program's
#		file and the Makefile.
#
#  4a.	Type "make" and press enter to compile/verify your program.
#
#  4b.	Type "make upload" and press enter to upload your program to the Arduino
#		board.
#
#
#	Setting Enviroment Variables:
#
#	The default values can be set by changing the values in this Makefile.
#	To set the variables for one time use at the command line do something like
#	the following when executing the "make" command.
#
#		make SOURCE="somefile.cpp" BOARD="diecimila" upload
#
#
#	Enviroment Variables:
#
#		SOURCE -
#			Name of the source file to your program (e.g. main.cpp)
#
#		BOARD -
#			Type of Arduino board.
#			Options are:
#				uno, atmega328, diecimila, nano328, nano, mega2560, mega, leonardo,
#				micro, mini, ethernet, fio, bt328, bt, lilypad328, lilypad,
#				pro5v328, pro5v, pro328, pro, atmega168, atmega8
#
#		ARDUINO_DIR -
#			Directory where the Arduino folder is located.
#
#		ARDUINO_APP - 
#			Directory where the Arduino application is located.
#
#		PORT - 
#			Serial port connected to the Arduino board.
#
#	Note:
#		This will not program the EEPROM memory. But can easily be modified to
#		do so if you would like.
#
#-------------------------------------------------------------------------------


# Name of source file with extension (e.g. main.cpp)----------------------------
#-------------------------------------------------------------------------------
SOURCE = main.cpp


# Name of source file with extension (e.g. main.cpp)----------------------------
#-------------------------------------------------------------------------------
BOARD = uno


# Directory continaing user added libraries ------------------------------------
#-------------------------------------------------------------------------------
ARDUINO_DIR = ~/Dropbox/Arduino


# Directory continaing Arduino.app ---------------------------------------------
#-------------------------------------------------------------------------------
ARDUINO_APP = /Applications/Arduino.app


# Serial port connected to board -----------------------------------------------
#-------------------------------------------------------------------------------
PORT = /dev/tty.usb*


################################################################################
# Below here nothing should have to be changed...


# Define shell -----------------------------------------------------------------
SHELL := /bin/bash


# Define source base name ------------------------------------------------------
sourceName := $(basename $(SOURCE))


# Define user directories and files --------------------------------------------
userLibDir      := $(ARDUINO_DIR)/libraries
userLibTemplDir := $(ARDUINO_DIR)/libraryTemplateClasses


# Define arduino directories and files -----------------------------------------
arduinoJavaDir      := $(ARDUINO_APP)/Contents/Resources/Java
arduinoCoreDir      := $(arduinoJavaDir)/hardware/arduino/cores/arduino
arduinoVariantsDir  := $(arduinoJavaDir)/hardware/arduino/variants
arduinoLibDir       := $(arduinoJavaDir)/libraries
arduinoBoardsFile   := $(arduinoJavaDir)/hardware/arduino/boards.txt
arduinoStaticLibDir := $(arduinoJavaDir)/arduinoLib
arduinoObjDirName   := arduinoObjFiles


# Define AVR directories and files ---------------------------------------------
AVRDir      := $(arduinoJavaDir)/hardware/tools/avr
AVRBin      := $(AVRDir)/bin
AVRLib      := $(AVRDir)/avr-4/lib
AVRDUDEConf := $(AVRDir)/etc/avrdude.conf


# Define non-implicit rule program variables -----------------------------------
AVRDUDE    := $(AVRBin)/avrdude
AVRObjCopy := $(AVRBin)/avr-objcopy


# Define implicit rule program variables  --------------------------------------
CC  := $(AVRBin)/avr-gcc
CPP := $(AVRBin)/avr-g++
AR  := $(AVRBin)/avr-ar
LD  := $(AVRBin)/avr-gcc


# Get board parameters  --------------------------------------------------------
mcu     := $(shell grep $(BOARD).build.mcu $(arduinoBoardsFile) | sed 's/$(BOARD).build.mcu=//')
cpu     := $(shell grep $(BOARD).build.f_cpu $(arduinoBoardsFile) | sed 's/$(BOARD).build.f_cpu=//')
variant := $(shell grep $(BOARD).build.variant $(arduinoBoardsFile) | sed 's/$(BOARD).build.variant=//')
baud    := $(shell grep $(BOARD).upload.speed $(arduinoBoardsFile) | sed 's/$(BOARD).upload.speed=//')
progr   := $(shell grep $(BOARD).upload.protocol $(arduinoBoardsFile) | sed 's/$(BOARD).upload.protocol=//')


# Define implicit rule option variables  ---------------------------------------
CFLAGS   := -DF_CPU=$(cpu) \
			-mmcu=$(mcu) \
			-Os \
			-fno-exceptions -ffunction-sections -fdata-sections

CPPFLAGS := -DF_CPU=$(cpu) \
			-mmcu=$(mcu) \
			-Os \
			-fno-exceptions -ffunction-sections -fdata-sections
			
LDFLAGS := -mmcu=$(mcu) \
           -Wl,--gc-sections
           
# Define non-implicit rule option variables  -----------------------------------
AVRDUDEFLAGS := -C $(AVRDUDEConf) \
				-p $(mcu) \
				-c arduino \
				-P $(PORT) \
				-b $(baud) \
				-D
				
# Define includes for compiler  ------------------------------------------------
coreIncs     := -I$(arduinoCoreDir)
variantsIncs := -I$(arduinoVariantsDir)/$(variant)
libIncs      := $(shell find $(arduinoLibDir) \( -name examples -prune \) -o \( -type d \) -print | sed 's/^/-I/g')
VPATHIncs    := $(libIncs)
arduinoIncs  := $(coreIncs) $(variantsIncs) $(libIncs)

userLibIncs      := $(shell find $(userLibDir)  \! -name "*.svn" -d 1 \( -type d -or -type l \) -print | sed 's/^/-I/g')
userLibTemplIncs := $(shell find $(userLibTemplDir)  \! -name "*.svn" -d 1 \( -type d -or -type l \) -print | sed 's/^/-I/g')
userIncs         := $(userLibIncs) $(userLibTemplIncs)


# Define search path for prerequisites  ----------------------------------------
VPATH := $(shell echo $(VPATHIncs) | sed 's/-I//g')


# Define Arduino core object files ---------------------------------------------
coreCFiles   := $(shell find $(arduinoCoreDir) -name "*.c" -print)
coreCPPFiles := $(shell find $(arduinoCoreDir) -name "*.cpp" -print)
coreCObjs    := $(addprefix $(arduinoCoreDir)/../$(arduinoObjDirName)/,$(notdir $(coreCFiles:.c=.o)))
coreCPPObjs  := $(addprefix $(arduinoCoreDir)/../$(arduinoObjDirName)/,$(notdir $(coreCPPFiles:.cpp=.o)))
coreObjs     := $(coreCObjs) $(coreCPPObjs)


# Define Arduino library object files ------------------------------------------
libCFiles   := $(shell find $(arduinoLibDir) -name "*.c")
libCPPFiles := $(shell find $(arduinoLibDir) -name "*.cpp")
libFiles    := $(libCFiles) $(libCPPFiles)
libCObjs    := $(addprefix $(arduinoLibDir)/$(arduinoObjDirName)/,$(notdir $(libCFiles:.c=.o)))
libCPPObjs  := $(addprefix $(arduinoLibDir)/$(arduinoObjDirName)/,$(notdir $(libCPPFiles:.cpp=.o)))
libObjs     := $(libCObjs) $(libCPPObjs)


# Define all Arduino objects files ---------------------------------------------
arduinoObjs := $(coreObjs) $(libObjs)


# Define source dependencies ---------------------------------------------------
userSourceLibDepenH := $(shell echo $(filter-out %.cpp,$(filter-out $(sourceName).o: $(SOURCE),$(shell g++ $(userLibIncs) -M -MM $(SOURCE)))))
userSourceLibDepenO := $(subst .h,.o,$(userSourceLibDepenH))


# Define Phony targets ---------------------------------------------------------
.PHONY : all cleanAll clean compile libStatic debug


# Define targets ---------------------------------------------------------------
all : compile

cleanAll : clean
	@-rm -R $(arduinoStaticLibDir); \
	rm -R $(arduinoCoreDir)/../$(arduinoObjDirName); \
	rm -R $(arduinoLibDir)/$(arduinoObjDirName); \
	rm -R $(userLibDir)/*/*.o
	
clean :
	@-rm *.o *.elf *.hex
	
upload : compile
	$(AVRDUDE) $(AVRDUDEFLAGS) -U flash:w:$(sourceName).hex

compile : $(sourceName).hex

libStatic : $(arduinoStaticLibDir)/arduino.a


# Explicit pattern rules -------------------------------------------------------

# Edit this part to allow EEPROM to be programmed
$(sourceName).hex : $(sourceName).elf
	$(AVRObjCopy) -j .text -j .data -O ihex $? $@
	
$(sourceName).elf : $(sourceName).o $(userSourceLibDepenO) $(arduinoStaticLibDir)/arduino.a
	$(LD) $(LDFLAGS) -o $@ $(sourceName).o  $(userSourceLibDepenO) \
	$(arduinoStaticLibDir)/arduino.a $(AVRLib)/libm.a
	
$(sourceName).o : $(sourceName).cpp $(userSourceLibDepenH)
	$(CPP) -c $(arduinoIncs) $(userIncs) $(CPPFLAGS) $< -o $@
	
$(arduinoStaticLibDir)/arduino.a : $(arduinoObjs)
	@if [ ! -d $(arduinoStaticLibDir) ]; \
	then \
	    mkdir -p $(arduinoStaticLibDir); \
	fi
	@for iObj in $(arduinoObjs); \
	do \
	    $(AR) rcs $(arduinoStaticLibDir)/arduino.a $$iObj; \
	done


# Implicit pattern rules for files ----------------------------------------------
%.o : %.c %.h
	$(CC) $(arduinoIncs) $(CFLAGS) -c $< -o $@

%.o : %.cpp %.h
	@$(CPP) $(arduinoIncs) $(CPPFLAGS) -c $< -o $@
	
%.h : %.cpp

%.h : %.c


# Implicit pattern rules for Arduino core files ---------------------------------
$(arduinoCoreDir)/../$(arduinoObjDirName)/%.o : $(arduinoCoreDir)/%.c $(arduinoCoreDir)/%.h
	@if [ ! -d $(dir $@) ]; \
	then \
		mkdir -p $(dir $@); \
	fi
	$(CC) $(coreIncs) $(variantsIncs) $(CFLAGS) -c $< -o $@

$(arduinoCoreDir)/../$(arduinoObjDirName)/%.o : $(arduinoCoreDir)/%.c
	@if [ ! -d $(dir $@) ]; \
	then \
		mkdir -p $(dir $@); \
	fi
	@$(CC) $(coreIncs) $(variantsIncs) $(CFLAGS) -c $< -o $@
	
$(arduinoCoreDir)/../$(arduinoObjDirName)/%.o : $(arduinoCoreDir)/%.cpp $(arduinoCoreDir)/%.h
	@if [ ! -d $(dir $@) ]; \
	then \
		mkdir -p $(dir $@); \
	fi
	@$(CPP) $(coreIncs) $(variantsIncs) $(CPPFLAGS) -c $< -o $@

$(arduinoCoreDir)/../$(arduinoObjDirName)/%.o : $(arduinoCoreDir)/%.cpp
	@if [ ! -d $(dir $@) ]; \
	then \
		mkdir -p $(dir $@); \
	fi
	@$(CPP) $(coreIncs) $(variantsIncs) $(CPPFLAGS) -c $< -o $@


# Implicit pattern rules for Arduino library files ------------------------------
$(arduinoLibDir)/$(arduinoObjDirName)/%.o : %.c %.h
	@if [ ! -d $(dir $@) ]; \
	then \
		mkdir -p $(dir $@); \
	fi
	@$(CC) $(coreIncs) $(variantsIncs) $(libIncs) $(CFLAGS) -c $< -o $@

$(arduinoLibDir)/$(arduinoObjDirName)/%.o : %.c
	@if [ ! -d $(dir $@) ]; \
	then \
		mkdir -p $(dir $@); \
	fi
	@$(CC) $(coreIncs) $(variantsIncs) $(libIncs) $(CFLAGS) -c $< -o $@

$(arduinoLibDir)/$(arduinoObjDirName)/%.o : %.cpp %.h
	@if [ ! -d $(dir $@) ]; \
	then \
		mkdir -p $(dir $@); \
	fi
	@$(CPP) $(coreIncs) $(variantsIncs) $(libIncs) $(CPPFLAGS) -c $< -o $@

$(arduinoLibDir)/$(arduinoObjDirName)/%.o : %.cpp
	@if [ ! -d $(dir $@) ]; \
	then \
		mkdir -p $(dir $@); \
	fi
	@$(CPP) $(coreIncs) $(variantsIncs) $(libIncs) $(CPPFLAGS) -c $< -o $@


# Debug target ------------------------------------------------------------------
debug :
	@echo $(mcu)