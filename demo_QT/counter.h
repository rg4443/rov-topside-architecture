#ifndef _COUNTER_H
#define _COUNTER_H

#include <QLabel>
#include <QPushButton>
#include <QTimer>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFont>
#include <QString>
#include <QWidget>

class Counter : public QWidget {
Q_OBJECT

public:
	Counter(QWidget *parent = nullptr);

private slots:
	void updateCount();
	void reset();

private:
	QLabel *displayLabel;
	QPushButton *startButton;
	QPushButton *stopButton;
	QPushButton *resetButton;
	QTimer *timer;
	int counter;
};

#endif
