#include "SettingsDialog.h"

namespace mknap_pso
{

    SettingsDialog::SettingsDialog(QWidget *parent) : QDialog(parent)
    {
        setupUi(this);

        //QPushButton *b = buttonBox->button(QDialogButtonBox::Apply);
        //connect(b, SIGNAL(clicked()), this, SLOT(applyClicked()));

        connect(buttonBox, SIGNAL(accepted()), this, SLOT(okayClicked()));
        connect(buttonBox, SIGNAL(rejected()), this, SLOT(cancelClicked()));

        parameters = Parameters::getDefaultParameters();
    }

    SettingsDialog::~SettingsDialog()
    {
    }

    void SettingsDialog::applyClicked()
    {
        int nrOfParticles = nrOfParticlesEdit->text().toInt();
        int constant1 = constant1Edit->text().toInt();
        int constant2 = constant2Edit->text().toInt();
        int iterations = iterationsEdit->text().toInt();

        parameters.set(nrOfParticles,
                       constant1,
                       constant2,
                       iterations);
    }

    void SettingsDialog::okayClicked()
    {
        int nrOfParticles = nrOfParticlesEdit->text().toInt();
        int constant1 = constant1Edit->text().toInt();
        int constant2 = constant2Edit->text().toInt();
        int iterations = iterationsEdit->text().toInt();

        parameters.set(nrOfParticles,
                       constant1,
                       constant2,
                       iterations);

        close();
    }

    void SettingsDialog::cancelClicked()
    {
        close();
        // TODO: hide()
    }

    Parameters SettingsDialog::getParameters()
    {
        return parameters;
    }

}
