#ifndef DAEMONHANDLER_H
#define DAEMONHANDLER_H

#include <QString>

#include <QProcess>
#include <QDebug>

#include "WalletSettings.h"


class DaemonHandler
{
public:

    DaemonHandler(const WalletSettings& pSettings);
    ~DaemonHandler();

    bool isOk() const {
        qWarning() << "PROGRAM : " << main_process.program();
        return !main_process.program().isEmpty();
    }

    const QString getDaemonProgram() const {
        return main_process.program();
    }

    /* */
    bool execDaemon();
    bool terminateDaemon();

private:

    const WalletSettings& settings;
    QProcess main_process;
};

#endif // DAEMONHANDLER_H
