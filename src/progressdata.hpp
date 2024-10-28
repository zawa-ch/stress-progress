//	SPDX-FileCopyrightText: 2024 zawa-ch.
//	SPDX-License-Identifier: GPL-3.0-only
#ifndef PROGRESSDATA_HPP
#define PROGRESSDATA_HPP
#include <QObject>
struct ProgressData {
public:
	QString title;
	QString description;
	QString completeText;
	int minValue;
	int maxValue;
	QString unit;
	int timerInterval;
	int forwardAmount;
};
#endif
