#include "progresswidget.hpp"

#pragma region UI
UI::ProgressWidget::ProgressWidget(QWidget* parent) : layout(parent), descriptionlabel(parent), progresslabel(parent), progressbar(parent) {
	init_layout();
}
void UI::ProgressWidget::init_layout() {
	layout.addWidget(&descriptionlabel);
	layout.addWidget(&progresslabel);
	layout.addWidget(&progressbar);
	progresslabel.setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
	progressbar.setTextVisible(false);
}
#pragma endregion
#pragma region ProgressWidget
ProgressWidget::ProgressWidget(QWidget* parent) : QWidget(parent), ui(std::make_unique<UI::ProgressWidget>(this)) {
	ui->progresslabel.setText(build_progl());
	show();
}
QString ProgressWidget::description() const noexcept { return ui->descriptionlabel.text(); }
const qint64& ProgressWidget::minValue() const noexcept { return min_value_; }
const qint64& ProgressWidget::maxValue() const noexcept { return max_value_; }
const QString& ProgressWidget::unit() const noexcept { return unit_; }
const qint64& ProgressWidget::value() const noexcept { return value_; }
void ProgressWidget::setDescription(const QString& description) {
	ui->descriptionlabel.setText(description);
	emit descriptionChanged(description);
}
void ProgressWidget::setMinValue(qint64 value) {
	min_value_ = value;
	ui->progressbar.setMinimum(min_value_);
	emit minValueChanged(min_value_);
}
void ProgressWidget::setMaxValue(qint64 value) {
	max_value_ = value;
	bool pre_comp = value_ >= max_value_;
	ui->progressbar.setMaximum(max_value_);
	value_ = value_ <= max_value_ ? value_ : max_value_;
	ui->progresslabel.setText(build_progl());
	emit maxValueChanged(max_value_);
	if (!pre_comp && value_ >= max_value_) {
		emit complete();
	}
}
void ProgressWidget::setUnit(const QString& unit) {
	unit_ = unit;
	ui->progresslabel.setText(build_progl());
	emit unitChanged(unit_);
}
void ProgressWidget::setValue(qint64 newvalue) {
	value_ = newvalue;
	bool pre_comp = value_ >= max_value_;
	value_ = value_ <= max_value_ ? value_ : max_value_;
	ui->progressbar.setValue(value_);
	ui->progresslabel.setText(build_progl());
	emit valueChanged(value_);
	if (!pre_comp && value_ >= max_value_) {
		emit complete();
	}
}
void ProgressWidget::advanceValue(qint64 amount) {
	setValue(value() + amount);
}
void ProgressWidget::resetValue() {
	setValue(min_value_);
}
void ProgressWidget::apply(const ProgressData& data) {
	ui->descriptionlabel.setText(data.description());
	min_value_ = data.minValue();
	max_value_ = data.maxValue();
	unit_ = data.unit();
	value_ = min_value_;
	ui->progressbar.setMinimum(min_value_);
	ui->progressbar.setMaximum(max_value_);
	ui->progressbar.setValue(value_);
	ui->progresslabel.setText(build_progl());
	emit descriptionChanged(data.description());
	emit minValueChanged(min_value_);
	emit maxValueChanged(max_value_);
	emit unitChanged(unit_);
	emit valueChanged(value_);
}
QString ProgressWidget::build_progl() const {
	return QString("<span style=\"font-size:") + QString::number(font().pointSizeF() * 1.5f) + "pt\">" + QString::number(value_) + "</span> / " + QString::number(max_value_) + unit_;
}
#pragma endregion
