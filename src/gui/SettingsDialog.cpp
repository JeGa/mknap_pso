#include "SettingsDialog.h"

namespace mknap_pso
{

    SettingsDialog::SettingsDialog(QWidget *parent) : QDialog(parent)
    {
        setupUi(this);

        connect(buttonBox, SIGNAL(clicked(QAbstractButton *)), this, SLOT(buttonBoxClicked(QAbstractButton *)));
        connect(buttonBox, SIGNAL(accepted()), this, SLOT(okayClicked()));
        connect(buttonBox, SIGNAL(rejected()), this, SLOT(cancelClicked()));

        parameters = Parameters::getDefaultParameters();
        displayParameters();
    }

    SettingsDialog::~SettingsDialog()
    {
    }

    void SettingsDialog::buttonBoxClicked(QAbstractButton *button)
    {
        if (buttonBox->standardButton(button) == QDialogButtonBox::Apply)
            saveParameters();
    }

    void SettingsDialog::okayClicked()
    {
        saveParameters();

        close();
    }

    void SettingsDialog::cancelClicked()
    {
        close();
    }

    void SettingsDialog::saveParameters()
    {
        int nrOfParticles = nrOfParticlesEdit->text().toInt();
        int iterations = iterationsEdit->text().toInt();
        double inertiaWeight = inertiaWeightEdit->text().toDouble();
        double constant1 = constant1Edit->text().toDouble();
        double constant2 = constant2Edit->text().toDouble();
        double vMax = vMaxEdit->text().toDouble();

        parameters.set(nrOfParticles,
                       iterations,
                       inertiaWeight,
                       constant1,
                       constant2,
                       vMax);
    }

    void SettingsDialog::displayParameters()
    {
        nrOfParticlesEdit->setText(QString::number(parameters.getNumberOfParticles()));
        iterationsEdit->setText(QString::number(parameters.getIterations()));
        inertiaWeightEdit->setText(QString::number(parameters.getInertiaWeight()));
        constant1Edit->setText(QString::number(parameters.getConstant1()));
        constant2Edit->setText(QString::number(parameters.getConstant2()));
        vMaxEdit->setText(QString::number(parameters.getVMax()));
    }

    Parameters SettingsDialog::getParameters()
    {
        return parameters;
    }

}
