#!/bin/bash

# This is a simple download helper script
# to initialise the whole build environment
# to get
# xldir.jar
# xl-packer.jar
# wnf-compiler.jar

# check for atari800 emulator
# check for atasm assembler

set -e

cd $(dirname $0)

PWD=$(pwd)

NEEDS=0

echo "This script initialise the wnf compiler environment."
echo

CURL_OPTS="-k"
mkdir -p compiler/bin

# check if we found xldir
if [[ -z "$(which xldir)" ]]; then
  echo "No xldir tool found, get from github.com."
  curl $CURL_OPTS -L -o compiler/bin/xldir.jar "https://github.com/the-atari-team/lla.xldir.disktool/releases/download/latest/xldir.jar"

  cat >compiler/bin/xldir <<__EOF__
#!/bin/bash
java -jar $PWD/compiler/bin/xldir.jar \$@
__EOF__
  chmod +x compiler/bin/xldir
else
  echo "Found xldir tool in \$PATH."
fi


# check if we found xl-packer
if [[ -z "$(which xl-packer)" ]]; then
  echo "No xl-packer tool found, get from github.com."
  curl $CURL_OPTS -L -o compiler/bin/xl-packer.jar "https://github.com/the-atari-team/tat.packer/releases/download/latest/xl-packer.jar"

  cat >compiler/bin/xl-packer <<__EOF__
#!/bin/bash
java -jar $PWD/compiler/bin/xl-packer.jar \$@
__EOF__
  chmod +x compiler/bin/xl-packer
else
  echo "Found xl-packer tool in \$PATH."
fi


# check if we found wnfc
if [[ -z "$(which wnfc)" ]]; then
  echo "No wnf compiler found, get from github.com."
  curl $CURL_OPTS -L -o compiler/bin/wnf-compiler.jar "https://github.com/the-atari-team/wnf.compiler/releases/download/latest/wnf-compiler.jar"

  cat >compiler/bin/wnfc <<__EOF__
#!/bin/bash
java -jar $PWD/compiler/bin/wnf-compiler.jar \$@
__EOF__
  chmod +x compiler/bin/wnfc
else
  echo "Found wnfc in \$PATH."
fi

if [[ -z "$(which atari800)" ]]; then
  echo "Please install the atari800 emulator!"
  echo "  Also make it available on command line."
  NEEDS=$((NEEDS+1))
else
  echo "Found atari800 in \$PATH."
fi

if [[ -z "$(which atasm)" ]]; then
  echo "Please install the atasm assembler!"
  echo "  Also make it available on command line."
else
  echo "Found atasm assembler in \$PATH."

  VERSION=$(atasm --version 2>&1 | awk '{print $2}')
  MAJOR=${VERSION%%.*}
  MINOR=${VERSION##*.}
  if [[ $MAJOR -eq 1 ]]; then
      if [[ $MINOR -lt 23 ]]; then
          echo "We need at least version 1.23 of atasm assembler!"
          NEEDS=$((NEEDS+1))
      else
          echo "Found atasm assembler in version: $MAJOR.$MINOR"
      fi
  fi 
fi

if [[ ! -e ../firmware/ATARIXL.ROM ]]; then
  echo "Please copy the ATARIXL.ROM firmware to ../firmware directory."
  NEEDS=$((NEEDS+1))
else
  echo "Found ATARIXL.ROM firmware file."
fi

if [[ "$PATH" =~ .*compiler/bin.* ]]; then
  echo "Found the 'compiler/bin' directory in \$PATH."
else
  echo "Add the 'compiler/bin' to your PATH env-variable."
  echo "Add this to your .bash script 'export PATH=\$PATH:\$(pwd)/compiler/bin'"
fi

echo
echo "Problems found: $NEEDS"
echo

if [[ $NEEDS -eq 0 ]]; then
    echo "No more problems found, now call 'make'"
else
    echo "There are more problems, please read above"
fi
