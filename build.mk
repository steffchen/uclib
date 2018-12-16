
CFLAGS += -I ${UCLIB}

LDFLAGS += -Wl,-Map=$(TARGET).map -L ${UCLIB} -T common.ld

%.elf: $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^
	$(SIZE) $@

%.bin: %.elf
	$(OBJCOPY) -O binary -R .eeprom $< $@

all: $(TARGET).bin

clean:
	rm -f $(OBJS)
	rm -f *.bin *.elf *.map
