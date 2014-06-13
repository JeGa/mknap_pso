#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "Solver.h"
#include "Parser.h"

#include <QMainWindow>
#include <QWidget>

#include "ui_mainwindow.h"

namespace mknap_pso
{

    class MainWindow : public QMainWindow, public Ui_MainWindow
    {
            Q_OBJECT

        private:
            mknap_pso::Solver solver;
            mknap_pso::Parser parser;

        private slots:
            void solveBtnClicked();
            void openFile();
            void about();
            void tableItemClicked(QTableWidgetItem *item);

        public:
            MainWindow(QWidget *parent = 0);
            virtual ~MainWindow();
    };

}

#endif
