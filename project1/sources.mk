SRCS_PATH = ./src

SRCS= \
$(SRCS_PATH)/main.c \
$(SRCS_PATH)/conversion.c \
$(SRCS_PATH)/memory.c \
$(SRCS_PATH)/project2.c \
$(SRCS_PATH)/circbuf.c \
$(SRCS_PATH)/LED.c


SRCS_INCLUDES = \
-I./include/common

THIRDY_PARTY_DIR = 3rd-party
CMOCKA_INCLUDE_DIR = $(THIRD_PARTY_DIR)/build-Debug/include
CMOCKA_LIBRARY = $(THIRD_PARTY_DIR)/build-Debug/lib/libcmocka.a

OBJS=$(SRCS:.c=.o)
ASMS=$(SRCS:.c=.s)
PPRS=$(SRCS:.c=.i)
DEPS=$(SRCS:.c=.d)
OUTS=$(SRCS:.c=.out)


TARGET=project2.elf
