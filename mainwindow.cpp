#include "mainwindow.h"

#include "password_manager.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle("Password Manager");
    resize(640, 480);

    central_widget = new QWidget(this);
    this->setCentralWidget(central_widget);

    // Main Layout
    hbox = new QHBoxLayout;
    central_widget->setLayout(hbox);

    // GroupBox around the Form
    groupBox_form = new QGroupBox;

    // Add Input Fields to the Form
    lineEdit_service = new QLineEdit;
    lineEdit_username = new QLineEdit;
    lineEdit_password = new QLineEdit;

    lineEdit_service->setPlaceholderText("e.g. Gmail");
    lineEdit_username->setPlaceholderText("e.g. user@example.com");
    lineEdit_password->setReadOnly(true);

    form_layout = new QFormLayout;
    form_layout->addRow("Service", lineEdit_service);
    form_layout->addRow("Username/Password", lineEdit_username);
    form_layout->addRow("Password", lineEdit_password);

    // Add Button to the Form
    button_generate_password = new QPushButton("Generate Password");
    button_generate_password->setShortcut(QKeySequence(Qt::Key_Return));
    form_layout->addRow("", button_generate_password);

    // Group box
    groupBox_form->setLayout(form_layout);
    hbox->addWidget(groupBox_form);

    // Connection of the signals and slots
    connect(button_generate_password, &QPushButton::clicked, this, &MainWindow::on_button_click);
}

MainWindow::~MainWindow() = default;

void MainWindow::on_button_click()
{
    int PASSWORD_LEN = 16;
    bool IS_PASSWORD_INCLUDE_SPECIAL = true;

    m_current_service = lineEdit_service->text();
    m_current_username = lineEdit_username->text();
    m_current_password = QString::fromStdString(generate_random_password(PASSWORD_LEN, IS_PASSWORD_INCLUDE_SPECIAL));

    lineEdit_password->setText(m_current_password);

    store_user_info_to_csv(m_current_service.toStdString(),
                           m_current_username.toStdString(),
                           m_current_password.toStdString());
}
