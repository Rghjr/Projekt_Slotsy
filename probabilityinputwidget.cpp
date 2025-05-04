#include "ProbabilityInputWidget.h"

ProbabilityInputWidget::ProbabilityInputWidget(int count, QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);

    for (int i = 0; i < count; ++i) {
        auto *label = new QLabel(QString("Prawdopodobieństwo %1:").arg(i + 1), this);
        auto *input = new QLineEdit(this);
        input->setPlaceholderText("Wpisz liczbę");
        inputs.append(input);
        layout->addWidget(label);
        layout->addWidget(input);
    }

    setLayout(layout);
}

QVector<double> ProbabilityInputWidget::getProbabilities() const {
    QVector<double> probs;
    for (auto *input : inputs) {
        probs.append(input->text().toDouble());
    }
    return probs;
}
