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

#ifndef RMW_FASTRTPS_CPP__IDENTIFIER_HPP_
#define RMW_FASTRTPS_CPP__IDENTIFIER_HPP_

extern const char * const eprosima_fastrtps_identifier;

#include "fastrtps/utils/IPLocator.h"

#define SET_MULTICAST(param) \
    eprosima::fastrtps::rtps::Locator_t param##loopbackLocator; \
    eprosima::fastrtps::rtps::IPLocator::createLocator(LOCATOR_KIND_UDPv4, "127.0.0.1", 0, param##loopbackLocator); \
    param.multicastLocatorList.push_back(param##loopbackLocator); \
    param.unicastLocatorList.clear();

#endif  // RMW_FASTRTPS_CPP__IDENTIFIER_HPP_
