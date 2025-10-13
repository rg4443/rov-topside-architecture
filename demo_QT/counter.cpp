#include "counter.h"

Counter::Counter(QWidget *parent)
	: QWidget(parent)
	, counter(0)
{
	this->displayLabel = new QLabel(QString::number(counter), this);
	this->displayLabel->setAlignment(Qt::AlignCenter);

	QFont font = this->displayLabel->font();
	font.setPointSize(24);
	this->displayLabel->setFont(font);

	this->startButton = new QPushButton("Start", this);
	this->stopButton = new QPushButton("Stop", this);
	this->resetButton = new QPushButton("Reset", this);

	this->timer = new QTimer(this);
	this->timer->setInterval(100);

	// Button Layout
	QHBoxLayout *buttonLayout = new QHBoxLayout(this);
	buttonLayout->addWidget(this->startButton);
	buttonLayout->addWidget(this->stopButton);
	buttonLayout->addWidget(this->resetButton);

	// Main Layout
	// \_ Display Widget
	// \_ Button Layout
	QVBoxLayout *mainLayout = new QVBoxLayout(this);
	mainLayout->addWidget(displayLabel);
	mainLayout->addLayout(buttonLayout);

	this->setLayout(mainLayout);

	this->connect(this->startButton, &QPushButton::clicked, this->timer,
		      qOverload<>(&QTimer::start));
	this->connect(this->stopButton, &QPushButton::clicked, this->timer,
		      &QTimer::stop);
	this->connect(this->resetButton, &QPushButton::clicked, this,
		      &Counter::reset);
	this->connect(timer, &QTimer::timeout, this, &Counter::updateCount);
}

void Counter::updateCount()
{
	this->counter++;
	displayLabel->setText(QString::number(this->counter));
}

void Counter::reset()
{
	this->timer->stop();
	this->counter = 0;
	displayLabel->setText(QString::number(this->counter));
}
