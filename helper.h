#ifndef HELPER_H
#define HELPER_H

#include <iostream>
#include <QDateTime>
#include <QElapsedTimer>


QElapsedTimer startTime = QElapsedTimer();


std::string formatElapsedTime(long long msec)
{
    long long seconds = msec/1000;
    long long minutes = seconds/60;
    int remainder_seconds = seconds%60;
    long long hours = minutes/60;
    int remainder_minutes = minutes%60;
    return std::to_string(hours) + ":" + std::to_string(remainder_minutes) + ":" + std::to_string(remainder_seconds);
}

void printProgress(float progress, const QString additionalMsg = "", int barWidth=20)
{
    std::string date = QDateTime::currentDateTime().date().toString("MM-dd").toStdString();
    std::string time = QDateTime::currentDateTime().time().toString().toStdString();
    std::cout << date << ' ' << time << ' ' << additionalMsg.toStdString() << " [";
    int pos = barWidth * progress;
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos) std::cout << "=";
        else if (i == pos) std::cout << ">";
        else std::cout << " ";
    }
    std::cout << "] " << int(progress * 100.0) << "%" << "\tElapsed " << (formatElapsedTime(startTime.elapsed()));
    std::cout.flush();
    std::cout << std::endl;
}

#endif // HELPER_H
