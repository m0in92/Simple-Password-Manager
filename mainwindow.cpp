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

    // Add Password Option (Password Length) to the Form
    comboBox_passwordLength = new QComboBox();
    comboBox_passwordLength->addItem("8");
    comboBox_passwordLength->addItem("12");
    comboBox_passwordLength->addItem("16");
    comboBox_passwordLength->addItem("20");
    comboBox_passwordLength->addItem("24");
    comboBox_passwordLength->addItem("32");
    comboBox_passwordLength->setCurrentText("16");
    form_layout->addRow("Password Length", comboBox_passwordLength);

    // Add Button to the Form
    button_generate_password = new QPushButton("Generate Password");
    button_generate_password->setShortcut(QKeySequence(Qt::Key_Return));
    form_layout->addRow("", button_generate_password);

    // Group box Containing Form Items
    groupBox_form->setLayout(form_layout);

    // Table View (and the relevant QStandardModel) for Displaing the Stored Passwords
    table_view = new QTableView();
    model_password = new QStandardItemModel();

    update_password_model_from_csv();
    // QStandardItem *item = new QStandardItem("New Item");
    // model_password->setItem(1, 1, item);

    table_view->setModel(model_password);
    table_view->resizeColumnsToContents();

    // Add Widgets to the Main Layout
    hbox->addWidget(groupBox_form);
    hbox->addWidget(table_view);

    // Connection of the signals and slots
    connect(button_generate_password, &QPushButton::clicked, this, &MainWindow::on_button_click);
}

MainWindow::~MainWindow() = default;

void MainWindow::on_button_click()
{
    bool IS_PASSWORD_INCLUDE_SPECIAL = true;

    m_current_service = lineEdit_service->text();
    m_current_username = lineEdit_username->text();

    int len_password = comboBox_passwordLength->currentText().toInt();
    m_current_password = QString::fromStdString(generate_random_password(len_password, IS_PASSWORD_INCLUDE_SPECIAL));

    lineEdit_password->setText(m_current_password);

    store_user_info_to_csv(m_current_service.toStdString(),
                           m_current_username.toStdString(),
                           m_current_password.toStdString());

    update_password_model_from_csv();
    table_view->resizeColumnsToContents();
}

void MainWindow::update_password_model_from_csv()
{
    QFile file_password(QString::fromStdString(DATA_FILE_PATH));

    if (file_password.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file_password);

        int row = 0;
        bool first_row = true;
        while (!in.atEnd())
        {
            QString line = in.readLine();
            QStringList values = line.split(",");

            // Set the First Row as the Heading
            if (first_row)
            {
                model_password->setHorizontalHeaderLabels(values);
                first_row=false;
                continue;
            }

            // Set column count
            if (model_password->columnCount() < values.size())
                model_password->setColumnCount(values.size());

            for (int col = 0; col < values.size(); ++col)
            {
                QStandardItem *item =
                    new QStandardItem(values[col]);

                model_password->setItem(row, col, item);
            }

            row++;
        }

        file_password.close();
    }
}
