#ifndef WALLET_H
#define WALLET_H

#include <QObject>
#include <QDebug>
#include <QList>

#include "AbstractModel.h"
#include "TransactionModel.h"

class WalletInterface;

class WalletModel : public AbstractModel
{
    Q_OBJECT

    Q_PROPERTY(bool ready READ isReady WRITE setReady NOTIFY readyChanged)
    Q_PROPERTY(double balance READ getBalance WRITE setBalance NOTIFY balanceChanged)
    Q_PROPERTY(double unlocked_balance READ getUnlockedBalance WRITE setUnlockedBalance NOTIFY unlockedBalanceChanged)
    Q_PROPERTY(QString address READ getAddress NOTIFY addressChanged)
    Q_PROPERTY(QList<QObject*> transactions READ getTransactions NOTIFY transactionsChanged)
    Q_PROPERTY(QList<QObject*> aggregated_incoming_transactions READ getAggregatedIncomingTransactions NOTIFY aggregatedIncomingTransactionsChanged)
    Q_PROPERTY(QList<QObject*> aggregated_outgoing_transactions READ getAggregatedOutgoingTransactions NOTIFY aggregatedOutgoingTransactionsChanged)

public:
    WalletModel();
    ~WalletModel();

    void setBalance(double pBalance)
    {

        if ( balance == pBalance ) {
            return;
        }

        balance = pBalance;
        emit balanceChanged();

    }

    double getBalance() const
    {
        return balance;
    }


    void setWalletInterface(WalletInterface* iface)
    {
        wallet_interface = iface;
    }

    void setAddress(const QString& pAddress) {
        if ( pAddress != address ) {

            if ( pAddress.length() != 95 ) {
                qCritical() << "Attempted to assign bad address : " << pAddress;
                return;
            }

            address = pAddress;
            emit addressChanged(address);

        }
    }

    const QString& getAddress() const
    {
        return address;
    }


    void setUnlockedBalance(double pUnlockedBalance)
    {
        if (unlocked_balance != pUnlockedBalance) {
            unlocked_balance = pUnlockedBalance;
            emit unlockedBalanceChanged(pUnlockedBalance);
        }
    }


    double getUnlockedBalance() const
    {
        return unlocked_balance;
    }

    const QList<QObject*>& getTransactions() const
    {
        return transactions;
    }

    /* Not invokable from QML */
    void setTransactions(const QList<QObject*>& pTransactions) {

        /* Basic comparison : TODO */
        if ( transactions.size() != pTransactions.size() ) {

            qDeleteAll(transactions);
            transactions = pTransactions;
            emit transactionsChanged(pTransactions);
        }
    }

    /* Not invokable from QML */
    void setAggregatedIncomingTransactions(const QList<QObject*>& pAggregatedTransactions) {

        /* Basic comparison : TODO */
        if ( aggregated_incoming_transactions.size() != pAggregatedTransactions.size() ) {

            qDeleteAll(aggregated_incoming_transactions);
            aggregated_incoming_transactions = pAggregatedTransactions;
            emit aggregatedIncomingTransactionsChanged(pAggregatedTransactions);
        }
    }

    /* Not invokable from QML */
    void setAggregatedOutgoingTransactions(const QList<QObject*>& pAggregatedTransactions) {

        /* Basic comparison : TODO */
        if ( aggregated_outgoing_transactions.size() != pAggregatedTransactions.size() ) {

            qDeleteAll(aggregated_outgoing_transactions);
            aggregated_outgoing_transactions = pAggregatedTransactions;
            emit aggregatedOutgoingTransactionsChanged(pAggregatedTransactions);
        }
    }

    bool isReady() const
    {
        return ready;
    }

    QList<QObject*> getAggregatedIncomingTransactions() const
    {
        return aggregated_incoming_transactions;
    }

    QList<QObject*> getAggregatedOutgoingTransactions() const
    {
        return aggregated_outgoing_transactions;
    }

signals:
    void balanceChanged();
    void transferSuccessful(const QString& tx_hash, double amount, const QString& address, int fee);
    void addressChanged(const QString& pAddress);
    void transferError(int error_code, const QString& error_message);

    void unlockedBalanceChanged(double unlocked_balance);

    void transactionsChanged(QList<QObject*> transactions);
    void aggregatedIncomingTransactionsChanged(QList<QObject*> aggregated_incoming_transactions);
    void aggregatedOutgoingTransactionsChanged(QList<QObject*> aggregated_outgoing_transactions);

    void readyChanged(bool ready);


public slots:
    Q_INVOKABLE bool transfer(double amount, const QString& address, double pFee, const QString& pPaymentId, int pMixinCount);



void setReady(bool pReady)
{
    if (ready != pReady) {
        ready = pReady;
        emit readyChanged(pReady);
    }
}

private:

    WalletInterface* wallet_interface;

    double balance;
    QString address;
    double unlocked_balance;
    QList<QObject*> transactions;
    QList<QObject*> aggregated_incoming_transactions;
    QList<QObject*> aggregated_outgoing_transactions;

    bool ready;

};

#endif // WALLET_H
