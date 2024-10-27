#ifndef PROGRESSWIDGET_HPP
#define PROGRESSWIDGET_HPP
#include "progressdata.hpp"

#include <QLabel>
#include <QLayout>
#include <QProgressBar>
#include <QWindow>
#include <memory>
namespace UI {
class ProgressWidget {
public:
	explicit ProgressWidget(QWidget* parent = nullptr);

	void init_layout();

	QVBoxLayout layout;
	QLabel descriptionlabel;
	QLabel progresslabel;
	QProgressBar progressbar;
};
} // namespace UI
class ProgressWidget : public QWidget {
	Q_OBJECT
	Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged FINAL)
	Q_PROPERTY(qint64 minValue READ minValue WRITE setMinValue NOTIFY minValueChanged FINAL)
	Q_PROPERTY(qint64 maxValue READ maxValue WRITE setMaxValue NOTIFY maxValueChanged FINAL)
	Q_PROPERTY(QString unit READ unit WRITE setUnit NOTIFY unitChanged FINAL)
	Q_PROPERTY(qint64 value READ value WRITE setValue NOTIFY valueChanged FINAL)

public: // constructor
	explicit ProgressWidget(QWidget* parent = nullptr);

private:
	std::unique_ptr<UI::ProgressWidget> ui;
	qint64 min_value_;
	qint64 max_value_;
	QString unit_;
	qint64 value_;

signals:
	void descriptionChanged(const QString&);
	void minValueChanged(qint64);
	void maxValueChanged(qint64);
	void unitChanged(const QString&);
	void valueChanged(qint64);
	void complete();

public: // properties
	[[nodiscard]] QString description() const noexcept;
	[[nodiscard]] const qint64& minValue() const noexcept;
	[[nodiscard]] const qint64& maxValue() const noexcept;
	[[nodiscard]] const QString& unit() const noexcept;
	[[nodiscard]] const qint64& value() const noexcept;

public slots:
	void setDescription(const QString& newvalue);
	void setMinValue(qint64 newvalue);
	void setMaxValue(qint64 newvalue);
	void setUnit(const QString& newvalue);
	void setValue(qint64 newvalue);
	void advanceValue(qint64 amount);
	void resetValue();

public:
	void apply(const ProgressData& data);

private:
	QString build_progl() const;
};
#endif
