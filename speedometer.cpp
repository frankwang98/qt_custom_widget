#include "speedometer.h"
#include <QPainter>
#include <QtMath>

struct Speedometer::PainterHelper
{
	PainterHelper(QPainter& p) : m_painter(p)
	{
		m_painter.save();
	}
	virtual ~PainterHelper()
	{
		m_painter.restore();
	}

private:
	QPainter& m_painter;
};

Speedometer::Speedometer(QWidget*parent)
	: QWidget(parent)
{
	m_arcLineColorMap.insert(0, "#F22A78");
	m_arcLineColorMap.insert(1, "#F12A78");
	m_arcLineColorMap.insert(2, "#F12B78");

	m_arcLineColorMap.insert(3, "#0FB7ED");
	m_arcLineColorMap.insert(4, "#0FB7CC");
	m_arcLineColorMap.insert(5, "#10B7EC");
	m_arcLineColorMap.insert(6, "#2EC3F9");

	m_arcLineColorMap.insert(7, "#13B48D");
	m_arcLineColorMap.insert(8, "#14B38D");
	m_arcLineColorMap.insert(9, "#15B18D");
	m_arcLineColorMap.insert(10, "#17AF8E");

	setWindowFlags(Qt::FramelessWindowHint);
	setAttribute(Qt::WA_TranslucentBackground);
}

Speedometer::~Speedometer()
{}

/// 
/// @brief:	setIndicatorValue
/// @param: const qreal value - 
///  @ret:	void
///				
void Speedometer::setIndicatorValue(const qreal value)
{
	const qreal maxValue = 1024.0;
	const qreal minValue = 0.0;

	m_longIndicatorValue = value;

	if (minValue > value)
	{
		m_longIndicatorValue = minValue;
	}

	if (maxValue < value)
	{
		m_longIndicatorValue = maxValue;
	}

	update();
}

/// 
/// @brief:	setUnitText
/// @param: const QString & str - 
///  @ret:	void
///				
void Speedometer::setUnitText(const QString& str)
{
	m_unitText = str;
	update();
}

/// 
/// @brief:	setIndicatorValueDecimal
/// @param: const int count - 
///  @ret:	void
///				
void Speedometer::setIndicatorValueDecimal(const int count)
{
	m_indicatorValueDecimalPrecision = count;
	const int maxValue = 2;
	const int minValue = 0;
	if (maxValue < m_indicatorValueDecimalPrecision)
	{
		m_indicatorValueDecimalPrecision = maxValue;
	}

	if (minValue > m_indicatorValueDecimalPrecision)
	{
		m_indicatorValueDecimalPrecision = minValue;
	}
	update();
}

/// 
/// @brief:	paintEvent
/// @param: QPaintEvent * event - 
///  @ret:	void
///				
void Speedometer::paintEvent(QPaintEvent* event)
{
	if (false == isVisible())
	{
		return;
	}

	QPainter painter(this);
	painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing, true);

	int widgetWidth = this->width();
	int widgetHeight = this->height();
	int side = qMin(widgetWidth, widgetHeight);

	m_pieRadius = side * 0.9 / 2.0;

	//绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放
	painter.translate(side / 2 + 4, side / 2 + 4);



	/// 绘制刻度线
	drawArcDialLine(&painter);

	// 绘制圆弧
	drawArc(&painter);

	/// 绘制刻度数值
	drawArcDialLineNumber(&painter);

	/// 绘制指针
	drawIndicator(&painter);

	/// 绘制指示器当前显示的数值
	drawIndicatorValueText(&painter);

}


/// 
/// @brief:	绘制圆弧
/// @param: QPainter * painter - 
///  @ret:	void
///				
void Speedometer::drawArc(QPainter* painter)
{
	PainterHelper ph(*painter);

	/// 保持边距
	const qreal alignOffset = 0;


	/// 圆弧所在矩形
	QRectF outerRect{ -m_pieRadius + alignOffset, -m_pieRadius + alignOffset, m_pieRadius * 2, m_pieRadius * 2 };


	// 定义圆弧的参数
	//QRectF outerRect(50, 50, 200, 200); // 外圆弧的外接矩形
	//QRectF innerRect(60, 60, 180, 180); // 内圆弧的外接矩形（通过缩小矩形实现宽度）
	QRectF innerRect(outerRect.x() + 10, outerRect.y() + 10, outerRect.width() - 20, outerRect.height() - 20);
	int startAngle = -40 * 16;           // 起始角度，单位为1/16度
	int totalSpan = 250 * 16;           // 总跨度角度，单位为1/16度

	// 创建渐变色
	QConicalGradient gradient(outerRect.center(), startAngle / 16); // 渐变色中心点与起始角度对齐
	gradient.setColorAt(0.0, QColor("#F22A78"));	 
	gradient.setColorAt(48 / 250.0, QColor("#0FB7EE"));  
	gradient.setColorAt(144 / 250.0, QColor("#2AEBA2"));  
	gradient.setColorAt(1, QColor("#00FF00"));

	// 创建外圆弧路径
	QPainterPath outerPath;
	outerPath.arcMoveTo(outerRect, startAngle / 16); // 移动到起始点
	outerPath.arcTo(outerRect, startAngle / 16, totalSpan / 16); // 绘制外圆弧

	// 创建内圆弧路径
	QPainterPath innerPath;
	innerPath.arcMoveTo(innerRect, (startAngle + totalSpan) / 16); // 移动到终点
	innerPath.arcTo(innerRect, (startAngle + totalSpan) / 16, -totalSpan / 16); // 绘制内圆弧（反向）

	// 将两条路径连接起来
	QPainterPath path;
	path.addPath(outerPath);
	path.connectPath(innerPath);

	// 使用渐变色填充路径
	painter->fillPath(path, gradient);


}

/// 
/// @brief:	drawArcDialLine
/// @param: QPainter * painter - 
///  @ret:	void
///				
void Speedometer::drawArcDialLine(QPainter* painter)
{
	PainterHelper ph(*painter);
	painter->setBrush(Qt::NoBrush);
	const qreal lineLen = 13;
	qreal pieRadius = m_pieRadius;

	/// colorStr-划线的颜色
	/// rotateAngle - 较零位的旋转角度
	auto drawArcLine = [&painter, &lineLen, &pieRadius](const QString& colorStr, const qreal rotateAngle)
	{
		painter->setPen(QPen(QColor(colorStr), 2));
		painter->rotate(rotateAngle);
		painter->drawLine(pieRadius - lineLen, 0, pieRadius - 1, 0);
	};

	/// 总共需要绘制11根刻度线，
	const qint32 lineCount = 11;

	/// 绘制每根刻度线需要旋转的角度
	qreal rotateAngle = m_arcAngle / (lineCount - 1);

	/// 多旋转, 是为了统一绘制刻度线. 
	painter->rotate(150 - rotateAngle);

	for (int index = lineCount - 1; index >= 0; --index)
	{
		/// 得到刻度线的颜色
		const QString colorStr = m_arcLineColorMap.value(index);

		rotateAngle = ((lineCount - 10) * 100) * (240.0 / 1000.0);

		/// 顺时针绘制刻度线，所以角度为正数
		drawArcLine(colorStr, rotateAngle);
	}
}

/// 
/// @brief:	drawArcDialLineNumber
/// @param: QPainter * painter - 
///  @ret:	void
///				
void Speedometer::drawArcDialLineNumber(QPainter* painter)
{
	PainterHelper ph(*painter);

	qreal textRadius = m_pieRadius * 0.75;

	QFontMetrics fm(painter->font());
	
	/// 总共需要绘制11根刻度线，
	const qint32 lineCount = 11;

	/// 绘制每根刻度线需要旋转的角度
	//const qreal rotateAngle = 250.0 / (lineCount - 1);
	/// 绘制数值的方向时顺时针， 从左向右绘制，
	qreal startAngle = 60 + 90;

	for (int index = 0; index < lineCount; ++ index)
	{
		QString valueStr = QString::number(index * 100);

		int tmpAngle = startAngle + ((index * 100) * (250.0 / 1024));
		qreal angleArc = (tmpAngle % 360) * 3.14159265 / 180.0;

		qreal textXX = (textRadius) * cos(angleArc);
		qreal textYY = (textRadius) * sin(angleArc);

		int textW = (int)fm.width(valueStr);
		int textH = (int)fm.height();

		textXX -= textW / 2;
		textYY -= textH / 2;

		const QString textColor = m_arcLineColorMap[lineCount - 1 - index];
		painter->setPen(QColor(textColor));
		painter->drawText(textXX, textYY, textW, textH, Qt::AlignCenter, valueStr);
	}

}

/// 
/// @brief:	绘制长指针
/// @param: QPainter * painter - 
///  @ret:	void
///				
void Speedometer::drawIndicator(QPainter* painter)
{
	PainterHelper ph(*painter);

	/// 长指针是一个四边形组成
	/// 指针偏转方向： 顺时针，
	const qreal startAngle = 60 + 90;
	
	/// 表盘的范围时0~100，角度范围 240度。 计算当前指针的偏转角度
	const qreal tmpIndicatorAngle = m_longIndicatorValue * (m_arcAngle / 1000.0);

	/// 指针的偏转角度=起始角度+当前角度
	const qreal indicatorAngle = startAngle + tmpIndicatorAngle;

	/// 旋转指定角度
	painter->rotate(indicatorAngle);

	/// 绘制固定的四边形, 长指针较长的一端指向X的正半轴
	QPointF longIndicatorPointArr[4] = 
	{
		QPointF(-12, 0),
		QPointF(0, -6),
		QPointF(m_pieRadius * 1.0, 0),
		//QPointF(m_pieRadius * 1.0, 1),
		QPointF(0, 6)
	};

	painter->setPen(QColor(m_longIndicatorBorderLineColor));
	painter->setBrush(QColor(m_longIndicatorFillColor));

	painter->drawPolygon(longIndicatorPointArr, sizeof(longIndicatorPointArr) / sizeof(longIndicatorPointArr[0]));
}

/// 
/// @brief:	drawIndicatorValueText
/// @param: QPainter * painter - 
///  @ret:	void
///				
void Speedometer::drawIndicatorValueText(QPainter* painter)
{
	PainterHelper ph(*painter);

	const QString valueStr = QString("%1").arg(m_longIndicatorValue, 0, 'f', m_indicatorValueDecimalPrecision);

	painter->setBrush(Qt::NoBrush);
	painter->setPen(QColor(m_indicatorValueTextColor));

	QRectF valueRect{};
	{
		QFont fontTmp = painter->font();
		fontTmp.setPointSize(22);
		painter->setFont(fontTmp);


		QFontMetrics fm(fontTmp);
		/// 计算文字显示的矩形方框
		qreal textW = (m_pieRadius * 0.7 * 0.8) * 2;
		qreal textH = fm.height();
		qreal textYY = m_pieRadius * 0.7 * 0.5;
		painter->drawText(-textW / 2, textYY, textW, textH, Qt::AlignCenter, valueStr);
		valueRect = QRectF{ -textW / 2, textYY, textW, textH };
	}


	/// 绘制显示的单位
	QFont fontTmp = painter->font();
	fontTmp.setPointSize(12);
	painter->setFont(fontTmp);
	QFontMetrics fm(fontTmp);

	/// 单位显示的宽和高为数值显示的宽高相同
	qreal textWW = valueRect.width();
	qreal textHH = fm.height();
	qreal textXX = valueRect.x();
	qreal textYY = valueRect.y() + valueRect.height() + 3;

	painter->setPen(QColor(m_unitTextColor));
	painter->drawText(textXX, textYY, textWW, textHH, Qt::AlignCenter, m_unitText);
}
