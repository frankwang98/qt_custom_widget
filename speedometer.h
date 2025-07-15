#pragma once

#include <QWidget>
#include <QMap>

class QPaintEvent;
class QPainter;

/// 
/// @brief: 速度仪表控件， 类似网速的控件 
/// 
class Speedometer  : public QWidget
{
	Q_OBJECT

public:
	explicit Speedometer(QWidget*parent = nullptr);
	virtual ~Speedometer();

	/// 
	/// @brief:	设置指示器显示的数值
	/// @param: const qreal value 
	///  @ret:	void
	///				
	void setIndicatorValue(const qreal value);

	/// 
	/// @brief:	设置指示器显示的单位
	/// @param: const QString & str 
	///  @ret:	void
	///				
	void setUnitText(const QString& str);

	/// 
	/// @brief:	设置显示的数值保留几位小数，若为负数，则整数显示， 最大显示2位小数
	/// @param: const int count 
	///  @ret:	void
	///				
	void setIndicatorValueDecimal(const int count);

private:
	void paintEvent(QPaintEvent* event);

	/// 
	/// @brief:	绘制圆弧
	/// @param: QPainter * painter 
	///  @ret:	void
	///				
	void drawArc(QPainter* painter);

	/// 
	/// @brief:	绘制圆弧上的刻度线
	/// @param: QPainter * painter 
	///  @ret:	void
	///				
	void drawArcDialLine(QPainter* painter);

	/// 
	/// @brief:	绘制刻度数值
	/// @param: QPainter * painter 
	///  @ret:	void
	///				
	void drawArcDialLineNumber(QPainter* painter);

	/// 
	/// @brief:	绘制指针
	/// @param: QPainter * painter 
	///  @ret:	void
	///				
	void drawIndicator(QPainter* painter);
	
	/// 
	/// @brief:	绘制指示器的数值
	/// @param: QPainter * painter 
	///  @ret:	void
	///				
	void drawIndicatorValueText(QPainter* painter);

private:
	struct PainterHelper;

	/// pie的半径
	qreal		m_pieRadius{ 10.0 };

	/// 圆弧角度
	const qreal m_arcAngle{ 240.0 };

	/// 红色圆弧所占角度比例
	const qreal m_redArcAngleRate{ 0.2 };
	/// 蓝色圆弧所占角度比例
	const qreal m_blueArcAngleRate{ 0.4 };
	/// 绿色圆弧所占角度比例
	const qreal m_greenArcAngleRate{ 0.4 };

	/// 圆弧刻度线的配置， <key-索引，value-刻度线的颜色>
	QMap<int, QString>	m_arcLineColorMap{};

	/// 当前指针的位置, 范围： 0~1024.0， 若超过极值，指针固定在极值的位置
	qreal m_longIndicatorValue{0};

	/// 指针的填充颜色 #D42231  B2DFF6
	QString m_longIndicatorFillColor{"#5D6B99"};
	/// 指针的边线的颜色
	QString m_longIndicatorBorderLineColor{ "#5D6B99" };

	/// 显示数值的精度,小数点后的个数
	int		m_indicatorValueDecimalPrecision{0};
	/// 显示的文本的颜色
	QString	m_indicatorValueTextColor{"#18BED6"};

	/// 单位文本
	QString m_unitText{"KB/S"};
	/// 单位文本显示的颜色
	QString m_unitTextColor{"#18BED6"};
};
