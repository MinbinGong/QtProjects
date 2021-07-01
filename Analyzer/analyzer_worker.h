#ifndef ANALYZER_WORKER_H
#define ANALYZER_WORKER_H

#include <QString>
#include <QWidget>

class analyzer_worker
{
public:
    analyzer_worker();
    virtual ~analyzer_worker() {}

    void execute(QWidget *parent, const QString &reference, const QString &target);
};

#endif // ANALYZER_WORKER_H
