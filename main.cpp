#include <QCoreApplication>
#include <QDebug>
#include <QCommandLineParser>
#include "openCLHelper.h"
#include "helper.h"


#define DEFAULT_OUTPUT_DIR "./output"
#define DEFAULT_PLATFORM 0
#define DEFAULT_DEVICE 0

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    startTime.start();
    QCoreApplication::setApplicationName("lsmi");
    QCoreApplication::setApplicationVersion("1.0");
    QCommandLineParser parser;
    parser.setApplicationDescription("Helper\nThe app requires at least the -b & -p or -d to run.");
    parser.addHelpOption();
    parser.addOptions({
            {{"b", "brain-tag"},
                QCoreApplication::translate("main", "Brain Tag to be used.")},
            {{"p", "pair-tag"},
                QCoreApplication::translate("main", "Pair Tag to be used.")},
            {{"o", "output-directory"},
                QCoreApplication::translate("main", "Output processed files to <directory>."),
                QCoreApplication::translate("main", "directory")},
            {{"l", "device-list"},
              QCoreApplication::translate("main", "List processing usable devices available.")},
            {{"d","device"},QCoreApplication::translate("main", "Set selected <platform> & <device>"),
            QCoreApplication::translate("main", "platform device")}
        });
    parser.process(app);
    if (parser.isSet("l"))
    {
        printDevicesInfo();
        printProgress(0.55, "testing!!!!!");
        app.exit(0);
        return 0;
    }
    const QString outDir = parser.isSet("o") ? parser.value("o") : QString(DEFAULT_OUTPUT_DIR);
    int platform_id = parser.isSet("d") ? parser.values("d")[0].toInt() : DEFAULT_PLATFORM;
    int device_id = parser.isSet("d") ? parser.values("d")[1].toInt() : DEFAULT_DEVICE;
    if (!parser.isSet("b") || !parser.isSet("p"))
        parser.showHelp(1);
    const QString brainTag = parser.value("b");
    const QString pairTag = parser.value("p");
    return app.exec();
}
