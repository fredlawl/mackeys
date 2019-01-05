#!/usr/bin/env bash

set -e

MODULE="mackeys"

make
sudo rmmod "$MODULE" &>/dev/null
sudo insmod "$MODULE.ko" &>/dev/null
