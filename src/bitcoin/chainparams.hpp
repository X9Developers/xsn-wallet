#ifndef CHAINPARAMS_HPP
#define CHAINPARAMS_HPP

#include <vector>
#include <map>

namespace bitcoin {

struct CChainParams {
    enum class Base58Type {
        PUBKEY_ADDRESS,
        SCRIPT_ADDRESS,
        SECRET_KEY,
        EXT_PUBLIC_KEY,
        EXT_SECRET_KEY,
        MAX_BASE58_TYPES
    };

    using Base58TypesMap = std::map<Base58Type, std::vector<unsigned char>>;

    explicit CChainParams(Base58TypesMap base58Map);
    ~CChainParams();

    const std::vector<unsigned char> &base58Prefix(Base58Type type) const;

private:
    Base58TypesMap _base58Types;
};

}

#endif // CHAINPARAMS_HPP
