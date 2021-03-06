#ifndef WRAPPERWALLET_H
#define WRAPPERWALLET_H

#include <QTimer>
#include <QMutex>

#include "Interfaces/WalletInterface.h"
#include "WalletSettings.h"


namespace Monero { class Wallet; }

class WrapperWallet : public WalletInterface
{
    Q_OBJECT
public:
    WrapperWallet(WalletModel& pModel, const WalletSettings& pSettings, const MoneroInterface& pMoneroInterface) : WalletInterface(pModel,pMoneroInterface), wallet(NULL), settings(pSettings) {}
     ~WrapperWallet();

    void getBalance();
    void getAddress();
    void transfer(unsigned long long pAmount, const QString& pAddress, unsigned long long pFee, const QString& pPaymentId, int pMixinCount);
    void getPayments(const QString& pPaymentId);
    void getIncomingTransfers(const QString& pFilter = "all");
    void store();

    void enable();


public slots:
    bool refreshWallet();

private:
    Monero::Wallet* wallet;
    const WalletSettings& settings;

    QTimer refresh_timer;

    QMutex refresh_mutex;
};

#endif // WRAPPERWALLET_H
