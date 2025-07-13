#=============================================================================
# SPDX-FileCopyrightText: 2024 João Gouveia <jtalonegouveia@gmail.com>
#
# SPDX-License-Identifier: GPL-3.0-or-later
#=============================================================================

include(ECMAddTests)
file(GLOB_RECURSE TEST_FILES Test*.cpp)
ecm_add_tests(${TEST_FILES} LINK_LIBRARIES MankalaEngine Qt6::Test)
