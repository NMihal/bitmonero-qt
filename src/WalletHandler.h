#ifndef WALLETHANDLER_H
#define WALLETHANDLER_H

#include <QProcess>
#include <QObject>
#include <QDir>
#include <QDebug>

/* TODO : Add an abstraction layer */
class WalletHandler : public QObject
{

Q_OBJECT

Q_PROPERTY(QString default_wallet_location READ getDefaultWalletLocation)


public:

    WalletHandler(const QString& pProgramPath = "/usr/bin/simplewallet");

    const QString& getDefaultWalletLocation() const
    {
        qDebug() << "LOC ";
        return default_wallet_location;
    }

public slots:

    Q_INVOKABLE bool createWallet(const QString& pFile, const QString& pPassword);

    bool tryWalletProgram();


    bool tryWallet(const QString& pFile, const QString& pPassword);
    Q_INVOKABLE bool tryWalletAsync(const QString& pFile, const QString& pPassword);

    bool closeWallet();
    bool openWalletAsync(const QString& pWalletFile, const QString& pWalletPassword, const QString& pBindIP, int pBindPort);

    bool isOpen() const {
        return open;
    }

    Q_INVOKABLE bool walletFileExists(const QString &pFile);

public slots:
    void tryWalletResponse(int pCode);

signals:
    void tryWalletResult(bool result);

private:

    QProcess* execTryWallet(const QString& pFile, const QString& pPassword);

    bool walletDirectoryExists(const QString& pFile);

    QString default_wallet_location = QDir::homePath() + "/.bitmonero/";
    QProcess main_process;
    bool open;

};

#endif // WALLETHANDLER_H