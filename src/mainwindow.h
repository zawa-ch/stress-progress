#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "progressdialog.hpp"

#include <QMainWindow>
#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
	Q_OBJECT

public:
	MainWindow(QWidget* parent = nullptr);
	~MainWindow();

private:
	Ui::MainWindow* ui;
	std::unique_ptr<ProgressDialog> dialog;

private slots:
	void dialog_onFinished(int result);
	void unitEdit_onTextChanged(const QString& text);
	void startValueSpin_onValueChanged(int value);
	void endValueSpin_onValueChanged(int value);
	void execButton_onClicked();
	void action_Quit_onTriggered();
	void action_Execute_onTriggered();

private:
	void run_progress();
	void update_value_range();
	void update_value_unit();
	void enable_exec();
	void disable_exec();
};
#endif // MAINWINDOW_H
