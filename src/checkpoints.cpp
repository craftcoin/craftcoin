// Copyright (c) 2009-2012 The Bitcoin developers
// Copyright (c) 2011-2012 Litecoin Developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "main.h"
#include "uint256.h"

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    //
    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    //
    static MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of // Fetched from http://crc.cryptocoinexplorer.com/
        (         0, uint256("0x64a9141746cbbe06c7e1a4b7f2abb968ccdeba66cd67c1add1091b29db00578e"))
        (         1, uint256("0xb148d04d286819a2b7b351413803f5119cd99656d4a9858342e823656aff96ce"))
        (        10, uint256("0x16649f8da56b6c0161c9e311cf50679074cc97e891dcbbd361667f73ff100c9e"))
        (       100, uint256("0x81cf9a3d580549022b9824d4da2e89cf069d50065ef81db7f1c655431d58c620"))
        (      1000, uint256("0xb2c469e23698d422d82e8a2e0f311b6b9e53fd834b552009479d0fe28abfae7a"))
        (      2500, uint256("0x1fc1b2d0423b749bf57df04f85d54159c5d31c9bfce891f1c9261836e8e1e50d"))
        (      5000, uint256("0xb60d2946ef3c7a99cfe157326825f5e0a849265a944235834f7d00c4fee454e6"))
        (      7500, uint256("0xcdc68be30f63273f1caf7ee5dfb4b5a582b517aef1befe2c1ebee0e749a736e2"))
        (     10000, uint256("0x8716645da048a0580c8b1b41e2c98d4ee64b1ac182bcba279ad94254b68c04d8"))
        (     15000, uint256("0xf1d1a34dacf4ce0fb555ca4614543277f794b687068aaadc3cd47c96acc96038"))
        (     20000, uint256("0x1f654ca0134c126ab9b00d705359c4315adf992cfb4c055ff31c0d5dab3ca9a1"))
        (     24000, uint256("0xc9f7d4742c8320f7f5cb4e32f0485eb0685b16731e3a0fc0845f3e7dfc124acf"))

        ;

    bool CheckBlock(int nHeight, const uint256& hash)
    {
        if (fTestNet) return true; // Testnet has no checkpoints

        MapCheckpoints::const_iterator i = mapCheckpoints.find(nHeight);
        if (i == mapCheckpoints.end()) return true;
        return hash == i->second;
    }

    int GetTotalBlocksEstimate()
    {
        if (fTestNet) return 0;
        return mapCheckpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        if (fTestNet) return NULL;

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, mapCheckpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }
}
