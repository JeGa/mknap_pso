#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QWidget>

#include "ui_mainwindow.h"

namespace mknap_pso
{

    class MainWindow : public QMainWindow, public Ui_MainWindow
    {
            Q_OBJECT

        private:

        public:
            MainWindow(QWidget *parent = 0);
            virtual ~MainWindow();
    };

}

#endif
