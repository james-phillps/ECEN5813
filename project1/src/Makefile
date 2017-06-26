include sources.mk

#Defaults
CC = gcc
CFLAGS= -Wall -Werror -g -std=c99 -DVERBOSE -DPROJECT1  #Compile time switch for project

LDFLAGS= -O0 -Xlinker -Map = project1.map  #linker generates .map file


ifeq ($(PLATFORM), HOST)
  CC=gcc
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
     LDFLAGS= -O0 \
		          -Xlinker -Map=project1.map \
							-T "MKL25Z128xxx_flash.ld"
endif

$(TARGET) : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

%.s: %.c
	$(CC) -S $(CFLAGS) -o $@ $<

%.i: %.c
	$(CC) -E $(CFLAGS) -o $@ $<

%.d: %.c
	$(CC) -MM $(CFLAGS) -o $@ $<

.PHONY: compile-all asm-all ppr-all dep-all build clean

compile-all : $(OBJS)
asm-all     : $(ASMS)
ppr-all     : $(PPRS)
dep-all     : $(DEPS)
build       : $(TARGET)
clean       :
	rm -f $(OBJS) $(ASMS) $(PPRS) $(DEPS) $(TARGET)
