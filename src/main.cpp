#include "core/BluecherryApp.h"
#include "ui/MainWindow.h"
#include <QApplication>
#include <QSettings>
#include <QtPlugin>
#include <QMessageBox>

#ifdef QT_STATIC
Q_IMPORT_PLUGIN(qjpeg)
#endif

#ifdef USE_BREAKPAD
void initBreakpad();
#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    {
        QStringList args = a.arguments();
        args.takeFirst();
        if (args.size() >= 1 && args[0] == QLatin1String("--crash"))
        {
            QMessageBox::critical(0, QObject::tr("Crash"), QObject::tr("Crash!\n%1").arg((args.size() >= 2) ? args[1] : QString()), QMessageBox::Ok);
            return 0;
        }
    }

#ifdef USE_BREAKPAD
    initBreakpad();
#endif

    a.setOrganizationName(QLatin1String("bluecherry"));
    a.setOrganizationDomain(QLatin1String("bluecherrydvr.com"));
    a.setApplicationName(QLatin1String("bluecherry"));

#ifdef Q_OS_WIN
    QSettings::setDefaultFormat(QSettings::IniFormat);
#endif

    bcApp = new BluecherryApp;

    MainWindow w;
    w.show();

    return a.exec();
}
