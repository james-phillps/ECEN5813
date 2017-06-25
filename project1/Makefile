include sources.mk

#Defaults
CC = gcc
CFLAGS= -Wall    \  #Enable all warning messages
        -Werror  \  #Treat all warnings as errors
				-g       \	#General debug information in executable
				-std=c99 \  #Defines ANSI standard
				-DVERBOSE \ #Compile time switch for debugger
				-DPROJECT1 \ #Compile time switch for project
LDFLAGS= -O0     \  #Optimization level
         -Xlinker \ #Pass following argument as option to linker
				 -Map = project1.map  #linker generates .map file


ifeq ($(PLATFORM), HOST)
  CC=gcc
	CPPFLAGS= -E   \  #Only run the preprocessor
	          -o      #Output to file
endif

ifeq ($(PLATFORM),BBB)
     CC=arm-linux-gnueabihf-gcc
		 CFLAGS= -Wall  \
		         -Werror \
						 -g      \
						 -std=c99 \
						 -DVERBOSE \
						 -DPROJECT1
endif

ifeq ($(PLATFORM), KL25Z)
     CC=arm-none-eabi-gcc
		 CFLAGS= -Wall    \
		         -Werror  \
						 -g       \
						 -std=c99 \
						 -DPROJECT1 \
						 -mcpu=cortex-m0plus \ #Specifies name of tgt ARM processor
						 -mthumb \  #Use Thumb instruction set
						 -march=armv6 \ #Specifies tgt ARM architecture, affects asm instructions
						 -mfloat-abi=soft \ #Which floating point ABI: soft, softfp, hard
						 -mfpu=fpv4-sp-d16 \
						 --specs=nosys.specs
     LDFLAGS= -O0 /
		          -Xlinker -Map=project1.map \
							-T "MKL25Z128xxx_flash.ld"
endif

.PHONY: compile-all #Compile all objects, but do not link (Use -c option)
compile-all:
	$(CC) -c $(CFLAGS) $(LDFLAGS)
	#Actually put this at top so it's the first Target

.PHONY: build  #Compile all object files and link into final executable
build: #Add dependencies
	#Add command

.PHONY: clean  #Remove compiled objects, preprocessed, assembly, executable, and build output files
clean: #Add dependencies
	#Add command

%.i: %.c ../include/common/%.h
	$(CC) -E $(CFLAGS) $(LDFLAGS) -o $@ $<

%.asm: %.s ../include/common/%.h
	$(CC) -S $(CFLAGS) $(LDFLAGS) -o $@ $<

%.o: %.c ../include/common/%.h
	$(CC) -c $(CFLAGS) $(LDFLAGS) -o $@ $<
