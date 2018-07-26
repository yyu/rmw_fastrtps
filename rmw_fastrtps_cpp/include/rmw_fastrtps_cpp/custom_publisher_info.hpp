// Copyright 2016 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef RMW_FASTRTPS_CPP__CUSTOM_PUBLISHER_INFO_HPP_
#define RMW_FASTRTPS_CPP__CUSTOM_PUBLISHER_INFO_HPP_

#include <atomic>
#include <condition_variable>
#include <mutex>
#include <set>
#include <utility>

#include "fastrtps/publisher/Publisher.h"
#include "fastrtps/publisher/PublisherListener.h"

#include "rcutils/logging_macros.h"

#include "rmw/rmw.h"
#include "rmw/error_handling.h"

class PubListener;

typedef struct CustomPublisherInfo
{
  eprosima::fastrtps::Publisher * publisher_;
  PubListener * listener_;
  void * type_support_;
  rmw_gid_t publisher_gid;
  const char * typesupport_identifier_;
} CustomPublisherInfo;


class PubListener : public eprosima::fastrtps::PublisherListener
{
public:
  explicit PubListener(CustomPublisherInfo * info):
    matched_guard_condition_(nullptr)
  {
    (void)info;
  }

  void
  onPublicationMatched(
    eprosima::fastrtps::Publisher * pub,
    eprosima::fastrtps::rtps::MatchingInfo & info)
  {
    (void) pub;
    std::lock_guard<std::mutex> lock(internalMutex_);
    auto guid = info.remoteEndpointGuid;

    if (eprosima::fastrtps::rtps::MATCHED_MATCHING == info.status) {
      matched_.insert(guid);
    } else if (eprosima::fastrtps::rtps::REMOVED_MATCHING == info.status) {
      matched_.erase(guid);
    }
    matched_count_ = matched_.size();

    if (matched_guard_condition_) {
      rmw_ret_t ret = rmw_trigger_guard_condition(matched_guard_condition_);
      if (ret != RMW_RET_OK) {
        RCUTILS_LOG_ERROR_NAMED(
          "rmw_fastrtps_cpp",
          "failed to trigger matched publisher guard condition: %s",
          rmw_get_error_string_safe())
      }
    }
  }

  void
  attachGuard(rmw_guard_condition_t * guard_condition)
  {
    std::lock_guard<std::mutex> lock(internalMutex_);
    matched_guard_condition_ = guard_condition;
  }

  void
  detachGuard()
  {
    std::lock_guard<std::mutex> lock(internalMutex_);
    matched_guard_condition_ = nullptr;
  }

  size_t
  numSubscribers()
  {
    return matched_count_;
  }

private:
  std::mutex internalMutex_;
  std::set<eprosima::fastrtps::rtps::GUID_t> matched_;
  std::atomic_size_t matched_count_;
  rmw_guard_condition_t * matched_guard_condition_;
};

#endif  // RMW_FASTRTPS_CPP__CUSTOM_PUBLISHER_INFO_HPP_
