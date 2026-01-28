/*
*
*    _ _
*    | (_)_ __ ___   ___
*    | | | '_ ` _ \ / _ \
*    | | | | | | | |  __/
*    |_|_|_| |_| |_|\___|
*
*    [Li]ght Weight
*    [M]ulti Threaded
*    & [E]fficient
*
*/


#ifndef LIME_H
#define LIME_H

#include <format>

#include "version.h"
#include "http/http.h"
#include "json/json.h"
#include "threadpool/threadpool.h"
#include "utils/logger.h"

namespace lime {
  namespace version {
    inline constexpr uint8_t Major = VERSION_MAJOR;
    inline constexpr uint8_t Minor = VERSION_MINOR;
    inline constexpr uint8_t Patch = VERSION_PATCH;
    inline constexpr uint8_t EarlyRelease = VERSION_EARLYRELEASE;

    [[nodiscard]]
    constexpr inline std::string to_string() {
      if (EarlyRelease == 0) {
        return std::format("v{}.{}.{}", Major, Minor, Patch);
      }

      return std::format("v{}.{}.{}.{} (early release)", Major, Minor, Patch, EarlyRelease);
    }
  } // verion
} // lime

#endif // LIME_H
