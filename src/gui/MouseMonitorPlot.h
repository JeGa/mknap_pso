/**
 * This plot class is from the Smart-Minotaur project.
 * @author JeGa
 */

#ifndef MOUSE_MONITOR_PLOT_H
#define MOUSE_MONITOR_PLOT_H

#include <memory>

#include <qwt_plot_curve.h>
#include <qwt_plot_layout.h>
#include <qwt_plot.h>
#include <QVector>

namespace minotaur
{

    struct CurveContainer {
        QwtPlotCurve curve;
        QVector<double> yData;

        CurveContainer(QColor color) {
            curve.setPen(color, 1.0);
        }

        ~CurveContainer() {
        }

        void update(double data) {
            yData.append(data);
        }
    };

    class MouseMonitorPlot : public QwtPlot
    {
            Q_OBJECT

        private:
            QVector<std::shared_ptr<CurveContainer>> curves;
            QVector<double> xData;

            int xStep;
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

            void updatePlot(QVector<double> data);
            void clearCurves();
            void clear();
            void setDotStyle();

            void addCurve(QColor color);
    };

}

#endif
