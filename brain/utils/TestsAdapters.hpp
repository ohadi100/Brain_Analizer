#pragma once
/**
 * @file
 * @brief This file contains adapters definitions that going to ease the unit tests capabilities.
 *
 */
namespace brain
{
namespace utils
{
#ifdef TESTS
#define VIRTUAL_FOR_TESTS virtual  // Enable UT to override class methods
#else
#define VIRTUAL_FOR_TESTS
#endif

#ifdef TESTS
#define PRIVATE_NOT_FOR_TESTS
#else
#define PRIVATE_NOT_FOR_TESTS private:
#endif

#ifdef TESTS
#define FRIEND_FOR_TESTS(className) friend class className;
#else
#define FRIEND_FOR_TESTS(className)
#endif
}  // namespace utils
}  // namespace brain
