#ifndef VERSIONDIALOG_HPP
#define VERSIONDIALOG_HPP
#include "applicationdomain.hpp"

#include <QDialog>
#include <QDialogButtonBox>
#include <QLabel>
#include <QVBoxLayout>
#include <memory>
class VersionDialog : public QDialog {
	Q_OBJECT

private:
	class UI {
	public:
		UI(QWidget* parent) : layout(parent), body(parent), buttons(parent) {
			buttons.setStandardButtons(QDialogButtonBox::Ok);
			layout.addWidget(&body);
			layout.addWidget(&buttons);
		}

		QVBoxLayout layout;
		QLabel body;
		QDialogButtonBox buttons;
	};

public:
	VersionDialog(QWidget* parent = nullptr) : ui(std::make_unique<UI>(this)) {
		setMinimumSize(200, 140);
		connect(&ui->buttons, SIGNAL(accepted()), SLOT(accept()));
		ui->body.setText("<span style=\"font-size:" + QString::number(font().pointSizeF() * 1.5f) + "pt;\">" + tr("application_title") + "</span><br/>" + ApplicationDomain::name + " " + ApplicationDomain::version + "<br/>" + ApplicationDomain::author + " licensed under " + ApplicationDomain::license + "<br/>" + ApplicationDomain::url);
	}

private:
	std::unique_ptr<UI> ui;
};
#endif
