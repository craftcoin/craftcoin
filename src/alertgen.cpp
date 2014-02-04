// Copyright (c) 2011-2012 
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

//////////////////////////////////////////////////////////////////////////
//
// Key Generation
//
// Generate private key
//
//    openssl ecparam -out key.pem -name secp256k1 -genkey
//
// Print out key pair
//
//    openssl ec -inform PEM -in key.pem  -pubout -text -noout
//
// Take the public key (pub) and remove all : symbols and convert into a
// single line.
// 
// Paste this hex string as the alert public key in main.h
//
// Search for CheckSignature and key.SetPubKey(ParseHex("..."))
// 
// This updates the public key so clients will accept alerts from the 
// private key
//
// Encoding private key
//
// Note: The private key must be kept secure
//
// Convert the private key to der format
//
//    openssl ec -inform pem -in key.pem -param_enc explicit -outform der -out key.der 
//
// Convert the der format to a hex representation of the private key
//
//    xxd -p key.der
// 
// Alerts can be sent from the command line using the rpc interface.
// Replace 30...4b with the private key as a single line hex string.
// The private key has a length of 279 bytes (558 characters)
//
// ./craftcoind sendalert 30 "The alert message" 1376433494 21 21 30...4b
//
//////////////////////////////////////////////////////////////////////////


#include "main.h"
#include "key.h"
#include "alertgen.h"

using namespace std;
using namespace boost;

CAlert GetAlert(int id, std::string message, int relayUntil, int priority, int cancelid, int expiration, std::string privateKey)
{

     CUnsignedAlert alert;

     alert.SetNull();

     alert.nRelayUntil = relayUntil;
     alert.nExpiration = expiration;
     alert.nID = id;
     alert.nCancel = cancelid;
     alert.nMinVer = 0;
     alert.nMaxVer = PROTOCOL_VERSION + 10000;
     alert.nPriority = priority;

     alert.strStatusBar = message;

     CDataStream s(SER_NETWORK, PROTOCOL_VERSION);
     s << alert;

     CAlert signedAlert;
     signedAlert.vchMsg.resize(s.size());
     s.read((char*)&signedAlert.vchMsg[0], s.size());

     CDataStream prKeySer(SER_NETWORK, PROTOCOL_VERSION);

     prKeySer << ParseHex(privateKey);

     CPrivKey prKey;
     prKeySer >> prKey;

     CKey key;
     key.SetPrivKey(prKey);

     key.Sign(Hash(signedAlert.vchMsg.begin(), signedAlert.vchMsg.end()), signedAlert.vchSig);

     return signedAlert;

}
