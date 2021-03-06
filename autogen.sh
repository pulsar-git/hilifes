#!/bin/sh

export WANT_AUTOMAKE='1.7'
export WANT_AUTOCONF_2_5=1

libtoolize --force && aclocal -I scripts/m4 $ACLOCAL_FLAGS && autoheader && automake --include-deps --add-missing --foreign && autoconf 
