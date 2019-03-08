// Copyright 2019 Proyectos y Sistemas de Mantenimiento SL (eProsima).
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

/**
 * @file ServerAttributes.h
 *
 */

#ifndef SERVERATTRIBUTES_H_
#define SERVERATTRIBUTES_H_
#ifndef DOXYGEN_SHOULD_SKIP_THIS_PUBLIC


#include "../common/Guid.h"
#include "../common/Locator.h"


namespace eprosima {
namespace fastrtps{
namespace rtps {

    class ParticipantProxyData;

    /**
     * Class RemoteServerAttributes, to define the attributes of the Discovery Server Protocol.
     * @ingroup RTPS_ATTRIBUTES_MODULE
     */

    class RemoteServerAttributes
    {
    public:
        inline bool operator==(const RemoteServerAttributes & r) const { return guidPrefix == r.guidPrefix; }

        GUID_t GetPDPReader() const;
        GUID_t GetPDPWriter() const;

        GUID_t GetEDPPublicationsReader() const;
        GUID_t GetEDPSubscriptionsWriter() const;

        GUID_t GetEDPPublicationsWriter() const;
        GUID_t GetEDPSubscriptionsReader() const;

        //!Metatraffic Unicast Locator List
        LocatorList_t metatrafficUnicastLocatorList;
        //!Metatraffic Multicast Locator List.
        LocatorList_t metatrafficMulticastLocatorList;

        //!Guid prefix
        GuidPrefix_t guidPrefix;

        // Live participant proxy reference
        const ParticipantProxyData * proxy{};
    };
}
} /* namespace rtps */
} /* namespace eprosima */
#endif
#endif /* SERVERATTRIBUTES_H_ */
