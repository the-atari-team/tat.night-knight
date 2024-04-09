#!/bin/bash

# Generator, um die @HUFFMAN_DECODE_II Funktion als includierbare Datei bereitzustellen
# erwartet als Parameter die Label Datei aus dem atasm Assembler
# in dieser Datei liegen die Daten falsch herum
# Der Art: Adresse (ohne $ Prefix) und dessen Name

ATASM_LABEL_FILE=$1
cat ${ATASM_LABEL_FILE} | grep '@HUFFMAN_DECODE_II' | awk '{print $2 "=$" $1;}'
