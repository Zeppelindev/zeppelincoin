// Copyright (c) 2014-2016, The Monero Project
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without modification, are
// permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice, this list of
//    conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice, this list
//    of conditions and the following disclaimer in the documentation and/or other
//    materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its contributors may be
//    used to endorse or promote products derived from this software without specific
//    prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
// THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
// STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF
// THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Parts of this file are originally copyright (c) 2012-2013 The Cryptonote developers


#include "wallet_manager.h"
#include "wallet.h"

namespace epee {
    unsigned int g_test_dbg_lock_sleep = 0;
}

namespace Bitmonero {

Wallet *WalletManagerImpl::createWallet(const std::string &path, const std::string &password,
                                    const std::string &language, bool testnet)
{
    WalletImpl * wallet = new WalletImpl(testnet);
    wallet->create(path, password, language);
    return wallet;
}

Wallet *WalletManagerImpl::openWallet(const std::string &path, const std::string &password, bool testnet)
{
    WalletImpl * wallet = new WalletImpl(testnet);
    wallet->open(path, password);
    return wallet;
}

Wallet *WalletManagerImpl::recoveryWallet(const std::string &path, const std::string &memo, bool testnet)
{
    WalletImpl * wallet = new WalletImpl(testnet);
    wallet->recover(path, memo);
    return wallet;
}

bool WalletManagerImpl::closeWallet(Wallet *wallet)
{
    WalletImpl * wallet_ = dynamic_cast<WalletImpl*>(wallet);
    bool result = wallet_->close();
    if (!result) {
        m_errorString = wallet_->errorString();
    } else {
        delete wallet_;
    }
    return result;
}

bool WalletManagerImpl::walletExists(const std::string &path)
{
    return false;
}

std::string WalletManagerImpl::errorString() const
{
    return m_errorString;
}

void WalletManagerImpl::setDaemonHost(const std::string &hostname)
{

}



///////////////////// WalletManagerFactory implementation //////////////////////
WalletManager *WalletManagerFactory::getWalletManager()
{

    static WalletManagerImpl * g_walletManager = nullptr;

    if  (!g_walletManager) {
        epee::log_space::log_singletone::add_logger(LOGGER_CONSOLE, NULL, NULL, LOG_LEVEL_MAX);
        g_walletManager = new WalletManagerImpl();
    }

    return g_walletManager;
}



}
