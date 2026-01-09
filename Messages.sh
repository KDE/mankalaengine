#!/bin/sh
# SPDX-FileCopyrightText: 2025 Srisharan V S <srisharan.psgtech@gmail.com>
# SPDX-License-Identifier: GPL-3.0-or-later

# Extract translatable strings from all .cpp and .h files in src/ and include/
# and generate a .pot file for the MankalaEngine project.
$XGETTEXT `find . -name \*.cpp -o -name \*.h` -o $podir/mankalaengine.pot
