#ifndef WALLETINTERFACE_HH
#define WALLETINTERFACE_HH

#include <QDebug>
#include <QList>

#include <map>
#include <ctype.h>

#include "MetaInterface.h"
#include "Models/WalletModel.h"
#include "Models/TransactionModel.h"

class WalletInterface : public MetaInterface
{

public:
    WalletInterface(WalletModel& pWalletModel) : wallet_model(pWalletModel) {
        pWalletModel.setWalletInterface(this);
    }

    virtual ~WalletInterface() {}

    virtual void getBalance() = 0;
    virtual void getAddress() = 0;
    virtual void transfer(unsigned long long pAmount, const QString& pAddress, unsigned long long pFee, const QString& pPaymentId, int pMixinCount) = 0;
    virtual void getPayments(const QString& pPaymentId) = 0;
    virtual void getIncomingTransfers(const QString& pFilter) = 0;
    virtual void store() = 0;

protected:

    void onBalanceUpdated(double pBalance, double pUnlockedBalance)
    {
        wallet_model.setReady(true);
        wallet_model.setBalance(pBalance);
        wallet_model.setUnlockedBalance(pUnlockedBalance);
    }


    void onAddressUpdated(const QString& pAddress)
    {
        wallet_model.setReady(true);
        wallet_model.setAddress(pAddress);
    }


    void onTransferSuccessful(const QString& pTxHash, unsigned long long pAmount, const QString& pAddress, unsigned long long pFee)
    {
        emit wallet_model.transferSuccessful(pTxHash,pAmount,pAddress,pFee);
        qDebug() << "Transfer Successful : " << pAmount << " to " << pAddress << " (fee : " << pFee << ")\nHash: " << pTxHash;
    }


    void onIncomingTransfersUpdated(const QList<TransactionModel*>& pTransfers) {

        QList<QObject*> lAbstractTransfersList;
        for( TransactionModel* lTransaction : pTransfers ) {
            lAbstractTransfersList.append(lTransaction);
        }

        wallet_model.setTransactions(lAbstractTransfersList);
        qDebug() << "Transactions SET";

        /* Aggregates transactions */
        std::map<QString,TransactionModel*> lTransactionsMap;
        for( TransactionModel* lTransaction : pTransfers ) {

            if (lTransactionsMap.count(lTransaction->getId()) == 0) {
                lTransactionsMap[lTransaction->getId()] = new TransactionModel(lTransaction->getId(), 0, true, false);
            }

            TransactionModel* lAggregatedTransaction = lTransactionsMap[lTransaction->getId()];
            lAggregatedTransaction->setAmount( lAggregatedTransaction->getAmount() + lTransaction->getAmount() );
            lAggregatedTransaction->setSpendable( lAggregatedTransaction->isSpendable() && lTransaction->isSpendable() );
        }

        QList<QObject*> lAbstractAggregatedTransfersList;
        for ( std::pair<QString,TransactionModel*> lAggregatedTransaction : lTransactionsMap) {
            lAbstractAggregatedTransfersList.append(lAggregatedTransaction.second);
        }

        wallet_model.setAggregatedTransactions(lAbstractAggregatedTransfersList);

    }


    void onTransferError(int pErrorCode, const QString& pErrorMessage) {

        qWarning() << "Transfer error " << pErrorCode << " : " << pErrorMessage;

        /* Throws to UI */
        emit wallet_model.transferError(pErrorCode, pErrorMessage);

    }

private:
    WalletModel& wallet_model;
};

#endif // WALLETINTERFACE_HH
