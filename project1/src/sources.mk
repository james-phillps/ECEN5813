SRCS = \
./main.c \
./conversion.c \
./memory.c \
./project1.c \
./debug.c


SRCS_INCLUDES = \
-I../include/common

OBJS=$(SRCS:.c=.o)
ASMS=$(SRCS:.c=.s)
PPRS=$(SRCS:.c=.i)
DEPS=$(SRCS:.c=.d)


TARGET=project1.elf
