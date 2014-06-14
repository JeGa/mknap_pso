/**
 * This plot class is from the Smart-Minotaur project.
 * @author JeGa
 */

#ifndef MOUSE_MONITOR_PLOT_H
#define MOUSE_MONITOR_PLOT_H

#include <qwt_plot_curve.h>
#include <qwt_plot_layout.h>
#include <qwt_plot.h>
#include <QVector>

namespace minotaur
{

    class MouseMonitorPlot : public QwtPlot
    {
            Q_OBJECT

        private:
            QwtPlotCurve curve;

            QVector<double> xData;
            QVector<double> yData;

            int xStep;
            int yStep;
            int maxSize;

            std::string xAxisTitle;
            std::string yAxisTitle;

        public:
            MouseMonitorPlot(QwtPlot *parent = 0) : QwtPlot(parent) {}
            virtual ~MouseMonitorPlot() {}

            void init(QColor color,
                      std::string title,
                      std::string xAxisTitle,
                      std::string yAxisTitle);
            void updatePlot(double data);
            void clear();
            void setDotStyle();
            void toggleColor();
    };

}

#endif