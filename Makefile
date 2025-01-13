SYSTEMC_HOME    = /home/root/lib/systemc-2.3.3
TARGET_ARCH     = linux64

SYSTEMC_INC_DIR = $(SYSTEMC_HOME)/include
SYSTEMC_LIB_DIR = $(SYSTEMC_HOME)/lib-$(TARGET_ARCH)

FLAGS           = -g -Wall -pedantic -Wno-long-long \
                 -DSC_INCLUDE_DYNAMIC_PROCESSES -fpermissive \
                 -I $(SYSTEMC_INC_DIR)
LDFLAGS         = -L $(SYSTEMC_LIB_DIR) -lsystemc -lm

SRCS = src/**
OBJS = $(SRCS:.cpp=.o)
	
main:
	g++ -std=c++11 -o model $(LDFLAGS) $(FLAGS) $(SRCS)

