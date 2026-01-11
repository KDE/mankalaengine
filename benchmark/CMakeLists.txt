#=============================================================================
# SPDX-FileCopyrightText: 2024 João Gouveia <jtalonegouveia@gmail.com>
#
# SPDX-License-Identifier: GPL-3.0-or-later
#=============================================================================

add_executable(benchmark benchmark.cpp)
target_link_libraries(benchmark PRIVATE MankalaEngine)

target_include_directories(benchmark PUBLIC ../src)
ecm_mark_nongui_executable(benchmark)
