//===--------- event_provider_normal.hpp - Level Zero Adapter -------------===//
//
// Copyright (C) 2024 Intel Corporation
//
// Part of the Unified-Runtime Project, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
#pragma once

#include <deque>
#include <memory>
#include <mutex>
#include <stack>

#include <unordered_map>
#include <ur/ur.hpp>
#include <ur_api.h>
#include <ze_api.h>

#include "../device.hpp"
#include "common.hpp"
#include "event.hpp"

namespace v2 {

enum queue_type {
  QUEUE_REGULAR,
  QUEUE_IMMEDIATE,
};

class provider_pool {
public:
  provider_pool(ur_context_handle_t, ur_device_handle_t, event_type,
                queue_type);
  ~provider_pool();

  event_borrowed allocate();
  size_t nfree() const;

private:
  // TODO: use a RAII wrapper for the pool handle
  ze_event_pool_handle_t pool;

  std::vector<ze_event_handle_t> freelist;
};

class provider_normal : public event_provider {
public:
  provider_normal(ur_context_handle_t, ur_device_handle_t, event_type,
                  queue_type);

  ~provider_normal() override;

  event_allocation allocate() override;
  ur_device_handle_t device() override;

private:
  event_type producedType;
  queue_type queueType;
  ur_context_handle_t urContext;
  ur_device_handle_t urDevice;

  std::unique_ptr<provider_pool> createProviderPool();
  std::vector<std::unique_ptr<provider_pool>> pools;
};

} // namespace v2
