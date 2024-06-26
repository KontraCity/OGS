#pragma once

// STL modules
#include <thread>
#include <chrono>
#include <cmath>

namespace kc {

namespace Utility
{
    /// @brief Delay execution for some time
    /// @param seconds Amount of seconds to delay for
    void Sleep(double seconds);

    /// @brief Round value to decimal places
    /// @param value The value to round
    /// @param decimalPlaces Decimal places to round to
    /// @return Rounded value
    double Round(double value, int decimalPlaces);
}

} // namespace kc
