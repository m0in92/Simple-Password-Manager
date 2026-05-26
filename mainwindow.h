#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QGroupBox>
#include <QLineEdit>
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

public slots:
    void on_button_click();

private:
    QWidget *central_widget;
    QHBoxLayout *hbox;
    QGroupBox *groupBox_form;
    QFormLayout *form_layout;
    QLineEdit *lineEdit_service;
    QLineEdit *lineEdit_username;
    QLineEdit *lineEdit_password;
    QPushButton *button_generate_password;

    QString m_current_service;
    QString m_current_username;
    QString m_current_password;
};
#endif // MAINWINDOW_H
