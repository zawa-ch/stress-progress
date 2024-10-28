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
};
#endif
