#ifndef COMMON_HPP
#define COMMON_HPP
#include <stdint.h>

using AssetID = unsigned;
using AccountIndex = unsigned;
using Balance = int64_t;

/*!
 * \brief RegisterQtTypes call once to register types in qt meta type system.
 */
void RegisterCommonQtTypes();

#endif // COMMON_HPP
