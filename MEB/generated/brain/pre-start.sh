#!/bin/sh

# this script is a hook that is called right before the container is started with runc
# it is only called if it is in place, no error if file is missing
# PWD is /container/<name>/

