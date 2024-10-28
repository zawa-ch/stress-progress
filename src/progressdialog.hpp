//	SPDX-FileCopyrightText: 2024 zawa-ch.
//	SPDX-License-Identifier: GPL-3.0-only
#ifndef PROGRESSDIALOG_HPP
#define PROGRESSDIALOG_HPP
#include "completedialog.hpp"
#include "progressdata.hpp"
#include "progresswidget.hpp"

#include <QDialog>
#include <memory>
class ProgressDialog : public QDialog {
	Q_OBJECT

private:
	class UI {
	public:
		UI(QWidget* parent);

		QGridLayout layout;
		ProgressWidget progress;
		CompleteDialog complete;
	};

public:
	ProgressDialog(QWidget* parent = nullptr);

private:
	std::unique_ptr<UI> ui;

public slots:
	void apply(const ProgressData& data);
	void start();
	void stop();
	void reset();

private slots:
	void progress_onComplete(const QString& text);

protected:
	virtual void reject() override;
	virtual void closeEvent(QCloseEvent* e) override;
};
#endif
