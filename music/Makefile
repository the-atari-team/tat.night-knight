CC=wnfc
ASM=atasm
PACKER=xl-packer

OS_NAME = $(OSNAME)
ifeq ("${OS_NAME}", "Linux")
  ALTIRRA=wine /home/lars/.wine/drive_c/atarixl.software/AtariXL_400/Altirra-410b27.exe
else
  ALTIRRA=Altirra.exe
endif

ATARI800_OPTIONS='-kbdjoy0'

FIRMWARE=../../firmware
COMPILER=../../compiler

WNFC_OPTIONS='-O' 2 '-smallHeapPtr'

.PHONY: copy_turbobasic_files prepare_atari clean all prepare basic_tests info

# You need to give the "PROGRAM name" name out of wnf file here, add .65o
GAME_OBJ_FILES=\
PLYAUDIO.65o

INCLUDES= \

ADDITIONALS=\
.os.txt

all: $(INCLUDES) $(GAME_OBJ_FILES) game_disk

clean::
	rm -f .wnffiles.txt
	rm -f $(ADDITIONALS) $(GAME_OBJ_FILES) $(INCLUDES)
	rm -f *.COM *.ASM *.ASM.inc *.65o .insert.txt *.lab *.log
	rm -f PLYAUDIO.lst
	rm -f GAME.lab
	rm -f GAME.log
	rm -f PLYAUDIO.ASM PLYAUDIO.log PLYAUDIO.lst

clean::
	rm -f start-game.atr start-test.atr
	rm -f starter17.atr
	rm -f editor.atr

PLYAUDIO.65o: play-audio.wnf $(INCLUDES) night-knight-audio.INC HEXEN.INC NOTEN.INC
	$(CC) $< $(WNFC_OPTIONS) -I $(COMPILER)
	$(ASM) -ha -s $(@:.65o=.ASM) -g$(@:.65o=.lst) -I$(COMPILER) -l$(@:.65o=.lab) >$(@:.65o=.log)
	cp $@ $(@:.65o=.COM)

AUDIOPLY.INC: ../audio-play.wnf
	$(CC) $< $(WNFC_OPTIONS) -I $(COMPILER)


prepare_game: prepare
# Dann das Spiel selbst
#	echo "PACMAN.COM -> AUTORUN.SYS" >.wnffiles.txt
	touch .wnffiles.txt
	echo "PLYAUDIO.COM -> AUTORUN.SYS" >>.insert.txt

prepare_last:
	cat .wnffiles.txt >>.insert.txt
	echo "stop" >>.wnffiles.txt
#	ls -1 *.COM >>.insert.txt
#	ls -1 PLAYS*.DAT >>.insert.txt
#	ls -1 LEVEL*.DAT >>.insert.txt
	echo ".wnffiles.txt -> WNFFILES.TXT" >>.insert.txt

game_disk: prepare_game prepare_last
	xldir $(COMPILER)/starter17.atr insert .insert.txt start-game.atr

atari_game: game_disk
	atari800 \
    -hreadwrite \
    -H2 /tmp/atari \
    -xlxe_rom $(FIRMWARE)/ATARIXL.ROM \
    -xl -xl-rev 2 \
    -pal -showspeed -nobasic \
    -windowed -win-width 682 -win-height 482 \
    -refresh 2 \
    -vsync -video-accel		 \
    ${ATARI800_OPTIONS} \
   start-game.atr

# Start Altirra with debug and stop at start address
# /portable searchs for an Altirra.ini
debug: $(INCLUDES) $(GAME_OBJ_FILES) game_disk
	$(ALTIRRA) \
	/portable \
	/debug \
	/debugcmd: ".sourcemode on" \
	/debugcmd: ".loadsym PLYAUDIO.lst" \
	/debugcmd: ".loadsym PLYAUDIO.lab" \
	/debugcmd: "bp 4000" \
	/disk "start-game.atr"


prepare:
	rm -f .wnffiles.txt
	rm -f .insert.txt
	echo ".os.txt -> OS.TXT" >>.insert.txt

start: $(INCLUDES) $(GAME_OBJ_FILES) atari_game

help:
	@echo "Makefile for the Atari 8bit game Pacman"
	@echo "usage:"
	@echo "make             - to create the whole game disk"
	@echo "make clean       - remove all build files"
	@echo "make start       - start game in atari800 emulator"
	@echo "make help        - show this list"
