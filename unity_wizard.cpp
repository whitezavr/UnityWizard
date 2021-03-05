#include "unity_wizard.h"

IntroPage::IntroPage()
{
    setSubTitle("этот wizard поможет вам создать шаблон файла, "
             "который будет содержать тест-кейсы (для тестовоого окружения Unity)");
}

FinishPage::FinishPage()
{ setSubTitle("нажмите финиш и шаблон будет создан!"); }


EnterDataPage::EnterDataPage()
{
    setSubTitle("введение данных");

    nameLabel = new QLabel("название тестовой группы:");
    name = new QLineEdit;

    includeFileLabel = new QLabel("включить следующий файл:");
    includeFile = new QLineEdit;

    directoryOutTest = new QLineEdit;
    directoryOutTestRunner = new QLineEdit;
    directoryOutButton = new QPushButton("сохранить шаблон...");

    registerField("name", name);
    registerField("includeFileName", includeFile);
    registerField("directoryTest", directoryOutTest);
    registerField("directoryTestRunner", directoryOutTestRunner);

    connect(directoryOutButton, SIGNAL(clicked(bool)),
            this, SLOT(receiveDirectoryOut(bool)));

    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(nameLabel, 0, 0);
    gridLayout->addWidget(name, 0, 1);
    gridLayout->addWidget(includeFileLabel, 1, 0);
    gridLayout->addWidget(includeFile, 1, 1);

    QVBoxLayout *vBox = new QVBoxLayout;
    vBox->addWidget(directoryOutTest);
    vBox->addWidget(directoryOutTestRunner);
    QHBoxLayout *hlayerDirectory = new QHBoxLayout;
    hlayerDirectory->addLayout(vBox);
    hlayerDirectory->addWidget(directoryOutButton);

    QVBoxLayout *mainlayer = new QVBoxLayout;
    mainlayer->addLayout(gridLayout);
    mainlayer->addLayout(hlayerDirectory);

    setLayout(mainlayer);
}

void EnterDataPage::initializePage()
{
    name->setText("");
    includeFile->setText("");
    directoryOutTest->setText("./");
    directoryOutTestRunner->setText("./");
}

bool EnterDataPage::validatePage()
{

}

void EnterDataPage::receiveDirectoryOut(bool clicked)
{
    QString directoryOut = QFileDialog::getSaveFileName(this,
                                           tr("сохранить файл шаблона как:"),
                                           "./" + name->text());

    directoryOutTest->setText(directoryOut + "Test.c");
    directoryOutTestRunner->setText(directoryOut + "TestRunner.c");
}


UnityWizard::UnityWizard()
{
    setWindowTitle("Unity Wizard v1.0");

    QRect rect(50, 20, 100, 330);
    QPixmap originalPixmap(":/pictures/logo1.jpg");
    QPixmap pixmap = originalPixmap.copy(rect);

    setWizardStyle(QWizard::ClassicStyle);
    setPixmap(QWizard::WatermarkPixmap,pixmap);

    addPage(new IntroPage);
    addPage(new EnterDataPage);
    addPage(new FinishPage);

    show();
}

void UnityWizard::accept()
{
    QString name = field("name").toString();
    QByteArray includeFileName = field("includeFileName").toByteArray();
    QString directoryOutTest = field("directoryTest").toString();
    QString directoryOutTestRunner = field("directoryTestRunner").toString();

    QByteArray block;

    block += "#include \"unity_fixture.h\"\n";
    block += "#include <stdio.h>\n";
    block += "#include \"" + includeFileName + "\"\n";
    block += "#include \"RuntimeErrorStub.h\"\n";
    block += "#include \"RuntimeError.h\"\n\n";

    block += "TEST_GROUP(" + name.toLatin1() + ");\n\n";

    block += "TEST_SETUP(" + name.toLatin1() + ")\n{\n\n}\n\n";

    block += "TEST_TEAR_DOWN(" + name.toLatin1() + ")\n{\n\n}\n\n";

    block += "TEST(" + name.toLatin1() + ", )\n{\n\n}\n\n";

    QFile testFile(directoryOutTest);
    if (!testFile.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(0, QObject::tr("Unity Wizard"),
                             QObject::tr("Cannot write file %1")
                             .arg(directoryOutTest));
        return;
    }
    testFile.write(block);
    testFile.close();

    block.clear();

    block += "#include \"unity_fixture.h\"\n\n";
    block += "TEST_GROUP_RUNNER(" + name.toLatin1() + ")\n{\n";
    for (int i = 0; i < 40; i++)
    { block += "//\tRUN_TEST_CASE(" + name.toLatin1() + ", );\n"; }
    block += "}\n";

    QFile testRunnerFile(directoryOutTestRunner);
    if (!testRunnerFile.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(0, QObject::tr("Unity Wizard"),
                             QObject::tr("Cannot write file %1")
                             .arg(directoryOutTestRunner));
        return;
    }
    testRunnerFile.write(block);
    testRunnerFile.close();

    QDialog::accept();
}
