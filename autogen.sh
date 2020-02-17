#!/bin/sh

# Copyright (c) 2020 Raytheon BBN Technologies Corp.
# See LICENSE.txt for details.

cd "${0%/*}" || exit 1
exec autoreconf -fviW all
