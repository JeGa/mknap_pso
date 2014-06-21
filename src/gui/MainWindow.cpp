#include "MainWindow.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QTableWidgetItem>
#include <QTableWidget>
#include <QTime>

#include <stdexcept>
#include <iostream>
#include <ctime>

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
        connect(actionStart, SIGNAL(triggered()), this, SLOT(toolbarStart()));
        connect(actionStop, SIGNAL(triggered()), this, SLOT(toolbarStop()));
        connect(actionNext_Iteration, SIGNAL(triggered()), this, SLOT(toolbarNext()));
        connect(actionDo_pre_defined_test, SIGNAL(triggered()), this, SLOT(preDefinedTestClicked()));

        consoleEdit->append("> Choose file with multidimensional (multi-constraint) knapsack problem to solve.");

        settingsDialog = new SettingsDialog();
        plot = new minotaur::MouseMonitorPlot();
        plot->init(Qt::blue, "Global best fitness value", "Iteration", "Fitness value");
        graphLayout->layout()->addWidget(plot);

        swarmPlot = new minotaur::MouseMonitorPlot();
        swarmPlot->init(Qt::blue, "Particle best fitness value", "Iteration", "Fitness value");
        swarmTab->layout()->addWidget(swarmPlot);
        swarmPlot->setDotStyle();

        future = QtConcurrent::run(this, &MainWindow::runFunction);
    }

    MainWindow::~MainWindow()
    {
        delete settingsDialog;
        delete plot;
    }

    int MainWindow::runFunction()
    {
        return solver.solveProblemIteration();
    }

    void MainWindow::toolbarStart()
    {
        plot->clear();
        consoleEdit->clear();
        solver.setParameters(settingsDialog->getParameters());

        swarmPlot->clearCurves();
        std::srand(std::time(0));
        for (int i = 0; i < settingsDialog->getParameters().getNumberOfParticles(); ++i) {
            swarmPlot->addCurve(QColor((std::rand() % (255 + 1)),
                                       (std::rand() % (255 + 1)),
                                       (std::rand() % (255 + 1))));
        }

        QList<QTableWidgetItem *> items = table->selectedItems();
        if (items.size() >= 1) {
            int row = items.at(0)->row();

            solver.startSolveProblem(parser.getProblemsReference().at(row));

            consoleEdit->append("==================================");
            QString outTxt = "> Solving problem " + QString::number(row) + ":";
            consoleEdit->append(outTxt);
            printSwarmToConsole(solver.getSwarmReference());
            consoleEdit->append("==================================");

            printSwarmToTable(solver.getSwarmReference());
        }
    }

    int MainWindow::toolbarStop()
    {
        if (!solver.isSolving())
            return -1;

        int gBest = solver.stopSolveProblem();

        QString outTxt = "> FINAL SOLUTION VALUE: " + QString::number(gBest);
        consoleEdit->append(outTxt);
        consoleEdit->append("==================================");

        return gBest;
    }

    void MainWindow::toolbarNext()
    {
        if (!solver.isSolving())
            return;

        consoleEdit->append("----------------------------------");

        int gBest = runFunction();//future.result();

        printSwarmToTable(solver.getSwarmReference());
        printSwarmToConsole(solver.getSwarmReference());

        QString outTxt = "> gBest value: " + QString::number(gBest);
        consoleEdit->append(outTxt);

        QVector<double> data;
        data.append(gBest);
        plot->updatePlot(data);

        QVector<double> dataSwarm;
        for (auto &i : solver.getSwarmReference().getParticles())
            dataSwarm.append(i.getBestValue());
        swarmPlot->updatePlot(dataSwarm);
    }

    void MainWindow::solveBtnClicked()
    {
        toolbarStart();
        for (int i = 0; i < settingsDialog->getParameters().getIterations(); ++i) {
            QString outTxt = "> Iteration: " + QString::number(i);
            consoleEdit->append(outTxt);
            toolbarNext();
        }
        toolbarStop();
    }

    void MainWindow::openFile()
    {
        QString fileName = QFileDialog::getOpenFileName(this,
                           tr("Open mknap problem file"), "", tr("Problem files (*.txt)"));

        if (fileName == "")
            return;

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
                           "This application solves the mknap problem with discrete binary Particle Swarm Optimization.\n\n"
                           "Author: JeGa\n"
                           "Github: https://github.com/JeGa/mknap_pso");
    }

    void MainWindow::printSwarmToConsole(Swarm &swarm)
    {
        int counter = 0;
        for (auto &i : swarm.getParticles()) {
            QString outTxt = "> Particle " + QString::number(counter) + ":";
            consoleEdit->append(outTxt);

            consoleEdit->append(getPositionString(i.getPosition()));

            consoleEdit->append("Velocity: ");
            consoleEdit->append(getVelocityString(i.getVelocity()));

            outTxt = "=> pBest " + QString::number(i.getBestValue());
            consoleEdit->append(outTxt);

            ++counter;
        }
    }

    void MainWindow::initSwarmtable()
    {
        swarmTable->clear();
        swarmTable->setRowCount(0);
        swarmTable->setColumnCount(0);

        QStringList headerLabels;
        headerLabels << "Particle" << "pBest" << "pBest position" << "Position" << "Velocity";
        swarmTable->setColumnCount(5);
        swarmTable->setHorizontalHeaderLabels(headerLabels);
        swarmTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    }

    void MainWindow::printSwarmToTable(Swarm &swarm)
    {
        initSwarmtable();

        swarmParticlesEdit->setText(QString::number(swarm.getParticles().size()));
        swarmPBestEdit->setText(QString::number(swarm.getBestValue()));

        QString outText;
        Solution &position = swarm.getBestPosition();
        for (auto i : position)
            outText += QString::number(i);
        swarmPBestPositionEdit->setText(outText);

        int counter = 0;
        for (auto &i : swarm.getParticles()) {
            swarmTable->insertRow(swarmTable->rowCount());
            swarmTable->setItem(swarmTable->rowCount() - 1, 0, new QTableWidgetItem(QString::number(counter++)));
            swarmTable->setItem(swarmTable->rowCount() - 1, 1, new QTableWidgetItem(QString::number(i.getBestValue())));
            swarmTable->setItem(swarmTable->rowCount() - 1, 2, new QTableWidgetItem(getPositionString(i.getBestPosition())));
            swarmTable->setItem(swarmTable->rowCount() - 1, 3, new QTableWidgetItem(getPositionString(i.getPosition())));
            swarmTable->setItem(swarmTable->rowCount() - 1, 4, new QTableWidgetItem(getVelocityString(i.getVelocity())));
        }
    }

    QString MainWindow::getPositionString(Solution &position)
    {
        QString outText;
        for (auto i : position)
            outText += QString::number(i);
        return outText;
    }

    QString MainWindow::getVelocityString(Velocity &velocity)
    {
        QString outText;
        for (auto i : velocity)
            outText += QString::number(i) + ",";
        return outText;
    }

    //================================================================

    void MainWindow::preDefinedTestClicked()
    {
        consoleEdit->clear();

        // Problem 1

        consoleEdit->append("===================================");
        consoleEdit->append("Problem 1");
        consoleEdit->append("===================================");

        consoleEdit->append(doTest(0, 30, 100000, 1.0, 10.0, 1.0, 6.0));

        // TODO
        return;

        // Change particle number
        consoleEdit->append(doTest(0, 5, 500, 1.0, 2.0, 2.0, 6.0));
        consoleEdit->append(doTest(0, 10, 500, 1.0, 2.0, 2.0, 6.0));
        consoleEdit->append(doTest(0, 15, 500, 1.0, 2.0, 2.0, 6.0));
        consoleEdit->append(doTest(0, 20, 500, 1.0, 2.0, 2.0, 6.0));
        consoleEdit->append(doTest(0, 25, 500, 1.0, 2.0, 2.0, 6.0));
        consoleEdit->append(doTest(0, 30, 500, 1.0, 2.0, 2.0, 6.0));

        // Change inertia
        consoleEdit->append(doTest(0, 20, 500, 0.1, 2.0, 2.0, 6.0));
        consoleEdit->append(doTest(0, 20, 500, 0.5, 2.0, 2.0, 6.0));
        consoleEdit->append(doTest(0, 20, 500, 0.8, 2.0, 2.0, 6.0));
        consoleEdit->append(doTest(0, 20, 500, 0.9, 2.0, 2.0, 6.0));
        consoleEdit->append(doTest(0, 20, 500, 1.0, 2.0, 2.0, 6.0));
        consoleEdit->append(doTest(0, 20, 500, 1.1, 2.0, 2.0, 6.0));
        consoleEdit->append(doTest(0, 20, 500, 1.2, 2.0, 2.0, 6.0));
        consoleEdit->append(doTest(0, 20, 500, 1.5, 2.0, 2.0, 6.0));

        // Change c1 / c2
        consoleEdit->append(doTest(0, 20, 500, 1.0, 0.1, 1.0, 6.0));
        consoleEdit->append(doTest(0, 20, 500, 1.0, 0.5, 1.0, 6.0));
        consoleEdit->append(doTest(0, 20, 500, 1.0, 1.0, 1.0, 6.0));
        consoleEdit->append(doTest(0, 20, 500, 1.0, 2.0, 1.0, 6.0));
        consoleEdit->append(doTest(0, 20, 500, 1.0, 3.0, 1.0, 6.0));
        consoleEdit->append(doTest(0, 20, 500, 1.0, 5.0, 1.0, 6.0));
        consoleEdit->append(doTest(0, 20, 500, 1.0, 10.0, 1.0, 6.0));

        consoleEdit->append(doTest(0, 20, 500, 1.0, 1.0, 0.1, 6.0));
        consoleEdit->append(doTest(0, 20, 500, 1.0, 1.0, 1.0, 6.0));
        consoleEdit->append(doTest(0, 20, 500, 1.0, 1.0, 5.0, 6.0));

        // Change vMax
        consoleEdit->append(doTest(0, 20, 500, 1.0, 2.0, 2.0, 0.1));
        consoleEdit->append(doTest(0, 20, 500, 1.0, 2.0, 2.0, 0.5));
        consoleEdit->append(doTest(0, 20, 500, 1.0, 2.0, 2.0, 1.0));
        consoleEdit->append(doTest(0, 20, 500, 1.0, 2.0, 2.0, 2.0));
        consoleEdit->append(doTest(0, 20, 500, 1.0, 2.0, 2.0, 3.0));
        consoleEdit->append(doTest(0, 20, 500, 1.0, 2.0, 2.0, 4.0));
        consoleEdit->append(doTest(0, 20, 500, 1.0, 2.0, 2.0, 5.0));
        consoleEdit->append(doTest(0, 20, 500, 1.0, 2.0, 2.0, 10.0));
        consoleEdit->append(doTest(0, 20, 500, 1.0, 2.0, 2.0, 20.0));
    }

    QString MainWindow::doTest(int problem, int particles,
                               int iterations, double inertia,
                               double c1, double c2, double vMax)
    {
        int globalIt = 30;
        int gBest, best = INT32_MIN, worse = INT32_MAX;
        int meanOptimumSum = 0, meanTimeSum = 0;
        QString str;
        QTime t;

        Parameters p;
        p.set(particles, iterations, inertia, c1, c2, vMax);
        solver.setParameters(p);

        for (int j = 0; j < globalIt; ++j) {

            t.start();

            solver.startSolveProblem(parser.getProblemsReference().at(problem));
            for (int i = 0; i < p.getIterations(); ++i)
                runFunction();
            gBest = solver.stopSolveProblem();

            if (gBest > best)
                best = gBest;
            if (gBest < worse)
                worse = gBest;

            meanOptimumSum += gBest;
            meanTimeSum += t.elapsed();
        }
        str = "Mean of " + QString::number(globalIt) + " iterations -> (" + p.toString() + ") " +
              "Best value: " + QString::number(best) + ", Worst value: " + QString::number(worse) +
              " Mean Optimum: " + QString::number((double) meanOptimumSum / globalIt) +
              " Mean Time (ms): " + QString::number((double) meanTimeSum / globalIt);
        return str;
    }

}
