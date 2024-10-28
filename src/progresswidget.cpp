#include "progresswidget.hpp"

#include <QMetaMethod>

#pragma region UI
ProgressWidget::UI::UI(QWidget* parent) : layout(parent), descriptionlabel(parent), progresslabel(parent), progressbar(parent) {
	init_layout();
}
void ProgressWidget::UI::init_layout() {
	descriptionlabel.setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	progresslabel.setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
	progressbar.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	progressbar.setTextVisible(false);
	layout.addWidget(&descriptionlabel);
	layout.addWidget(&progresslabel);
	layout.addWidget(&progressbar);
}
#pragma endregion
#pragma region ProgressWidget
ProgressWidget::ProgressWidget(QWidget* parent) : QWidget(parent), ui(std::make_unique<UI>(this)) {
	this->connect(timer.get(), SIGNAL(timeout()), SLOT(timer_onTimeout()));
	setMinimumSize(320, 60);
	ui->progresslabel.setText(build_progl());
	show();
}
const QString& ProgressWidget::title() const noexcept { return data.title; }
const QString& ProgressWidget::description() const noexcept { return data.description; }
const QString& ProgressWidget::completeText() const noexcept { return data.completeText; }
const int& ProgressWidget::minValue() const noexcept { return data.minValue; }
const int& ProgressWidget::maxValue() const noexcept { return data.maxValue; }
const QString& ProgressWidget::unit() const noexcept { return data.unit; }
const int& ProgressWidget::timerInterval() const noexcept { return data.timerInterval; }
const int& ProgressWidget::forwardAmount() const noexcept { return data.forwardAmount; }
const int& ProgressWidget::value() const noexcept { return value_; }
bool ProgressWidget::isComplete() const noexcept { return value_ >= data.maxValue; }
void ProgressWidget::timer_onTimeout() {
	auto amount = data.forwardAmount;
	if (isSignalConnected(QMetaMethod::fromSignal(&ProgressWidget::advance))) {
		amount = emit advance(amount);
	}
	advanceValue(amount);
}
void ProgressWidget::setTitle(const QString& title) {
	data.title = title;
	emit titleChanged(title);
}
void ProgressWidget::setDescription(const QString& description) {
	data.description = description;
	ui->descriptionlabel.setText(description);
	emit descriptionChanged(description);
}
void ProgressWidget::setCompleteText(const QString& text) {
	data.completeText = text;
	emit completeTextChanged(text);
}
void ProgressWidget::setMinValue(int newvalue) {
	data.minValue = newvalue;
	emit minValueChanged(newvalue);
	update_value(value_);
}
void ProgressWidget::setMaxValue(int newvalue) {
	data.maxValue = newvalue;
	emit maxValueChanged(newvalue);
	update_value(value_);
}
void ProgressWidget::setUnit(const QString& unit) {
	data.unit = unit;
	ui->progresslabel.setText(build_progl());
	emit unitChanged(unit);
}
void ProgressWidget::setTimerInterval(int msec) {
	data.timerInterval = msec;
	timer->setInterval(msec);
	emit timerIntervalChanged(msec);
}
void ProgressWidget::setForwardAmount(int amount) {
	data.forwardAmount = amount;
	emit forwardAmountChanged(amount);
}
void ProgressWidget::setValue(int newvalue) { update_value(newvalue); }
void ProgressWidget::advanceValue(int amount) {
	setValue(value() + amount);
}
void ProgressWidget::resetValue() {
	setValue(data.minValue);
}
void ProgressWidget::apply(const ProgressData& data) {
	timer->stop();
	this->data = data;
	value_ = data.minValue;
	ui->descriptionlabel.setText(data.description);
	ui->progressbar.setMinimum(data.minValue);
	ui->progressbar.setMaximum(data.maxValue);
	ui->progressbar.setValue(value_);
	ui->progresslabel.setText(build_progl());
	emit titleChanged(data.title);
	emit descriptionChanged(data.description);
	emit completeTextChanged(data.completeText);
	emit minValueChanged(data.minValue);
	emit maxValueChanged(data.maxValue);
	emit unitChanged(data.unit);
	emit timerIntervalChanged(data.timerInterval);
	emit forwardAmountChanged(data.forwardAmount);
	emit valueChanged(value_);
}
void ProgressWidget::reset() {
	timer->stop();
	value_ = data.minValue;
	ui->progressbar.setValue(value_);
	ui->progresslabel.setText(build_progl());
	emit valueChanged(value_);
}
void ProgressWidget::startTimer() {
	timer->start();
}
void ProgressWidget::stopTimer() {
	timer->stop();
}
void ProgressWidget::update_value(int newvalue) {
	if (newvalue == value_) {
		return;
	}
	bool pre_comp = isComplete();
	value_ = normalize_value(newvalue);
	ui->progressbar.setValue(value_);
	ui->progresslabel.setText(build_progl());
	emit valueChanged(value_);
	if (!pre_comp && isComplete()) {
		emit isCompleteChanged(true);
		emit complete(data.completeText);
	} else if (!isComplete() && pre_comp) {
		emit isCompleteChanged(false);
	}
}
int ProgressWidget::normalize_value(int value) const {
	return data.minValue <= value ? (data.maxValue >= value ? value : data.maxValue) : data.minValue;
}
QString ProgressWidget::build_progl() const {
	return QString("<span style=\"font-size:") + QString::number(font().pointSizeF() * 1.5f) + "pt\">" + QString::number(value_) + "</span> / " + QString::number(data.maxValue) + data.unit;
}
#pragma endregion
