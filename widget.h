#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QMessageBox>
#include <QProcess>
#include <QDir>
#include <QDesktopServices>

extern QString A1[105],A2[105],Q1[105],Q2[105];
extern bool FillInProblem;
extern QVector<int>WrongProblemsList;

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}

QT_END_NAMESPACE
class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget() override;

private slots:
    void on_ChooseA_clicked();

    void on_ChooseB_clicked();

    void on_ChooseC_clicked();

    void on_ChooseD_clicked();

    void on_LastProblem_clicked();

    void on_NextProblem_clicked();

    void on_InputAnswer_returnPressed();

    void on_NewProblems_clicked();

    void on_WrongProblems_clicked();

    void showProblem(int);

    void on_comboBox_2_currentTextChanged(const QString &arg1);

    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_TurnToProblemNum_returnPressed();

    void on_WrongProblemsList_clicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
