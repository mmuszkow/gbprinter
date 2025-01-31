ifndef GBDK_HOME
	GBDK_HOME = ../gbdk/
endif

LCC = $(GBDK_HOME)bin/lcc -Wa-l -Wl-m -Wl-j

BINS = print.gb

# GBDK_DEBUG = ON
ifdef GBDK_DEBUG
	LCCFLAGS += -debug -v
endif


all:	$(BINS)

compile.bat: Makefile
	@echo "REM Automatically generated from Makefile" > compile.bat
	@make -sn | sed y/\\//\\\\/ | sed s/mkdir\ -p\/mkdir\/ | grep -v make >> compile.bat

# Compile and link single file in one pass
%.gb: main.c printer.c pattern.c
	$(LCC) $(LCCFLAGS) -o $@ $^
	rgbfix --color-compatible --fix-spec lhg --non-japanese --mbc-type 0 --rom-version 2 --pad-value 0xFF --ram-size 0 --game-id "MUH" --title "PRINT" --overwrite $(BINS)

clean:
	rm -f *.o *.lst *.map *.gb *~ *.rel *.cdb *.ihx *.lnk *.sym *.asm *.noi *.rst

