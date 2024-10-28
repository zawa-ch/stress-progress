#ifndef PROGRESSWIDGET_HPP
#define PROGRESSWIDGET_HPP
#include "progressdata.hpp"

#include <QLabel>
#include <QLayout>
#include <QProgressBar>
#include <QTimer>
#include <QWidget>
#include <memory>
class ProgressWidget : public QWidget {
	Q_OBJECT

	Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged FINAL)
	Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged FINAL)
	Q_PROPERTY(QString completeText READ completeText WRITE setCompleteText NOTIFY completeTextChanged FINAL)
	Q_PROPERTY(int minValue READ minValue WRITE setMinValue NOTIFY minValueChanged FINAL)
	Q_PROPERTY(int maxValue READ maxValue WRITE setMaxValue NOTIFY maxValueChanged FINAL)
	Q_PROPERTY(QString unit READ unit WRITE setUnit NOTIFY unitChanged FINAL)
	Q_PROPERTY(int timerInterval READ timerInterval WRITE setTimerInterval NOTIFY timerIntervalChanged FINAL)
	Q_PROPERTY(int forwardAmount READ forwardAmount WRITE setForwardAmount NOTIFY forwardAmountChanged FINAL)
	Q_PROPERTY(int value READ value WRITE setValue NOTIFY valueChanged FINAL)
	Q_PROPERTY(bool isComplete READ isComplete NOTIFY isCompleteChanged FINAL)

private:
	class UI {
	public:
		explicit UI(QWidget* parent = nullptr);

		void init_layout();

		QVBoxLayout layout;
		QLabel descriptionlabel;
		QLabel progresslabel;
		QProgressBar progressbar;
	};

public: // constructor
	explicit ProgressWidget(QWidget* parent = nullptr);

private:
	ProgressData data;
	std::unique_ptr<UI> ui;
	std::unique_ptr<QTimer> timer;
	int value_;

signals:
	void titleChanged(const QString&);
	void descriptionChanged(const QString&);
	void completeTextChanged(const QString&);
	void minValueChanged(int);
	void maxValueChanged(int);
	void unitChanged(const QString&);
	void timerIntervalChanged(int);
	void forwardAmountChanged(int);
	void valueChanged(int);
	void isCompleteChanged(bool);
	int advance(int);
	void complete(const QString&);

public: // properties
	[[nodiscard]] const QString& title() const noexcept;
	[[nodiscard]] const QString& description() const noexcept;
	[[nodiscard]] const QString& completeText() const noexcept;
	[[nodiscard]] const int& minValue() const noexcept;
	[[nodiscard]] const int& maxValue() const noexcept;
	[[nodiscard]] const QString& unit() const noexcept;
	[[nodiscard]] const int& timerInterval() const noexcept;
	[[nodiscard]] const int& forwardAmount() const noexcept;
	[[nodiscard]] const int& value() const noexcept;
	[[nodiscard]] bool isComplete() const noexcept;

private slots:
	void timer_onTimeout();

public slots:
	void setTitle(const QString& title);
	void setDescription(const QString& description);
	void setCompleteText(const QString& text);
	void setMinValue(int newvalue);
	void setMaxValue(int newvalue);
	void setUnit(const QString& unit);
	void setTimerInterval(int msec);
	void setForwardAmount(int amount);
	void setValue(int newvalue);
	void advanceValue(int amount);
	void resetValue();
	void apply(const ProgressData& data);
	void reset();
	void startTimer();
	void stopTimer();

private:
	void update_value(int);
	int normalize_value(int) const;
	QString build_progl() const;
};
#endif
