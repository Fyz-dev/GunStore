#include "login.h"
#include "connectionhandler.h"
#include "mainwindow.h"

#include <QApplication>
#include <QSqlDatabase>
#include <QVBoxLayout>
#include <QLabel>

#include <QDateTime>
#include <QFile>
void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    switch (type) {
    case QtDebugMsg:
        fprintf(stderr, "Debug: %s (%s:%u, %s)\n", msg.toStdString().c_str(), context.file, context.line, context.function);
        break;
    case QtWarningMsg:
        fprintf(stderr, "Warning: %s (%s:%u, %s)\n", msg.toStdString().c_str(), context.file, context.line, context.function);
        break;
    case QtCriticalMsg:
        fprintf(stderr, "Critical: %s (%s:%u, %s)\n", msg.toStdString().c_str(), context.file, context.line, context.function);
        break;
    case QtFatalMsg:
        fprintf(stderr, "Fatal: %s (%s:%u, %s)\n", msg.toStdString().c_str(), context.file, context.line, context.function);
        abort();
    }
    // сохраняем информацию о краше в файл
    QFile file("crashlog.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream stream(&file);
    stream << QString("%1 %2:%3 - %4\n").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz")).arg(context.file).arg(context.line).arg(msg);
}


int main(int argc, char *argv[])
{
    qInstallMessageHandler(myMessageOutput);
    QApplication a(argc, argv);
    std::shared_ptr<ConnectionHandler> connectionHandler = std::make_shared<ConnectionHandler>();
    std::shared_ptr<LoginViewModel> loginViewModel = std::make_shared<LoginViewModel>(connectionHandler);
    Login login(loginViewModel);

    login.show();
    if(a.exec() == 13)
    {
        std::unique_ptr<MainWindow> formMainWindow = std::make_unique<MainWindow>(connectionHandler.get());
        formMainWindow->show();

        a.exec();
    }

    return 0;
}
