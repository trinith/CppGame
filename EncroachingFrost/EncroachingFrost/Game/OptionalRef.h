#pragma once

#include <optional>

template <typename TType>
using OptionalRef = std::optional<std::reference_wrapper<TType>>;