
OUTPUT_FORMAT("elf32-avr")
OUTPUT_ARCH(avr:5)

MEMORY
{
	text (rx) : ORIGIN = 0x00000000, LENGTH = 32K
	data (rw!x) : ORIGIN = 0x00800100, LENGTH = 2K + 512
}

SECTIONS
{
	.text : {
		*(.vectors)
		*(.init0)
		*(.init2)
		*(.init4)
		*(.init9)
		*(.text)
		*(.text.*)
		*(.fini0)
	} > text

	.data : {
		PROVIDE(__data_start = .);

		/* usb configuration descriptor 0 */
		__usb_conf0_start = .;
		*(.data.usb_conf0)
		*(.data.usb_conf0.*)
		PROVIDE(__usb_conf0_size = . - __usb_conf0_start);

		*(.data)
		*(.data.*)

		*(.rodata)
		*(.rodata.*)
		PROVIDE(__data_end = .);
	} > data AT > text

	__data_load_start = LOADADDR(.data);

	.bss ALIGN(2) : {
		PROVIDE(__bss_start = .);
		*(.bss)
		*(.bss.*)
		*(COMMON)
		PROVIDE(__bss_end = .);
	} > data

	.noinit : {
		*(.noinit)
		*(.noinit.*)
		PROVIDE(__heap_start = .);
	} > data
}
