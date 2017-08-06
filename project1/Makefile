include sources.mk

#Defaults
CC = gcc
CFLAGS= -Wall -Werror -g -std=c99 -DPROJECT3  #Compile time switch for project

LDFLAGS= -O0 -Xlinker -Map=project3.map  #linker generates .map file


ifeq ($(PLATFORM), HOST)
  CC=gcc
  SRCS+= $(SRCS_PATH)/main.c
	CFLAGS+= -DVERBOSE
endif

ifeq ($(PLATFORM),BBB)
     CC=arm-linux-gnueabihf-gcc
     SRCS+= $(SRCS_PATH)/main.c
		 CFLAGS= -Wall  \
		         -Werror \
						 -g      \
						 -std=c99 \
						 -DVERBOSE \
						 -DPROJECT3 \
						 -DVERBOSE
endif

ifeq ($(PLATFORM), KL25Z)
     CC=arm-none-eabi-gcc
     CFLAGS= -Wall    \
		 				 -Werror  \
						 -g       \
						 -std=c99 \
						 -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -mfpu=fpv4-sp-d16 \
						 --specs=nosys.specs \
						 -DPROJECT2
     LDFLAGS= -O0 \
		          -Xlinker -Map=project1.map  \
							-T "./platform/MKL25Z128xxx4_flash.ld"
     SRCS+= $(SRCS_PATH)/system_MKL25Z4.c $(SRCS_PATH)/startup_MKL25Z4.S
		 SRCS+= $(SRCS_PATH)/uart.c
endif

$(TARGET) : $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

$(TEST) : $(OBJS)
	cc -std=c99 -Wall -Werror -g -O0

%.o: %.c %.S
	$(CC) -c $(CFLAGS) $(LDFLAGS) -o $@ $^

%.s: %.c
	$(CC) -S $(CFLAGS) $(LDFLAGS) -o $@ $<

%.i: %.c
	$(CC) -E $(CFLAGS) $(LDFLAGS) -o $@ $<

%.d: %.c
	$(CC) -MM $(CFLAGS) $(LDFLAGS) -o $@ $<

.PHONY: compile-all asm-all ppr-all dep-all build clean unit_tests

asm-dump: project1.elf
	objdump -SD $< > projec1.dump


all : $(OBJS)
asm-all     : $(ASMS)
#asm-dump    : $(ASM_DUMP)
ppr-all     : $(PPRS)
dep-all     : $(DEPS)
build       : $(TARGET)
unit_tests	: $(TEST)
clean       :
	rm -f $(OBJS) $(ASMS) $(PPRS) $(DEPS) $(OUTS) $(TARGET)
