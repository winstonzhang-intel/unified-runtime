# Copyright (C) 2024 Intel Corporation
# Part of the Unified-Runtime Project, under the Apache License v2.0 with LLVM Exceptions.
# See LICENSE.TXT
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

function(add_unittest name)
    set(target test-adapter-${name})
    add_adapter_test(${name}
        FIXTURE DEVICES
        ENVIRONMENT
            "UR_ADAPTERS_FORCE_LOAD=\"$<TARGET_FILE:ur_adapter_level_zero>\""
            "UR_L0_USE_QUEUE_V2=1"
        SOURCES
            ${PROJECT_SOURCE_DIR}/source/adapters/level_zero/common.cpp
            ${PROJECT_SOURCE_DIR}/source/adapters/level_zero/ur_level_zero.cpp
            ${ARGN})

    target_include_directories(${target} PUBLIC
        ${PROJECT_SOURCE_DIR}/source
        ${PROJECT_SOURCE_DIR}/source/adapters/level_zero
        ${PROJECT_SOURCE_DIR}/source/adapters/level_zero/v2
        LevelZeroLoader-Headers)

    target_link_libraries(${target} PRIVATE
        ${PROJECT_NAME}::common
        LevelZeroLoader
        LevelZeroLoader-Headers
    )
endfunction()

add_unittest(level_zero_command_list_cache
        command_list_cache_test.cpp
        ${PROJECT_SOURCE_DIR}/source/adapters/level_zero/v2/command_list_cache.cpp
)

add_unittest(level_zero_event_pool
        event_pool_test.cpp
        ${PROJECT_SOURCE_DIR}/source/adapters/level_zero/v2/event_pool.cpp
        ${PROJECT_SOURCE_DIR}/source/adapters/level_zero/v2/event_pool_cache.cpp
        ${PROJECT_SOURCE_DIR}/source/adapters/level_zero/v2/event_provider_normal.cpp
        ${PROJECT_SOURCE_DIR}/source/adapters/level_zero/v2/event_provider_counter.cpp
        ${PROJECT_SOURCE_DIR}/source/adapters/level_zero/v2/event.cpp
)
