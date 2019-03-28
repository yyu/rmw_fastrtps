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

#include "rmw/rmw.h"

#include "rmw_fastrtps_dynamic_cpp/identifier.hpp"

#include "rmw_fastrtps_shared_cpp/rmw_common.hpp"


rmw_ret_t
rmw_publisher_event_init(
  rmw_event_t * event,
  const rmw_publisher_t * publisher,
  const rmw_event_type_t event_type)
{
  return rmw_fastrtps_shared_cpp::__rmw_publisher_event_init(
    eprosima_fastrtps_identifier, event, publisher, event_type);
}

rmw_ret_t
rmw_subscription_event_init(
  rmw_event_t * event,
  const rmw_subscription_t * subscription,
  const rmw_event_type_t event_type)
{
  return rmw_fastrtps_shared_cpp::__rmw_subscription_event_init(
    eprosima_fastrtps_identifier, event, subscription, event_type);
}

rmw_ret_t
rmw_event_fini(rmw_event_t * event)
{
  return rmw_fastrtps_shared_cpp::__rmw_event_fini(
    eprosima_fastrtps_identifier, event);
}
