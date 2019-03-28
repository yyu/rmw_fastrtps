// Copyright 2016-2018 Proyectos y Sistemas de Mantenimiento SL (eProsima).
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

#include <utility>
#include <string>

#include "rmw/allocators.h"
#include "rmw/error_handling.h"
#include "rmw/impl/cpp/macros.hpp"
#include "rmw/rmw.h"

#include "fastrtps/Domain.h"
#include "fastrtps/TopicDataType.h"
#include "fastrtps/participant/Participant.h"
#include "fastrtps/subscriber/Subscriber.h"

#include "qos.hpp"

#include "rmw_fastrtps_shared_cpp/rmw_common.hpp"
#include "rmw_fastrtps_shared_cpp/custom_client_info.hpp"
#include "rmw_fastrtps_shared_cpp/custom_publisher_info.hpp"
#include "rmw_fastrtps_shared_cpp/custom_service_info.hpp"
#include "rmw_fastrtps_shared_cpp/custom_subscriber_info.hpp"


namespace rmw_fastrtps_shared_cpp
{

rmw_ret_t
__rmw_publisher_event_init(
  const char * identifier,
  rmw_event_t * rmw_event,
  const rmw_publisher_t * publisher,
  const rmw_event_type_t event_type)
{
  RMW_CHECK_ARGUMENT_FOR_NULL(publisher, RMW_RET_INVALID_ARGUMENT);
  RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
    publisher,
    publisher->implementation_identifier,
    identifier,
    return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);
  RMW_CHECK_ARGUMENT_FOR_NULL(rmw_event, RMW_RET_INVALID_ARGUMENT);
  if (nullptr != rmw_event->implementation_identifier) {
    RMW_SET_ERROR_MSG("expected zero-initialized event");
    return RMW_RET_INVALID_ARGUMENT;
  }

  rmw_event->implementation_identifier = publisher->implementation_identifier;
  rmw_event->data = static_cast<CustomEventInfo *>(publisher->data);
  rmw_event->event_type = event_type;

  return RMW_RET_OK;
}

rmw_ret_t
__rmw_subscription_event_init(
  const char * identifier,
  rmw_event_t * rmw_event,
  const rmw_subscription_t * subscription,
  const rmw_event_type_t event_type)
{
  RMW_CHECK_ARGUMENT_FOR_NULL(subscription, RMW_RET_INVALID_ARGUMENT);
  RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
    subscription,
    subscription->implementation_identifier,
    identifier,
    return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);
  RMW_CHECK_ARGUMENT_FOR_NULL(rmw_event, RMW_RET_INVALID_ARGUMENT);
  if (nullptr != rmw_event->implementation_identifier) {
    RMW_SET_ERROR_MSG("expected zero-initialized event");
    return RMW_RET_INVALID_ARGUMENT;
  }

  rmw_event->implementation_identifier = subscription->implementation_identifier;
  rmw_event->data = static_cast<CustomEventInfo *>(subscription->data);
  rmw_event->event_type = event_type;

  return RMW_RET_OK;
}

rmw_ret_t
__rmw_event_fini(const char * identifier, rmw_event_t * event)
{
  RMW_CHECK_ARGUMENT_FOR_NULL(event, RMW_RET_INVALID_ARGUMENT);
  RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
    event,
    event->implementation_identifier,
    identifier,
    return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);

  *event = rmw_get_zero_initialized_event();

  return RMW_RET_OK;
}

}  // namespace rmw_fastrtps_shared_cpp
