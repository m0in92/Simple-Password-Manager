/**
 * @file mainwindow.h
 * @brief Qt Widget Application for the Password Manager Dialog
 * @author Moin Ahmed
 * @date 2026
 *
 *
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QGroupBox>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>

#include <QTableView>
#include <QStandardItemModel>
#include <QFile>
#include <QTextStream>

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
    QComboBox *comboBox_passwordLength;
    QPushButton *button_generate_password;

    QTableView *table_view;
    QStandardItemModel *model_password;

    QString m_current_service;
    QString m_current_username;
    QString m_current_password;

    // Private Methods
    void update_password_model_from_csv();
};
#endif // MAINWINDOW_H
