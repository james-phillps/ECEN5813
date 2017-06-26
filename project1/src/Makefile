include sources.mk

#Defaults
CC = gcc
CFLAGS= -Wall -Werror -g -std=c99 -DVERBOSE -DPROJECT1  #Compile time switch for project

LDFLAGS= -O0 -Xlinker -Map=project1.map  #linker generates .map file


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
						 -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -mfpu=fpv4-sp-d16 \
						 --specs=nosys.specs
     LDFLAGS= -O0 \
		          -Xlinker -Map=project1.map  \
							-T "../platform/MKL25Z128xxx4_flash.ld"
     SRCS= \
		 ./main.c \
		 ./conversion.c \
		 ./memory.c \
		 ./project1.c \
		 ./debug.c \
		 ./system_MKL25Z4.c \
		 ./startup_MKL25Z4.S
endif

$(TARGET) : $(OBJS) $(OBJS_A)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

%.o: %.c %.S
	$(CC) -c $(CFLAGS) $(LDFLAGS) -o $@ $^

%.s: %.c
	$(CC) -S $(CFLAGS) $(LDFLAGS) -o $@ $<

%.i: %.c
	$(CC) -E $(CFLAGS) $(LDFLAGS) -o $@ $<

%.d: %.c
	$(CC) -MM $(CFLAGS) $(LDFLAGS) -o $@ $<

.PHONY: compile-all asm-all ppr-all dep-all build clean

compile-all : $(OBJS)
asm-all     : $(ASMS)
ppr-all     : $(PPRS)
dep-all     : $(DEPS)
build       : $(TARGET)
clean       :
	rm -f $(OBJS) $(ASMS) $(PPRS) $(DEPS) $(TARGET)
