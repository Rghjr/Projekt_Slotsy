#pragma once

#include <QWidget>
#include <QVector>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QLabel>

class ProbabilityInputWidget : public QWidget {
    Q_OBJECT

public:
    explicit ProbabilityInputWidget(int count = 6, QWidget *parent = nullptr);

    QVector<double> getProbabilities() const;

private:
    QVector<QLineEdit*> inputs;
};
