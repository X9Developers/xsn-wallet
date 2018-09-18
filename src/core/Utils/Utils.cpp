// Copyright (c) %YEAR The XSN developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#include "Utils.hpp"

//==============================================================================

Utils::Utils()
{

}

//==============================================================================

WorkerThread::WorkerThread(QObject *parent) : QThread(parent)
{
    _dummyObject.moveToThread(this);
}

//==============================================================================

QObject *WorkerThread::context()
{
    return &_dummyObject;
}

//==============================================================================
