//	SPDX-FileCopyrightText: 2024 zawa-ch.
//	SPDX-License-Identifier: GPL-3.0-only
#ifndef COMPLETEDIALOG_HPP
#define COMPLETEDIALOG_HPP
#include <QDialog>
#include <QDialogButtonBox>
#include <QLabel>
#include <QVBoxLayout>
#include <memory>
class CompleteDialog : public QDialog {
	Q_OBJECT
	Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged FINAL)

private:
	class UI {
	public:
		UI(QWidget* parent) : layout(parent), body(parent), buttons(parent) {
			body.setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
			buttons.setStandardButtons(QDialogButtonBox::Ok);
			layout.addWidget(&body);
			layout.addWidget(&buttons);
		}

		QVBoxLayout layout;
		QLabel body;
		QDialogButtonBox buttons;
	};

public:
	CompleteDialog(QWidget* parent = nullptr) : ui(std::make_unique<UI>(this)) {
		setMinimumSize(200, 140);
		connect(&ui->buttons, SIGNAL(accepted()), SLOT(accept()));
	}

private:
	std::unique_ptr<UI> ui;

signals:
	void textChanged(const QString&);

public:
	[[nodiscard]] QString text() const { return ui->body.text(); }

public slots:
	void setText(const QString& text) {
		ui->body.setText(text);
		emit textChanged(text);
	}
};
#endif
