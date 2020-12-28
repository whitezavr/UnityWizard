#ifndef UNITY_WIZARD_H
#define UNITY_WIZARD_H

#include "declarations.h"

class IntroPage: public QWizardPage
{
    Q_OBJECT

public:
    IntroPage();
};

class FinishPage: public QWizardPage
{
    Q_OBJECT

public:
    FinishPage();
};


class EnterDataPage: public QWizardPage
{
    Q_OBJECT

public:
    EnterDataPage();

protected:
    void initializePage() Q_DECL_OVERRIDE;
    bool validatePage() Q_DECL_OVERRIDE;

private:

    QLabel *nameLabel;
    QLineEdit *name;

    QLabel *includeFileLabel;
    QLineEdit *includeFile;

    QLineEdit *directoryOutTest;
    QLineEdit *directoryOutTestRunner;
    QPushButton *directoryOutButton;

public slots:
    void receiveDirectoryOut(bool clicked);
};


class UnityWizard : public QWizard
{
public:
    UnityWizard();
    void accept() Q_DECL_OVERRIDE;
};



#endif // UNITY_WIZARD_H
