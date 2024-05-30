#include "utility.hpp"

namespace kc {

void Utility::Sleep(double seconds)
{
    std::this_thread::sleep_for(std::chrono::microseconds(static_cast<size_t>(seconds * 1'000'000)));
}

double Utility::Round(double value, int decimalPlaces)
{
    double multiplier = std::pow(10, decimalPlaces);
    double result = std::round(value * multiplier) / multiplier;
    return (result == -0 ? 0 : result); // -0 doesn't make sense
}

} // namespace kc
