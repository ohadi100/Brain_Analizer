#!/bin/sh

# this script is a hook that is called after the container did stop and runc did terminate
# it is only called if it is in place, no error if file is missing
# PWD is /container/<name>/

