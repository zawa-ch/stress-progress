#include "progressdialog.hpp"

#include <QCloseEvent>

ProgressDialog::UI::UI(QWidget* parent) : layout(parent), progress(parent), complete(parent) {
	progress.setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
	complete.setModal(true);
	layout.addWidget(&progress);
	layout.setMargin(6);
}
ProgressDialog::ProgressDialog(QWidget* parent) : QDialog(parent), ui(std::make_unique<UI>(this)) {
	connect(&ui->progress, SIGNAL(complete(QString)), SLOT(progress_onComplete(QString)));
}
void ProgressDialog::apply(const ProgressData& data) {
	ui->progress.apply(data);
}
void ProgressDialog::start() {
	ui->progress.startTimer();
}
void ProgressDialog::stop() {
	ui->progress.stopTimer();
}
void ProgressDialog::reset() {
	ui->progress.reset();
}
void ProgressDialog::progress_onComplete(const QString& text) {
	ui->complete.setText(text);
	ui->complete.exec();
	done(0);
}
void ProgressDialog::reject() {
	stop();
	QDialog::reject();
}
void ProgressDialog::closeEvent(QCloseEvent* e) {
	e->accept();
	reject();
}
