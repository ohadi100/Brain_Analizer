/*
 * araUtils.hpp
 *
 *  Created on: Mar 10, 2021
 *      Author: Amit Kulkarni (S46R7VL) (amit.kulkarni@embitel.com)
 * 
 * We needed this file from the DRM (for future outputs).
 * Since we found multiple instances of this file across multiple repositories, we decided to take it as is without any changes.
 */

#ifndef SRC_INCLUDE_UTILS_ARAUTILS_HPP_
#define SRC_INCLUDE_UTILS_ARAUTILS_HPP_

#include <ara/core/future.h>
#include <ara/core/promise.h>

namespace vwg 
{
namespace e3p 
{
namespace drm 
{
/**
 * @brief Creates an \c ara::core::Future<T> instance containing a promise resolved to \p retVal
 *
 * @tparam T The type of the returned value.
 * @param retVal The value to be returned encapsulated in a \c Future object
 * @return An \c ara::core::Future<T> object containing a promise resolved to \p retVal
 */
template <typename T>
inline ara::core::Future<T>
createFutureOutput(T&& retVal)
{
    ara::core::Promise<T> promise;
    auto                  future = promise.get_future();
    promise.set_value(std::forward<T>(retVal));
    return future;
}

/**
 * @brief Creates an \c ara::core::Future<T> instance containing a promise resolved to the default value of \c T
 *
 * @tparam T The type of the returned value.
 * @param retVal The value to be returned encapsulated in a \c Future object.
 * @return An \c ara::core::Future<T> containing a promise resolved to the default value of \c T
 */
template <typename T>
inline ara::core::Future<T>
createFutureOutput()
{
    T retVal;
    return createFutureOutput(std::move(retVal));
}

/**
 * @brief Creates an \c ara::core::Future<void> instance containing an empty resolved promise.
 *
 * @tparam
 * @return An \c ara::core::Future<T> containing an empty resolved promise.
 */
template <>
inline ara::core::Future<void>
createFutureOutput()
{
    ara::core::Promise<void> promise;
    promise.set_value();
    return promise.get_future();
}

} /* namespace drm */
} /* namespace e3p */
} /* namespace vwg */


#endif /* SRC_INCLUDE_UTILS_ARAUTILS_HPP_ */
