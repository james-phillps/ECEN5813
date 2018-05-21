###This file is for use of the university of Colorado at Boulder Embedded Systems Engineering Professional Masters Program.


###Class:  ECEN5813 - Embedded Software Essentials
###Current Year: 2017
###Current Semester: Summer

**Repo Contents**
This repo contains the appropriate files for ECEN5813. The goal of ECEN5813 was
to develop firmware that could be cross-compiled to three different platforms:
the Freescale KL25Z, the BeagleBone Black, and the host PC. Cross compilation
can be selected at compile time using compile time switches in the makefile.

There were three projects in ECEN5813.

Project 1 implements basic memory manipulation functions, number to ASCII
conversion routines, printing debug messages with printf only when on the host
platform, and creation of a makefile to implement compile time switches so the
same source code successfully compiles and executes on all three platforms. The
project1.c file was provided by Instructor Fosdick to test all the required
functions.

Project 2 added the ability to transmit and receive messages over the UART on
the KL25Z, circular transmit and receive buffers, and add some processing
functions to analyze the content of messages received over the UART. The project
demo consisted of received an unknown string of text and printing the number of
alphabetic, numerical, punctuation, and miscellaneous characters in the string.

Project 3 was implementing a data logger, control/communication with a Nordic
radio module over a SPI peripheral, and implementing the DMA on the KL25Z.
Because this course was in the summer session, 16 weeks of content were
compressed into 10 weeks. This project was overloaded. Nordic.h is a header file
containing address and command definitions for the Nordic radio module. Project
3 also implemented the Systick peripheral on the KL25Z to run timing profiles on
the memory routines to compare the speed of using the DMA verses using the CPU
to move bytes in memory.
