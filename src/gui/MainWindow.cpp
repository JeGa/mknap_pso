#include "MainWindow.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QTableWidgetItem>
#include <QTableWidget>

namespace mknap_pso
{

    MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
    {
        setupUi(this);

        connect(actionOpen_mknap_file, SIGNAL(triggered()), this, SLOT(openFile()));
        connect(actionExit, SIGNAL(triggered()), this, SLOT(close()));
        connect(actionAbout, SIGNAL(triggered()), this, SLOT(about()));
        connect(solveBtn, SIGNAL(clicked()), this, SLOT(solveBtnClicked()));
        connect(table, SIGNAL(itemClicked(QTableWidgetItem *)), this, SLOT(tableItemClicked(QTableWidgetItem *)));
        connect(actionSet_parameter, SIGNAL(triggered()), this, SLOT(openSettingsDialog()));

        consoleEdit->append("> Choose file with multidimensional (multi-constraint) knapsack problem to solve.");

        settingsDialog = new SettingsDialog();
        plot = new minotaur::MouseMonitorPlot();
        plot->init(Qt::blue, "Global best fitness value", "Iteration", "Fitness value");
        graphLayout->layout()->addWidget(plot);
    }

    MainWindow::~MainWindow()
    {
        delete settingsDialog;
        delete plot;
    }

    void MainWindow::solveBtnClicked()
    {
        //for (auto &i : parser.getProblems()) {

        plot->clear();

        solver.setParameters(settingsDialog->getParameters());

        QList<QTableWidgetItem *> items = table->selectedItems();
        if (items.size() >= 1) {
            int row = items.at(0)->row();

            QString outTxt = "> Solving problem " + QString::number(row);
            consoleEdit->append(outTxt);

            solver.startSolveProblem(parser.getProblemsReference().at(row));

            for (int i = 0; i < 400; ++i) {
                int gBest = solver.solveProblemIteration();

                QString outTxt = "> Iteration: " + QString::number(i+1) + " Value: " + QString::number(gBest);
                consoleEdit->append(outTxt);

                plot->updatePlot(gBest);
            }

            solver.stopSolveProblem();
        }
    }

    void MainWindow::openFile()
    {
        QString fileName = QFileDialog::getOpenFileName(this,
                           tr("Open mknap problem file"), "", tr("Problem files (*.txt)"));

        parser.parseFile(fileName.toStdString());
        consoleEdit->append("> Parsed mknap problem file");

        nrOfProblemsEdit->setText(QString::number(parser.getProblemsReference().size()));
        fileNameEdit->setText(fileName);

        table->clear();
        table->setRowCount(0);
        table->setColumnCount(0);

        tableDetail->clear();
        tableDetail->setRowCount(0);
        tableDetail->setColumnCount(0);

        QStringList headerLabels;
        headerLabels << "Problem" << "Elements" << "Constraints" << "Solution";
        table->setColumnCount(4);
        table->setHorizontalHeaderLabels(headerLabels);
        table->setEditTriggers(QAbstractItemView::NoEditTriggers);
        table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

        int counter = 0;
        for (auto i : parser.getProblemsReference()) {
            table->insertRow(table->rowCount());
            table->setItem(table->rowCount() - 1, 0, new QTableWidgetItem(QString::number(counter++)));
            table->setItem(table->rowCount() - 1, 1, new QTableWidgetItem(QString::number(i->n)));
            table->setItem(table->rowCount() - 1, 2, new QTableWidgetItem(QString::number(i->m)));
            table->setItem(table->rowCount() - 1, 3, new QTableWidgetItem(QString::number(i->solution)));
        }
    }

    void MainWindow::tableItemClicked(QTableWidgetItem *item)
    {
        tableDetail->clear();
        tableDetail->setRowCount(0);
        tableDetail->setColumnCount(0);

        std::shared_ptr<KnapsackProblem> problem = parser.getProblemsReference().at(item->row());

        tableDetail->setRowCount(problem->m + 1);
        QStringList headerLabels;
        headerLabels << "Profit";
        for (int i = 0; i < (problem->m); i++) {
            QString label = "Constraint " + QString::number(i) + " (Capacity: " + QString::number(problem->capacity.at(i)) + ")";
            headerLabels << label;
        }
        tableDetail->setVerticalHeaderLabels(headerLabels);

        int j = 0;
        for (auto &profit : problem->profit) {
            tableDetail->insertColumn(tableDetail->columnCount());
            tableDetail->setItem(0, tableDetail->columnCount() - 1, new QTableWidgetItem(QString::number(profit)));

            int i = 0;
            for (auto &constraint : problem->constraint) {
                tableDetail->setItem(i + 1, tableDetail->columnCount() - 1, new QTableWidgetItem(QString::number(constraint.at(j))));
                ++i;
            }

            ++j;
        }
    }

    void MainWindow::openSettingsDialog()
    {
        settingsDialog->setVisible(true);
    }

    void MainWindow::about()
    {
        QMessageBox::about(this, tr("About mknap_pso"),
                           tr("This application solves the mknap problem with pso."));
    }

}
