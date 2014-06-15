#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "Solver.h"
#include "Parser.h"
#include "SettingsDialog.h"
#include "MouseMonitorPlot.h"

#include <QMainWindow>
#include <QWidget>
#include <QtConcurrent/QtConcurrent>

#include "ui_mainwindow.h"

namespace mknap_pso
{

    class MainWindow : public QMainWindow, public Ui_MainWindow
    {
            Q_OBJECT

        private:
            mknap_pso::Solver solver;
            mknap_pso::Parser parser;

            SettingsDialog *settingsDialog;

            minotaur::MouseMonitorPlot *plot;
            minotaur::MouseMonitorPlot *swarmPlot;

            QFuture<int> future;

            void printSwarmToConsole(Swarm &swarm);
            void printSwarmToTable(Swarm &swarm);
            QString getPositionString(Solution &position);
            QString getVelocityString(Velocity &velocity);
            void initSwarmtable();
            int runFunction();

        private slots:
            void solveBtnClicked();
            void openFile();
            void about();
            void tableItemClicked(QTableWidgetItem *item);
            void openSettingsDialog();

            void toolbarStart();
            int toolbarStop();
            void toolbarNext();

        public:
            MainWindow(QWidget *parent = 0);
            virtual ~MainWindow();
    };

}

#endif
