#ifndef PROGRESSDATA_HPP
#define PROGRESSDATA_HPP
#include <QObject>
class ProgressData : public QObject {
	Q_OBJECT
	Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged FINAL)
	Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged FINAL)
	Q_PROPERTY(QString completeText READ completeText WRITE setCompleteText NOTIFY completeTextChanged FINAL)
	Q_PROPERTY(qint64 minValue READ minValue WRITE setMinValue NOTIFY minValueChanged FINAL)
	Q_PROPERTY(qint64 maxValue READ maxValue WRITE setMaxValue NOTIFY maxValueChanged FINAL)
	Q_PROPERTY(QString unit READ unit WRITE setUnit NOTIFY unitChanged FINAL)

public:	// constructor
	explicit ProgressData(QObject* parent = nullptr) : QObject(parent) {}

private: // member values
	QString title_;
	QString description_;
	QString complete_text_;
	qint64 min_value_;
	qint64 max_value_;
	QString unit_;

signals:
	void titleChanged(const QString&);
	void descriptionChanged(const QString&);
	void completeTextChanged(const QString&);
	void minValueChanged(qint64);
	void maxValueChanged(qint64);
	void unitChanged(const QString&);

public:	// properties
	[[nodiscard]] const QString& title() const noexcept { return title_; }
	[[nodiscard]] const QString& description() const noexcept { return description_; }
	[[nodiscard]] const QString& completeText() const noexcept { return complete_text_; }
	[[nodiscard]] const qint64& minValue() const noexcept { return min_value_; }
	[[nodiscard]] const qint64& maxValue() const noexcept { return max_value_; }
	[[nodiscard]] const QString& unit() const noexcept { return unit_; }

	void setTitle(const QString& newvalue) noexcept {
		title_ = newvalue;
		emit titleChanged(title_);
	}
	void setDescription(const QString& newvalue) noexcept {
		description_ = newvalue;
		emit descriptionChanged(description_);
	}
	void setCompleteText(const QString& newvalue) noexcept {
		complete_text_ = newvalue;
		emit completeTextChanged(complete_text_);
	}
	void setMinValue(qint64 newvalue) noexcept {
		min_value_ = newvalue;
		emit minValueChanged(min_value_);
	}
	void setMaxValue(qint64 newvalue) noexcept {
		max_value_ = newvalue;
		emit maxValueChanged(max_value_);
	}
	void setUnit(const QString& newvalue) noexcept {
		unit_ = newvalue;
		emit unitChanged(unit_);
	}
};
#endif
