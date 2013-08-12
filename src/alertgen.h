// Copyright (c) 2011-2012
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ALERT_GEN_H
#define ALERT_GEN_H

CAlert GetAlert(int id, std::string message, int relayUntil, int priority, int cancelid, int expiration, std::string privateKey);

#endif
