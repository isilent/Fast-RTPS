// Copyright 2016-2019 Proyectos y Sistemas de Mantenimiento SL (eProsima).
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
 * @file LivelinessManager.h
 */
#ifndef LIVELINESS_MANAGER_H_
#define LIVELINESS_MANAGER_H_

#include "LivelinessData.h"
#include "../timedevent/TimedCallback.h"
#include "../../utils/collections/ResourceLimitedVector.hpp"

namespace eprosima {
namespace fastrtps {
namespace rtps {

/**
 * @brief A class managing the liveliness of a set of writers. Writers are represented by their LivelinessData
 * @details Uses a shared timed event and informs outside classes on liveliness changes
 * @ingroup WRITER_MODULE
 */
class LivelinessManager
{
public:

    /**
     * @brief LivelinessManager
     * @param liveliness_lost_callback
     * @param liveliness_lost_callback
     * @param service
     * @param event_thread
     */
    LivelinessManager(
            const std::function<void(GUID_t)>& liveliness_lost_callback,
            const std::function<void(GUID_t)>& liveliness_recovered_callback,
            asio::io_service& service,
            const std::thread& event_thread);

    /**
     * @brief Constructor
     */
    ~LivelinessManager();

    /**
     * @brief LivelinessManager
     * @param other
     */
    LivelinessManager(const LivelinessManager& other) = delete;

    /**
     * @brief Adds a writer to the set
     * @param guid GUID of the writer
     * @param kind Liveliness kind
     * @param lease_duration Liveliness lease duration
     * @return True if the writer was successfully added
     */
    bool add_writer(
            GUID_t guid,
            LivelinessQosPolicyKind kind,
            Duration_t lease_duration);

    /**
     * @brief Removes a writer
     * @param guid GUID of the writer
     * @return True if the writer was successfully removed
     */
    bool remove_writer(GUID_t guid);

    /**
     * @brief Asserts liveliness of a writer in the set
     * @param guid The writer to assert liveliness of
     * @return True if liveliness was successfully asserted
     */
    bool assert_liveliness(GUID_t guid);

private:

    //! A method call if the timer expires
    void timer_expired();

    //! A vector of liveliness data
    ResourceLimitedVector<LivelinessData> writers_;

    //! A timed callback expiring when a writer (the timer owner) loses its liveliness
    TimedCallback timer_;

    //! The timer owner, i.e. the writer which is next due to lose its liveliness
    LivelinessData* timer_owner_;

    //! A callback to inform outside classes that a writer lost its liveliness
    std::function<void(GUID_t)> liveliness_lost_callback_;

    //! A callback to inform outside classes that a writer recovered its liveliness
    std::function<void(GUID_t)> liveliness_recovered_callback_;
};

} /* namespace rtps */
} /* namespace fastrtps */
} /* namespace eprosima */
#endif /* LIVELINESS_MANAGER_H_ */
