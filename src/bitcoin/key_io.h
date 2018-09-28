// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2018 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_KEY_IO_H
#define BITCOIN_KEY_IO_H

#include <key.h>
#include <pubkey.h>
#include <script/standard.h>

#include <string>

namespace bitcoin {

class CChainParams;

CKey DecodeSecret(const std::string& str, const CChainParams &params);
std::string EncodeSecret(const CKey& key, const CChainParams &params);


CExtKey DecodeExtKey(const std::string& str, const CChainParams &params);
std::string EncodeExtKey(const CExtKey& extkey, const CChainParams &params);
CExtPubKey DecodeExtPubKey(const std::string& str, const CChainParams &params);
std::string EncodeExtPubKey(const CExtPubKey& extpubkey, const CChainParams &params);

std::string EncodeDestination(const CTxDestination& dest, const CChainParams &params);
CTxDestination DecodeDestination(const std::string& str, const CChainParams &params);
bool IsValidDestinationString(const std::string& str, const CChainParams& params);

}

#endif // BITCOIN_KEY_IO_H
