# Memory Map Night Knight 64k

* $00C0 - $00D3        Zeropage Addresses
* $00D4 - $00FF        compiler used Zeropage Addresses
* 
* $0100 '    loading...      ' 20 Bytes for loading
* $03c0 Displaylist for loading... Text stored in MACROS.INC, Font $BE00

* $3FD - $47f          Cassettenbuffer wird als Heap verwendet?

* $0580                simple 64k Routines
* $3D70 - 6 - ~$7ffa   ALL-PLAYFIELDS.DAT per incbin laden
*                      per MOVE wird es hinter das OS kopiert

* $0600                Night Knight Displaylist

* Options, Displaylists

* $0700 - $1c6c-1      DOS XL

* $1000 - $1800        Player Missile Grafik
* $1800 - $2000-1      Screen

* $1ba0                Game Screen
* $1D08                Title Screen
* $1F60                Score Text

* $2000 - $BE00-1      Night-Knight Game
* AKTUELLES ENDE: $B4c3

* $BE00 -              LOADING Font

// siehe playfield-data.INC
* $C000 - $C298-1      Castle-Font (night-knight-bernards-castle-font.wnf)
* $C298 - $C4b8        
* $C4B8 - $C800-1      Letter.inc 840 Bytes fuer Night Knight Image
* $C800 - $CA00-1      Title font (night-knight-title-font.wnf)
* $CB00                Castle 256 Zeichen, aus Castle-Font
* $CC00 - $D000-1      Night Knight Font ()

// $D000 - $D800-1     CUSTOM CHIPS ATARI

* $D800 - $FAB6        Komprimierte Leveldaten (80 Levels)
* $FAB7 - $FD42        Huffman Decoder ($2c7 bytes length)
*       - $FFF9        frei
