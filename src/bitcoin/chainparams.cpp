#include "chainparams.hpp"
#include <cassert>

namespace bitcoin {

//==============================================================================

CChainParams::CChainParams(CChainParams::Base58TypesMap base58Map) :
    _base58Types(base58Map)
{
    assert(_base58Types.count(Base58Type::PUBKEY_ADDRESS) == 1);
    assert(_base58Types.count(Base58Type::SCRIPT_ADDRESS) == 1);
    assert(_base58Types.count(Base58Type::SECRET_KEY) == 1);
    assert(_base58Types.count(Base58Type::EXT_PUBLIC_KEY) == 1);
    assert(_base58Types.count(Base58Type::EXT_SECRET_KEY) == 1);
}

//==============================================================================

CChainParams::~CChainParams()
{

}

//==============================================================================

const std::vector<unsigned char> &CChainParams::base58Prefix(CChainParams::Base58Type type) const
{
    auto it = _base58Types.find(type);
    return it->second;
}

//==============================================================================

}
