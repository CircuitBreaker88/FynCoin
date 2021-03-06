// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2018 The DraviteFlex developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"

#include "random.h"
#include "util.h"
#include "utilstrencodings.h"
#include "bignum.h"
#include <assert.h>

#include <boost/assign/list_of.hpp>


using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions

static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of(0, uint256("0x00000beb6d31d6fa1c2c223a72bb312d9786da72290da431093fbbbf4b474e6a"))
    (100, uint256("0x000001b2ee273bd9f8be82bc8d70a13c26cbb7543195237479e94d0324355fa4"))
    (200, uint256("0x000004a98302281909bccf94630ab256821dd6b0fcc6a02609e145c9348a344a"))
    (400, uint256("0x000000513a8d1ce2347eba0e89e7f82fc5706a771525f6b8ad4f01b66a84d2ec"))
    (600, uint256("0x0000007f0e962860f782c5f581a37af110225709ff181650b22a49f6dd19e63b"))
    (800, uint256("0x00000000527459192555c33d33f381958dac114430ae395a56b4e253b5e32cd2"))
    (1000, uint256("0x000000027c863fad47e948a72de791de420d3208b53f1b624b92d5ae1a927ce6"))
    (1200, uint256("0x0000000052d282dbad0f0896855c3514fb160b376b2354f2a50ee054d9cdfe9d"))
    (1400, uint256("0xa47cfacf4b7feac582c3b72200e9f1d32861f76809828a0b2fbef9f40b31a315"))
    (1600, uint256("0x8180c2bffd2c6097ead58712d3ab7cf130690c2934e7a88b4514d31e3351f348"))
    (1800, uint256("0x0eabad57947a5f38122421cad073025189bd55491f7f929e840fd442a1464f6a"));
;
static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1551975625, // * UNIX timestamp of last checkpoint block
    1,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    720        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("0x"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    0,
    0,
    0};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    0,
    0,
    0};

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x24;
        pchMessageStart[1] = 0x65;
        pchMessageStart[2] = 0x54;
        pchMessageStart[3] = 0x42;
        vAlertPubKey = ParseHex("04266db20be5c52b94818e2e41c9def7af38197280c65e813f682adf2ed501ac186022562dbdf2ce3204d07432660fb61ecad8e78b6b8d39c568fb892db8ecb736");
        nDefaultPort = 22050;
        bnProofOfWorkLimit = ~uint256(0) >> 20;
        bnProofOfStakeLimit = ~uint256(0) >> 16;
        nSubsidyHalvingInterval = 262800;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 90;
        nTargetSpacing = 90;
        nLastPOWBlock = 0;
        nMaturity = 10;
        nMasternodeCountDrift = 20;
	      nMasternodeColleteralLimxDev = 4000; //Params().MasternodeColleteralLimxDev()
        nModifierUpdateBlock = 1; // we use the version 2 for dmd
        nMaxMoneyOut = 15000000000 * COIN;
        nMinMnCollateral = 10000000 * COIN;
        nMaxMnCollateral = 260000000 * COIN;

        const char* pszTimestamp = "Its time to Flex on the Competition";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 0 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04e928b57880e492fdd2f0cdfd45b52b078a32a5282b4784202ac53b1299837e271f780192a8b014d33b51a6f8bbfc4cfaa3385829452bec7b77bf2f8f97520526") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1551633682;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 397138;

        uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
      /*  while (genesis.GetHash() > hashTarget)
        {
            ++genesis.nNonce;
            if (genesis.nNonce == 0)
            {
                printf("NONCE WRAPPED, incrementing time");
                ++genesis.nTime;
            }
			if (genesis.nNonce % 10000 == 0)
			{
				printf("nonce %08u: hash = %s \n", genesis.nNonce, genesis.GetHash().ToString().c_str());
			}
    }*/

        hashGenesisBlock = genesis.GetHash();
        /*printf("MN nNonce %u\n", genesis.nNonce);
	      printf("MN hashGenesisBlock %s\n", hashGenesisBlock.ToString().c_str());
	      printf("MN hashMerkleRoot %s\n", genesis.hashMerkleRoot.ToString().c_str());
        printf("MN nTime %u\n", genesis.nTime);*/

        assert(hashGenesisBlock == uint256("0x00000beb6d31d6fa1c2c223a72bb312d9786da72290da431093fbbbf4b474e6a"));
        assert(genesis.hashMerkleRoot == uint256("0xde57dcb6be5061596ba388d6ff536de6dbe1bd744b2e14aad6ed3383d8e164f0"));

        vSeeds.push_back(CDNSSeedData("95.179.180.98", "95.179.180.98"));
        vSeeds.push_back(CDNSSeedData("149.28.166.149", "149.28.166.149"));
        vSeeds.push_back(CDNSSeedData("149.56.134.229", "149.56.134.229"));
        vSeeds.push_back(CDNSSeedData("45.76.133.149", "45.76.133.149"));
        vSeeds.push_back(CDNSSeedData("45.32.58.63", "45.32.58.63"));
        vSeeds.push_back(CDNSSeedData("45.32.109.112", "45.32.109.112"));
        vSeeds.push_back(CDNSSeedData("209.250.254.7", "209.250.254.7"));
        vSeeds.push_back(CDNSSeedData("139.180.144.199", "139.180.144.199"));
        vSeeds.push_back(CDNSSeedData("", ""));
        vSeeds.push_back(CDNSSeedData("", ""));
        //vFixedSeeds.clear();
        //vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 31);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 16);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 193);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();
        // 	BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md 109 	0x8000006d
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x6d).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "0278c3e932fbe183b2f665de901966cb1cfc5ed3b0bf733b72286f265ffc03ff52dfd669fbb3f77d630e5393da65c721a9a891d2c4c6aa515dfd25ffe545582357";
        strDarksendPoolDummyAddress = "AcmpqXViWUXNroqVNYRdKjKrFM6PNa1oTM";
        nStartMasternodePayments = 1523967685;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0x64;
        pchMessageStart[1] = 0x75;
        pchMessageStart[2] = 0x29;
        pchMessageStart[3] = 0x22;
        vAlertPubKey = ParseHex("0441286086a0871308bf36091edb18d95bbe9b895abe14ec9b684b5255028ec644bacdbddb98a522a6bcd7ab8e7d3582d7a5b9bf59c427f7eabce447b5ba6de25f");
        nDefaultPort = 25794;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60;
        nTargetSpacing = 1 * 60;
        nLastPOWBlock = 200;
        nSubsidyHalvingInterval = 262800;
        nMaturity = 15;
        nModifierUpdateBlock = 51197; //approx Mon, 30 Apr 2018 04:00:00 GMT
        nMaxMoneyOut = 15000000000 * COIN;

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1551633682;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 397138;


        assert(hashGenesisBlock == uint256("0x00000beb6d31d6fa1c2c223a72bb312d9786da72290da431093fbbbf4b474e6a"));



        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 83);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 18);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 193);
        // Testnet DraviteFlex BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet DraviteFlex BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet DraviteFlex BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "04363509d5c65f5a9ca7ceedad4887007ae85469d249a6f566b788504ee5e105bcf1bbc515f49a7aac3bceb8864bb2ba84bebd92c66ff9022309e2bfbd5f70d11f";
        strDarksendPoolDummyAddress = "";
        nStartMasternodePayments = 1523967686;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        strNetworkID = "regtest";
        pchMessageStart[0] = 0x65;
        pchMessageStart[1] = 0x14;
        pchMessageStart[2] = 0x54;
        pchMessageStart[3] = 0x61;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60;
        nTargetSpacing = 1 * 60;
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        nSubsidyHalvingInterval = 262800;
        genesis.nTime = 1551633682;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 397138;

        hashGenesisBlock = genesis.GetHash();
      /*  uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
        while (genesis.GetHash() > hashTarget)
        {
            ++genesis.nNonce;
            if (genesis.nNonce == 0)
            {
                printf("NONCE WRAPPED, incrementing time");
                ++genesis.nTime;
            }
			if (genesis.nNonce % 10000 == 0)
			{
				printf("nonce %08u: hash = %s \n", genesis.nNonce, genesis.GetHash().ToString().c_str());
			}
        }
        printf("RT nNonce %u\n", genesis.nNonce);
	    printf("RT hashGenesisBlock %s\n", hashGenesisBlock.ToString().c_str());
	    printf("RT hashMerkleRoot %s\n", genesis.hashMerkleRoot.ToString().c_str());
        printf("RT nTime %u\n", genesis.nTime);*/

        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 22988;
        assert(hashGenesisBlock == uint256("0x00000beb6d31d6fa1c2c223a72bb312d9786da72290da431093fbbbf4b474e6a"));

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 22888;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
