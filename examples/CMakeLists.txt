#=============================================================================
# SPDX-FileCopyrightText: 2024 João Gouveia <jtalonegouveia@gmail.com>
# SPDX-FileCopyrightText: 2025 Srisharan V S <srisharan.psgtech@gmail.com>
#
# SPDX-License-Identifier: GPL-3.0-or-later
#=============================================================================

file(GLOB_RECURSE EXAMPLES *.cpp)
if(BUILD_EXAMPLES)
    foreach(example_src ${EXAMPLES})
        get_filename_component(example_name ${example_src} NAME_WE)

        add_executable(${example_name} ${example_src})
        target_link_libraries(${example_name} PRIVATE MankalaEngine)

        target_include_directories(${example_name} PUBLIC ../src)
        ecm_mark_nongui_executable(${example_name})
        install(TARGETS ${example_name} RUNTIME DESTINATION bin)
    endforeach()
endif()
