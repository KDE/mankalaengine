#=============================================================================
# SPDX-FileCopyrightText: 2024 João Gouveia <jtalonegouveia@gmail.com>
#
# SPDX-License-Identifier: GPL-3.0-or-later
#=============================================================================

find_package(Doxygen)
if (DOXYGEN_FOUND)
    set(DOXYGEN_IN ${CMAKE_SOURCE_DIR}/docs/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

    add_custom_target(docs ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
else (DOXYGEN_FOUND)
    message("Building the docs requires Doxygen installed")
endif (DOXYGEN_FOUND)
