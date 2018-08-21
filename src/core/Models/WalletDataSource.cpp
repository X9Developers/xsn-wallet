#include "WalletDataSource.hpp"
#include <QTimer>

//==============================================================================

template <class T>
static void ScheduleJob(WorkerThread &thread, std::function<T(void)> job, std::function<void(T)> onSuccess, std::function<void(QString)> onFailure)
{
    QTimer::singleShot(0, thread.context(), [=] {
        try
        {
            const auto &result = job();
            onSuccess(result);
        }
        catch (std::exception &ex)
        {
            onFailure(QString::fromStdString(ex.what()));
        }
    });
}

//==============================================================================

WalletDataSource::WalletDataSource(QObject *parent) : QObject(parent)
{
    initWorkerThread();
}

//==============================================================================

void WalletDataSource::fetchTransactions(QString id)
{
    ScheduleJob<TransactionsList>(_dataSourceWorker,
                std::bind(&WalletDataSource::executeFetch, this, id),
                std::bind(&WalletDataSource::transactionsFetched, this, std::placeholders::_1),
                std::bind(&WalletDataSource::transactionsFetchError, this, std::placeholders::_1));
}

//==============================================================================

void WalletDataSource::initWorkerThread()
{
    _dataSourceWorker.start();
}

//==============================================================================
