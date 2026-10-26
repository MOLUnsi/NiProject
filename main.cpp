#include "widget.h"

#include <QApplication>
QString A1[105],A2[105],Q1[105],Q2[105];
QVector<int>WrongProblemsList;


void init()
{
    srand(time(0));
//输入填空题题库
    int a1=1,a2=1,q1=1,q2=1;
    QFile file1("list1.txt");
    QTextStream in1(&file1);
    if (!file1.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "无法打开文件:list1.txt";
        return;
    }
    while(!in1.atEnd())
    {
        QString line=in1.readLine();
        if(line[0]=='#')
        {
            for(;;)
            {
                QString l=in1.readLine();
                if(l[0]=='#')
                {
                    q1++;
                    break;
                }
                Q1[q1]=Q1[q1]+l+'\n';
            }
        }
        if(line[0]=='$')
        {
            QString l=in1.readLine();
            A1[a1++]=l;
            l=in1.readLine();
        }
    }
    file1.close();
//输入选择题题库
    QFile file2("list2.txt");
    if (!file2.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "无法打开文件:list2.txt";
        return;
    }
    QTextStream in2(&file2);
    while(!in2.atEnd())
    {
        QString line=in2.readLine();
        if(line[0]=='#')
        {
            for(;;)
            {
                QString l=in2.readLine();
                if(l[0]=='#')
                {
                    q2++;
                    break;
                }
                Q2[q2]=Q2[q2]+l+'\n';
            }
        }
        if(line[0]=='$')
        {
            QString l=in2.readLine();
            A2[a2++]=l;
            l=in2.readLine();
        }
    }
    file2.close();
//输入错题集
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
int main(int argc, char *argv[])
{
    init();
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return QApplication::exec();
}
