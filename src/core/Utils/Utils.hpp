// Copyright (c) 2018 The XSN developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef UTILS_HPP
#define UTILS_HPP

#include <QThread>
#include <QObject>

class WorkerThread : public QThread
{
public:
    explicit WorkerThread(QObject *parent = Q_NULLPTR);
    QObject *context();

private:
    QObject _dummyObject;
};

class Utils
{
public:
    Utils();
};

#endif // UTILS_HPP
