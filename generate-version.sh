#!/bin/sh

set -e

if [ -d .git ] ; then
    version="$(git describe --dirty)"
elif [ -f version ] ; then
    version="$(cat version)"
else
    version="unknown"
fi

echo -e "#ifndef BABELD_VERSION\n#define BABELD_VERSION \"$version\"\n#endif"
