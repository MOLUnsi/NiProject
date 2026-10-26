#include "widget.h"
#include "ui_widget.h"

int ProblemNum=1;
bool FillInProblem=1;
bool Random=0;
bool WrongProblemMode=0;
bool TurnToFillInProblem=1;
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle("好好学习，天天向上");
    ui->ProblemViewer->setText(Q1[1]);
    ui->Doing->setText("新题");
    if(FillInProblem)
    {
        ui->InputAnswer->show();
        ui->ChooseA->hide();
        ui->ChooseB->hide();
        ui->ChooseC->hide();
        ui->ChooseD->hide();
    }
    else
    {
        ui->InputAnswer->hide();
        ui->ChooseA->show();
        ui->ChooseB->show();
        ui->ChooseC->show();
        ui->ChooseD->show();
    }
}

bool CheckAnswer(int PbmNum,QString InAns)
{
    QString StdAns;
    if(PbmNum<=100)
    {
        StdAns=A1[PbmNum];
    }
    else
    {
        StdAns=A2[PbmNum-100];
    }
    if(InAns==StdAns)//答案正确
    {
        return true;
    }
    else//答案错误
    {
        QFile file("WrongProblemList.txt");
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)) {
            qDebug() << "无法打开文件:WrongProblemList.txt";
            return false;
        }
        QTextStream out(&file);
        out<<PbmNum<<" ";
        out.flush();
        file.close();
        QMessageBox::information(nullptr,"啊哦~做错了嘻嘻","正确答案：\n"+StdAns+"\n而你的答案：\n"+InAns);
        return false;
    }
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_ChooseA_clicked()
{
    if(CheckAnswer(ProblemNum,"A"))
    {
        on_NextProblem_clicked();
    }
}

void Widget::on_ChooseB_clicked()
{
    if(CheckAnswer(ProblemNum,"B"))
    {
        on_NextProblem_clicked();
    }
}


void Widget::on_ChooseC_clicked()
{
    if(CheckAnswer(ProblemNum,"C"))
    {
        on_NextProblem_clicked();
    }
}


void Widget::on_ChooseD_clicked()
{
    if(CheckAnswer(ProblemNum,"D"))
    {
        on_NextProblem_clicked();
    }
}


void Widget::on_NextProblem_clicked()
{
    ui->InputAnswer->clear();

    if (!WrongProblemMode) {
        // —— 普通模式 ——
        if (!Random) {
            ProblemNum = (ProblemNum >= 200) ? 1 : ProblemNum + 1;
        } else {
            ProblemNum = rand() % 200 + 1;              // 修：不再碰错题集
        }
    } else {
        // —— 错题模式（isEmpty 已在 on_WrongProblems_clicked 拦住） ——
        int idx = WrongProblemsList.indexOf(ProblemNum);
        if (idx < 0) idx = 0;
        if (!Random) {
            idx = (idx + 1) % WrongProblemsList.size();
        } else {
            idx = rand() % WrongProblemsList.size();
        }
        ProblemNum = WrongProblemsList[idx];            // 取出的才是题号
    }

    showProblem(ProblemNum);                            // 见下方抽取
}

void Widget::on_LastProblem_clicked()
{
    ui->InputAnswer->clear();

    if (!WrongProblemMode) {
        if (!Random) {
            ProblemNum = (ProblemNum <= 1) ? 200 : ProblemNum - 1;
        } else {
            ProblemNum = rand() % 200 + 1;
        }
    } else {
        int idx = WrongProblemsList.indexOf(ProblemNum);
        if (idx < 0) idx = 0;
        if (!Random) {
            idx = (idx - 1 + WrongProblemsList.size()) % WrongProblemsList.size();
        } else {
            idx = rand() % WrongProblemsList.size();
        }
        ProblemNum = WrongProblemsList[idx];
    }

    showProblem(ProblemNum);
}

// 把"根据题号显示题目 + 切换控件"抽成一个函数，两处共用，不再重复 30 行
void Widget::showProblem(int num)
{
    if (num <= 100) {
        ui->ProblemViewer->setText(Q1[num]);
        FillInProblem = true;
    } else {
        ui->ProblemViewer->setText(Q2[num - 100]);
        FillInProblem = false;
    }

    ui->InputAnswer->setVisible(FillInProblem);
    ui->ChooseA->setVisible(!FillInProblem);
    ui->ChooseB->setVisible(!FillInProblem);
    ui->ChooseC->setVisible(!FillInProblem);
    ui->ChooseD->setVisible(!FillInProblem);
}

void Widget::on_InputAnswer_returnPressed()
{
    QString InAns=ui->InputAnswer->text();
    if(CheckAnswer(ProblemNum,InAns))
    {
        on_NextProblem_clicked();
    }
}


void Widget::on_NewProblems_clicked()
{
    WrongProblemMode=0;
    ui->Doing->setText("新题");
    ProblemNum=1;
    showProblem(1);
}


void Widget::on_WrongProblems_clicked()
{
    if(WrongProblemsList.size())
    {
        WrongProblemMode=1;
        ui->Doing->setText("错题");
        ProblemNum=WrongProblemsList[0];
        showProblem(WrongProblemsList[0]);
    }
}

void Widget::on_comboBox_2_currentTextChanged(const QString &arg1)
{
    if(arg1=="顺序刷题")
    {
        Random=0;
    }
    else
    {
        Random=1;
    }
}


void Widget::on_comboBox_currentTextChanged(const QString &arg1)
{
    if(arg1=="顺序刷题")
    {
        TurnToFillInProblem=1;
    }
    else
    {
        TurnToFillInProblem=0;
    }
}


void Widget::on_TurnToProblemNum_returnPressed()
{
    QString StrIndex=ui->TurnToProblemNum->text();
    int index=StrIndex.toInt();
    if(!TurnToFillInProblem)
        index+=100;
    ProblemNum=index;
    showProblem(index);
    ui->TurnToProblemNum->clear();
}


void Widget::on_WrongProblemsList_clicked()
{
    /*
    QFile file("WrongProblemList.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "无法打开文件:WrongProblemList.txt";
        return;
    }
    QTextStream out(&file);
    for(int i=0;i<WrongProblemsList.size();i++)
    {
        out<<WrongProblemsList[i]<<" ";
    }
    file.close();*/
    QFileInfo fi("WrongProblemList.txt");
    QDesktopServices::openUrl(QUrl::fromLocalFile(fi.absoluteFilePath()));
    //QProcess::execute("start calc");
    //reload
    QVector<int> NewVector;
    WrongProblemsList.swap(NewVector);
    QFile file3("WrongProblemList.txt");
    if (!file3.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "无法打开文件:WrongProblemList.txt";
        return;
    }
    QTextStream in3(&file3);
    QSet<int>s;
    int x=0;
    while(in3>>x)
    {
        if(x>=1&&x<=200)
        {
            s.insert(x);
        }
    }
    file3.close();
    WrongProblemsList=s.values();
    std::sort(WrongProblemsList.begin(),WrongProblemsList.end());
}

