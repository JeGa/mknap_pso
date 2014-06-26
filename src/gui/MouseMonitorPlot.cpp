#include "MouseMonitorPlot.h"

#define DEFAULT_MAX_SIZE 500

namespace minotaur
{

    void MouseMonitorPlot::init(QColor color,
                                std::string title,
                                std::string xAxisTitle,
                                std::string yAxisTitle)
    {
        maxSize = DEFAULT_MAX_SIZE;
        xStep = maxSize * 0.1;

        auto cContainer = std::make_shared<CurveContainer>(color);
        cContainer->curve.setSamples(xData, cContainer->yData);
        cContainer->curve.attach(this);

        curves.append(cContainer);

        setTitle(QString(title.c_str()));
        setAxisTitle(QwtPlot::xBottom, QString(xAxisTitle.c_str()));
        setAxisTitle(QwtPlot::yLeft, QString(yAxisTitle.c_str()));
    }

    void MouseMonitorPlot::updatePlot(QVector<double> data)
    {
        if (data.size() != curves.size())
            return;

        xData.append(xData.size());

        for (int i = 0; i < data.size(); ++i) {
            curves[i]->update(data.at(i));
            curves[i]->curve.setSamples(xData, curves[i]->yData);
        }

        replot();
    }

    void MouseMonitorPlot::clear()
    {
        for (auto i : curves)
            i->yData.clear();
        xData.clear();

        replot();
    }

    void MouseMonitorPlot::clearCurves()
    {
        curves.clear();
        xData.clear();

        replot();
    }

    void MouseMonitorPlot::setDotStyle()
    {
        for (int i = 0; i < curves.size(); ++i) {
            curves[i]->curve.setStyle(QwtPlotCurve::CurveStyle::Dots);
            curves[i]->curve.setPen(curves[i]->curve.pen().color(), 3.0);
        }
    }

    void MouseMonitorPlot::addCurve(QColor color)
    {
        auto cContainer = std::make_shared<CurveContainer>(color);
        cContainer->curve.setSamples(xData, cContainer->yData);
        cContainer->curve.attach(this);

        curves.append(cContainer);
    }

}
