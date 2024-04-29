CC=wnfc
ASM=atasm
PACKER=xl-packer

OS_NAME = $(OSNAME)
ifeq ("${OS_NAME}", "Linux")
  ALTIRRA=wine /home/lars/.wine/drive_c/atarixl.software/AtariXL_400/Altirra-420.exe
else
  ALTIRRA=Altirra.exe
endif

# ATARI800_OPTIONS='-kbdjoy0'

FIRMWARE=../firmware
LIBRARY=library

WNFC_OPTIONS='-O' 3 '-smallHeapPtr'

.PHONY: prepare_atari clean all prepare info

# You need to give the "PROGRAM name" name out of wnf file here, add .65o
GAME_OBJ_FILES=\
NIGHT.65o

INCLUDES=\
ENEMY.INC \
SKELETON.INC \
DRACULA.INC \
ARCHER.INC \
KNIGHT.INC \
WERWOLF.INC \
WIZARD.INC \
DUDE.INC \
GHOST.INC \
CAT.INC \
SPRITES.INC \
TABLES.INC \
NIGHTFNT.INC \
TITLEFNT.INC \
CASTLFNT.INC \
CASTLE.INC \
SHOWSCOR.INC \
PLYFIELD.INC \
PLAYERM.INC \
LEVEL.INC \
ELEVATOR.INC \
LETTER.INC \
DESIGN.INC \
INTRO.INC \
PASSWORD.INC \
HASH.INC \
AUDIOPLY.INC


ADDITIONALS=\
 FONT0.DAT \
 ALL-PLAYFIELDS.DAT

all: $(ADDITIONALS) $(INCLUDES) $(GAME_OBJ_FILES) game_disk

info:
	@echo "OO  OO  OO         OO       OO         OO   OO         OO         OO       OO   "
	@echo "OOO OO             OO       OO         OO  OO                     OO       OO   "
	@echo "OOOOOO OOO   OOOOO OOOOO  OOOOOO       OO OO   OOOOO  OOO   OOOOO OOOOO  OOOOOO "
	@echo "OO OOO  OO  OO  OO OO  OO   OO         OOOO    OO  OO  OO  OO  OO OO  OO   OO   "
	@echo "OO  OO  OO  OO  OO OO  OO   OO         OO OO   OO  OO  OO  OO  OO OO  OO   OO   "
	@echo "OO  OO  OO   OOOOO OO  OO   OO         OO  OO  OO  OO  OO   OOOOO OO  OO   OO   "
	@echo "OO  OO OOOO     OO OO  OO    OOO       OO   OO OO  OO OOOO     OO OO  OO    OOO "
	@echo "            OOOOO                                          OOOOO"

clean:: info
	rm -f .wnffiles.txt
	rm -f $(ADDITIONALS) $(GAME_OBJ_FILES) $(INCLUDES)
	rm -f *.COM *.ASM *.65o .insert.txt *.lab *.log
	rm -f *.ASM.inc NIGHT.lst KNIGHTST.lst
	rm -f huffman-decode.lst

clean::
	rm -f night-knight-game.atr

NIGHT.65o: night-knight.wnf night-knight-displaylist.INC HIGHSCORE.INC $(INCLUDES) compress GAME-DLI.INC $(LIBRARY)/DRAWBLOCK.INC ALL-PLAYFIELDS.DAT
	$(CC) $< $(WNFC_OPTIONS) -showvariableusage -I $(LIBRARY)
	$(ASM) -ha -s $(@:.65o=.ASM) -g$(@:.65o=.lst) -l$(@:.65o=.lab) >$(@:.65o=.log)
	cp $@ $(@:.65o=.COM)

NIGHTFNT.INC: night-knight-font.wnf
	$(CC) $< -noheader $(WNFC_OPTIONS) -I $(LIBRARY)

ELEVATOR.INC: elevator.wnf
	$(CC) $< $(WNFC_OPTIONS) -I $(LIBRARY)

TABLES.INC: tables.wnf
	$(CC) $< -noheader $(WNFC_OPTIONS) -I $(LIBRARY)

PLAYERM.INC: playermissile.wnf
	$(CC) $< -noheader $(WNFC_OPTIONS) -I $(LIBRARY)

LEVEL.INC: level.wnf
	$(CC) $< $(WNFC_OPTIONS) -I $(LIBRARY)

INTRO.INC: night-knight-intro.wnf $(LIBRARY)/KEYCODE.INC password.wnf
	$(CC) $< $(WNFC_OPTIONS) -I $(LIBRARY)

HASH.INC: hash.wnf
	$(CC) $< $(WNFC_OPTIONS) -I $(LIBRARY)

DESIGN.INC: level-design.wnf
	$(CC) $< $(WNFC_OPTIONS) -I $(LIBRARY)

TITLEFNT.INC: night-knight-title-font.wnf
	$(CC) $< -noheader $(WNFC_OPTIONS) -I $(LIBRARY)

CASTLE.INC: night-knight-bernards-castle.wnf
	$(CC) $< -noheader $(WNFC_OPTIONS) -I $(LIBRARY)

CASTLFNT.INC: night-knight-bernards-castle-font.wnf
	$(CC) $< -noheader $(WNFC_OPTIONS) -I $(LIBRARY)

PLYFIELD.INC: playfield.wnf
	$(CC) $< $(WNFC_OPTIONS) -I $(LIBRARY)

ENEMY.INC: enemy.wnf
	$(CC) $< $(WNFC_OPTIONS) -I $(LIBRARY)

SKELETON.INC: enemy-skeleton.wnf
	$(CC) $< $(WNFC_OPTIONS) -I $(LIBRARY)

DRACULA.INC: enemy-dracula.wnf
	$(CC) $< $(WNFC_OPTIONS) -I $(LIBRARY)

ARCHER.INC: enemy-archer.wnf
	$(CC) $< $(WNFC_OPTIONS) -I $(LIBRARY)

KNIGHT.INC: enemy-dark-knight.wnf
	$(CC) $< $(WNFC_OPTIONS) -I $(LIBRARY)

WERWOLF.INC: enemy-werwolf.wnf
	$(CC) $< $(WNFC_OPTIONS) -I $(LIBRARY)

WIZARD.INC: enemy-wizard.wnf
	$(CC) $< $(WNFC_OPTIONS) -I $(LIBRARY)

GHOST.INC: enemy-ghost.wnf
	$(CC) $< $(WNFC_OPTIONS) -I $(LIBRARY)

CAT.INC: enemy-cat.wnf
	$(CC) $< $(WNFC_OPTIONS) -I $(LIBRARY)

DUDE.INC: dude.wnf
	$(CC) $< $(WNFC_OPTIONS) -I $(LIBRARY)

SPRITES.INC: all-sprites.wnf
	$(CC) $< $(WNFC_OPTIONS) -I $(LIBRARY)

FONT0.DAT: font0.INC NIGHTFNT.INC
	$(ASM) $< -o$@ >/dev/null
#	$(ASM) $(@:.65o=.ASM) >$(@:.65o=.log)

SHOWSCOR.INC: show-score.wnf
	$(CC) $< $(WNFC_OPTIONS) -I $(LIBRARY)

LETTER.INC: night-knight-schriftzug.wnf
	$(CC) $< -noheader $(WNFC_OPTIONS) -I $(LIBRARY)

AUDIOPLY.INC: audio-play.wnf
	$(CC) $< $(WNFC_OPTIONS) -I $(LIBRARY)

PASSWORD.INC: password.wnf
	$(CC) $< -noheader $(WNFC_OPTIONS) -I $(LIBRARY)


prepare_game: prepare
# Dann das Spiel selbst
	touch .wnffiles.txt
#	echo "NIGHT.COM -> AUTORUN.SYS" >.wnffiles.txt
	echo "NIGHT.COM -> AUTORUN" >.wnffiles.txt     # for udos
#	echo "NIGHT.COM -> NIGHT.COM" >>.insert.txt

prepare_last:
	cat .wnffiles.txt >>.insert.txt
	echo "stop" >>.wnffiles.txt
#	ls -1 *.COM >>.insert.txt
#	ls -1 PLAYS*.DAT >>.insert.txt
#	ls -1 LEVEL*.DAT >>.insert.txt
#	echo ".wnffiles.txt -> WNFFILES.TXT" >>.insert.txt

# .FORCE:

game_disk: prepare_game prepare_last
#	xldir $(LIBRARY)/dos-sd.atr insert .insert.txt start-game.atr
	xldir $(LIBRARY)/udos.atr insert .insert.txt night-knight-game.atr
#	xldir $(LIBRARY)/dos-2.5-ed.atr insert .insert.txt start-game.atr

atari_game: game_disk
	atari800 \
    -hreadwrite \
    -H2 /tmp/atari \
    -xl -xl-rev 2 \
		-xlxe_rom $(FIRMWARE)/ATARIXL.ROM \
    -pal -showspeed -nobasic \
    -windowed -win-width 682 -win-height 482 \
    -vsync -video-accel \
	-stereo \
	-refresh 2 \
    ${ATARI800_OPTIONS} \
   night-knight-game.atr

#    -xlxe_rom $(FIRMWARE)/xeOSvep1_HS.rom \
#    start-game.atr

#    -xlxe_rom $(FIRMWARE)/ATARIXL.ROM \

# Start Altirra with debug and stop at start address
# /portable searchs for an Altirra.ini
debug: $(INCLUDES) $(GAME_OBJ_FILES) game_disk
	$(ALTIRRA) \
	/portable: \
	/debug: \
	/debugcmd: ".sourcemode on" \
	/debugcmd: ".loadsym NIGHT.lst" \
	/debugcmd: ".loadsym NIGHT.lab" \
	/debugcmd: "bp 2000" \
	/disk: "night-knight-game.atr"

prepare:
	rm -f .wnffiles.txt
	rm -f .insert.txt
	echo ".os.txt -> OS.TXT" >>.insert.txt

n: $(INCLUDES) $(GAME_OBJ_FILES)

start: n atari_game

PLAYFIELDS=\
 PLAYSB0.DAT \
 PLAYSB1.DAT \
 PLAYSB2.DAT \
 PLAYS01.DAT \
 PLAYS02.DAT \
 PLAYS03.DAT \
 PLAYS04.DAT \
 PLAYS05.DAT \
 PLAYS06.DAT \
 PLAYS07.DAT \
 PLAYS08.DAT \
 PLAYS09.DAT \
 PLAYS10.DAT \
 PLAYS11.DAT \
 PLAYS12.DAT \
 PLAYS13.DAT \
 PLAYS14.DAT \
 PLAYS15.DAT \
 PLAYS16.DAT \
 PLAYS17.DAT \
 PLAYS18.DAT \
 PLAYS19.DAT \
 PLAYS20.DAT \
 PLAYS21.DAT \
 PLAYS22.DAT \
 PLAYS23.DAT \
 PLAYS24.DAT \
 PLAYS25.DAT \
 PLAYS26.DAT \
 PLAYS27.DAT \
 PLAYS28.DAT \
 PLAYS29.DAT \
 PLAYS30.DAT \
 PLAYS31.DAT \
 PLAYS32.DAT \
 PLAYS33.DAT \
 PLAYS34.DAT \
 PLAYS35.DAT \
 PLAYS36.DAT \
 PLAYS37.DAT \
 PLAYS38.DAT \
 PLAYS39.DAT \
 PLAYS40.DAT \
 PLAYS41.DAT \
 PLAYS42.DAT \
 PLAYS43.DAT \
 PLAYS44.DAT \
 PLAYS45.DAT \
 PLAYS46.DAT \
 PLAYS47.DAT \
 PLAYS48.DAT \
 PLAYS49.DAT \
 PLAYS50.DAT \
 PLAYS51.DAT \
 PLAYS52.DAT \
 PLAYS53.DAT \
 PLAYS54.DAT \
 PLAYS55.DAT \
 PLAYS56.DAT \
 PLAYS57.DAT \
 PLAYS58.DAT \
 PLAYS59.DAT \
 PLAYS60.DAT \
 PLAYS61.DAT \
 PLAYS62.DAT \
 PLAYS63.DAT \
 PLAYS64.DAT \
 PLAYS65.DAT \
 PLAYS66.DAT \
 PLAYS67.DAT \
 PLAYS68.DAT \
 PLAYS69.DAT \
 PLAYS70.DAT \
 PLAYS71.DAT \
 PLAYS72.DAT \
 PLAYS73.DAT \
 PLAYS74.DAT \
 PLAYS75.DAT \
 PLAYS76.DAT \
 PLAYS77.DAT \
 PLAYS78.DAT \
 PLAYS79.DAT \
 PLAYS80.DAT \
 PLAYS81.DAT


# .PHONY: $(PLAYFIELDS)

clean::
	rm -f COMPRESSED-PLAYFIELDS.INC COMPRESSED-PLAYFIELDS-2.INC


#DATA.65o: night-knight-data.wnf COMPRESSED-PLAYFIELDS.INC
#	$(CC) $< $(WNFC_OPTIONS) -showvariableusage -I $(LIBRARY)
#	$(ASM) -ha -s $(@:.65o=.ASM) -g$(@:.65o=.lst) -l$(@:.65o=.lab) >$(@:.65o=.log)
#	cp $@ $(@:.65o=.COM)

# compress all playfields
COMPRESSED-PLAYFIELDS.INC: $(PLAYFIELDS)
	$(PACKER) --usepairs --data -of $@ $(PLAYFIELDS)

#COMPRESSED-PLAYFIELDS-2.INC: $(PLAYFIELDS)
#	$(PACKER) --useblocks --data -of $@ $(PLAYFIELDS)

ALL-PLAYFIELDS.DAT: playfield-data.INC huffman-decode.INC COMPRESSED-PLAYFIELDS.INC CASTLFNT.INC CASTLE.INC LETTER.INC TITLEFNT.INC NIGHTFNT.INC
	$(ASM) -ha $< -g$(@:.DAT=.lst) -l$(@:.DAT=.lab) -o$@ >/dev/null
#	$(ASM) $(@:.65o=.ASM) -g$(@:.65o=.lst) >$(@:.65o=.log)
	./generate-huffman-decode-label.sh $(@:.DAT=.lab) >HUFFMAN_DECODE.lab

compress: COMPRESSED-PLAYFIELDS.INC $(PLAYFIELDS)


start: all atari_game

init:
	./get-everything.sh

help:
	@echo "Makefile for the Atari 8bit game Night Knight"
	@echo "usage:"
	@echo "make             - to create the whole game disk"
	@echo "make clean       - remove all build files"
	@echo "make start       - start game in atari800 emulator"
	@echo "make help        - show this list"
