#ifndef SETTINGS_DIALOG_H
#define SETTINGS_DIALOG_H

#include <QDialog>
#include <QAbstractButton>

#include "Parameters.h"

#include "ui_dialog.h"

namespace mknap_pso
{

    class SettingsDialog : public QDialog, public Ui_Dialog
    {
            Q_OBJECT
        private:
            Parameters parameters;

        private slots:
            void applyClicked();
            void okayClicked();
            void cancelClicked();

        public:
            SettingsDialog(QWidget *parent = 0);
            ~SettingsDialog();

            Parameters getParameters();
    };

}

#endif
