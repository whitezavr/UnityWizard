#include <QApplication>

#include <unity_wizard.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    UnityWizard *pUnityWizard;
    pUnityWizard = new UnityWizard;
    pUnityWizard->show();

    return a.exec();
}
