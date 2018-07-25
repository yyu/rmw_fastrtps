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
#include <utility>

#include "fastrtps/publisher/Publisher.h"
#include "fastrtps/publisher/PublisherListener.h"

#include "rmw/rmw.h"

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
  explicit PubListener(CustomPublisherInfo * info)
  : conditionMutex_(nullptr), conditionVariable_(nullptr)
  {
    // Field is not used right now
    (void)info;
  }

  void
  onPublicationMatched(
    eprosima::fastrtps::Publisher * pub,
    eprosima::fastrtps::rtps::MatchingInfo & info)
  {
    (void)pub;
    (void)info;
  }

  void
  attachCondition(std::mutex * conditionMutex, std::condition_variable * conditionVariable)
  {
    std::lock_guard<std::mutex> lock(internalMutex_);
    conditionMutex_ = conditionMutex;
    conditionVariable_ = conditionVariable;
  }

  void
  detachCondition()
  {
    std::lock_guard<std::mutex> lock(internalMutex_);
    conditionMutex_ = nullptr;
    conditionVariable_ = nullptr;
  }

private:
  std::mutex internalMutex_;
  std::mutex * conditionMutex_;
  std::condition_variable * conditionVariable_;
};

#endif  // RMW_FASTRTPS_CPP__CUSTOM_PUBLISHER_INFO_HPP_
