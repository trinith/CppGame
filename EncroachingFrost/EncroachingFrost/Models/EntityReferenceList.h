#pragma once

#include <vector>

template <typename TEntity>
using EntityReferenceList = std::vector<std::reference_wrapper<TEntity>>;