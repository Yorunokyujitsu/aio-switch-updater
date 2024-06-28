#!/usr/bin/env bash

cp ASAP-Updater.elf release-ASAP-Updater.elf

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
cd $DIR
rm -r switch/ASAP-Updater/
mkdir -p switch/ASAP-Updater/
cp ASAP-Updater.nro switch/ASAP-Updater/
#VERSION=$(grep "APP_VERSION :=" Makefile | cut -d' ' -f4)
#cp aiosu-forwarder/aiosu-forwarder.nro switch/ASAP-Updater/ASAP-Updater-v$VERSION.nro
zip -FSr ASAP-Updater.zip switch/