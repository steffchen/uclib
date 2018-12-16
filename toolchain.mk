
CC := $(CROSS_PREFIX)gcc
LD := $(CROSS_PREFIX)gcc
OBJCOPY := $(CROSS_PREFIX)objcopy
SIZE := $(CROSS_PREFIX)size

include ${UCLIB}/build.mk
