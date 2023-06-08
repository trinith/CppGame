#pragma once

#include <Game\OptionalRef.h>
#include <unordered_map>

namespace Assets
{

    template <typename TAsset>
    class AssetBank
    {
    public:
        AssetBank() = default;

        AssetBank(const AssetBank&) = delete;
        AssetBank(AssetBank&&) = delete;
        AssetBank& operator=(const AssetBank&) = delete;
        AssetBank& operator=(AssetBank&&) = delete;

        template <typename... TArgs>
        OptionalRef<TAsset> Create(const std::string& assetName, TArgs&&... args)
        {
            auto emplaceResult = _assets.emplace(
                std::piecewise_construct,
                std::forward_as_tuple(assetName),
                std::forward_as_tuple(std::forward<TArgs>(args)...)
            );

            return (emplaceResult.second) ? OptionalRef<TAsset>{emplaceResult.first->second} : std::nullopt;
        }

        OptionalRef<TAsset> operator[](const std::string& assetName)
        {
            auto findResult = _assets.find(assetName);
            return (findResult != _assets.end()) ? OptionalRef<TAsset>{findResult->second} : std::nullopt;
        }

        OptionalRef<const TAsset> operator[](const std::string& assetName) const
        {
            auto findResult = _assets.find(assetName);
            return (findResult != _assets.end()) ? OptionalRef<const TAsset>{findResult->second} : std::nullopt;
        }

    private:
        using AssetMap = std::unordered_map<std::string, TAsset>;

        AssetMap _assets;
    };

}