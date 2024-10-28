#include "mainwindow.h"

#include "./ui_mainwindow.h"
#include "versiondialog.hpp"

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent), ui(new Ui::MainWindow), dialog(std::make_unique<ProgressDialog>(this)) {
	ui->setupUi(this);
	connect(dialog.get(), SIGNAL(finished(int)), SLOT(dialog_onFinished(int)));
	connect(ui->startValueSpin, SIGNAL(valueChanged(int)), SLOT(startValueSpin_onValueChanged(int)));
	connect(ui->endValueSpin, SIGNAL(valueChanged(int)), SLOT(endValueSpin_onValueChanged(int)));
	connect(ui->unitEdit, SIGNAL(textChanged(QString)), SLOT(unitEdit_onTextChanged(QString)));
	connect(ui->execButton, SIGNAL(clicked()), SLOT(execButton_onClicked()));
	connect(ui->action_Quit, SIGNAL(triggered()), SLOT(action_Quit_onTriggered()));
	connect(ui->action_Execute, SIGNAL(triggered()), SLOT(action_Execute_onTriggered()));
	connect(ui->action_About, SIGNAL(triggered()), SLOT(action_About_onTriggered()));
}
MainWindow::~MainWindow() {
	delete ui;
}
void MainWindow::dialog_onFinished(int result) {
	enable_exec();
}
void MainWindow::startValueSpin_onValueChanged(int value) {
	update_value_range();
}
void MainWindow::endValueSpin_onValueChanged(int value) {
	update_value_range();
}
void MainWindow::unitEdit_onTextChanged(const QString& text) {
	update_value_unit();
}
void MainWindow::execButton_onClicked() {
	run_progress();
}
void MainWindow::action_Quit_onTriggered() {
	close();
}
void MainWindow::action_Execute_onTriggered() {
	run_progress();
}
void MainWindow::action_About_onTriggered() {
	auto dialog = VersionDialog(this);
	dialog.exec();
}
void MainWindow::run_progress() {
	ProgressData pdata;
	pdata.title = ui->titleEdit->text();
	pdata.description = ui->descriptionEdit->toHtml();
	pdata.completeText = ui->completeTextEdit->toHtml();
	pdata.minValue = ui->startValueSpin->value();
	pdata.maxValue = ui->endValueSpin->value();
	pdata.unit = ui->unitEdit->text();
	pdata.timerInterval = ui->tickIntervalSpin->value();
	pdata.forwardAmount = ui->advanceAmountSpin->value();
	disable_exec();
	dialog->apply(pdata);
	dialog->show();
	dialog->start();
}
void MainWindow::update_value_range() {
	ui->endValueSpin->setMinimum(ui->startValueSpin->value());
	ui->startValueSpin->setMaximum(ui->endValueSpin->value());
}
void MainWindow::update_value_unit() {
	auto nu = QString(" ") + ui->unitEdit->text();
	ui->startValueSpin->setSuffix(nu);
	ui->endValueSpin->setSuffix(nu);
	ui->advanceAmountSpin->setSuffix(nu);
}
void MainWindow::enable_exec() {
	ui->execButton->setEnabled(true);
	ui->action_Execute->setEnabled(true);
	show();
}
void MainWindow::disable_exec() {
	ui->execButton->setEnabled(false);
	ui->action_Execute->setEnabled(false);
	hide();
}
