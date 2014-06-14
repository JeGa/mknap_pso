#include "MouseMonitorPlot.h"

#define DEFAULT_X_STEP 20
#define DEFAULT_Y_STEP 1000
#define DEFAULT_MAX_SIZE 400

namespace minotaur
{

    void MouseMonitorPlot::init(QColor color,
                                std::string title,
                                std::string xAxisTitle,
                                std::string yAxisTitle)
    {
        xStep = DEFAULT_X_STEP;
        yStep = DEFAULT_Y_STEP;
        maxSize = DEFAULT_MAX_SIZE;

        curve.setPen(color);
        curve.setSamples(xData, yData);
        curve.attach(this);

        setTitle(QString(title.c_str()));
        setAxisTitle(QwtPlot::xBottom, QString(xAxisTitle.c_str()));
        setAxisTitle(QwtPlot::yLeft, QString(yAxisTitle.c_str()));
    }

    void MouseMonitorPlot::updatePlot(double data)
    {
        xData.append(xData.size());
        yData.append(data);

        curve.setSamples(xData, yData);

        replot();
    }

    void MouseMonitorPlot::clear()
    {
        xData.clear();
        yData.clear();

        replot();
    }

    void MouseMonitorPlot::setDotStyle()
    {
        curve.setStyle(QwtPlotCurve::CurveStyle::Dots);
        curve.setPen(Qt::blue, 3.0);
    }

    void MouseMonitorPlot::toggleColor()
    {
        static int color = 0;
        curve.setPen((Qt::GlobalColor)color++, 3.0);

        if (color == 20)
            color = 0;
    }

}
