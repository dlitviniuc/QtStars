#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QFile>
#include <QBarSet>
#include <QBarSeries>
#include <QValueAxis>
#include <QBarCategoryAxis>
#include <QPieSeries>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    QFile file1("lista1.txt");
    QFile file2("lista2.txt");
    if(file1.exists() && file2.exists()){
        load();
    }else{
        connect(&manager, &QNetworkAccessManager::finished, this, &MainWindow::scaricato);
        download(0);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::download(int num){
    QNetworkRequest request(Url[num]);
    request.setRawHeader("Content-Type", "text");
    manager.get(request);
    //qDebug() << "download " << num;
}


void MainWindow::scaricato(QNetworkReply *reply){
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray response(reply->readAll());
        QFile file(files[num]);
        if(file.open(QIODevice::WriteOnly)){
            file.write(response);
            num++;
            file.close();
        }
        response.clear();
        if(num == 2){
            num = 0;
        }
    }
    reply->deleteLater();
    if(num == 1){
        download(num);
    }
    else{
        if(num == 0){
            load();
        }
        return;
    }

}

void MainWindow::load(){
    ui->labelEmi->setFont(QFont ("Times", 20, QFont::Bold));
    ui->labelUni->setFont(QFont ("Times", 20, QFont::Bold));
    readFile(files[0], &uni);
    showList(&uni, ui->uniView);
    //qDebug() << "lista1 " << uni.size();
    readFile(files[1], &emi);
    showList(&emi, ui->emiView);
    //qDebug() << "lista2 " << emi.size();
    grafoElenco(&uni, ui->BarUni);
    grafoElenco(&emi, ui->BarEmi);
    grafoTot();
}


void MainWindow::readFile(QString file_name, std::vector<artista> *lista){
    QFile file(file_name);
    //qDebug() << "entrato readFile " << file_name;
    if(file.open(QIODevice::ReadOnly))
    {
        //qDebug() << "file open " << file_name;
        QTextStream in(&file);
        while(!in.atEnd()){
            QString riga = in.readLine();
            QStringList ele = riga.split(' ');
            QString link = ele.at(0);
            if(ele.size()==1)
                ele.append("NoName");
            QString nome = ele.at(1);
            nome.replace("_", " ");
            //qDebug() << nome;
            if(!link.contains("https")){
                link = "https://en.wikipedia.org/" + link;
            }
            link = link.remove('"');
            artista a(link, nome);
            lista->push_back(a);
        }
        file.close();
    }else{
        qDebug() << "file not open " << file_name;
        qDebug() << file.errorString();
    }

}

void MainWindow::showList(std::vector<artista> *list, QTableWidget *tabella){
    //qDebug() << "entrato";
    QStringList header = {"Artista", "Link"};
    tabella->setColumnCount(2);
    tabella->setRowCount(list->size());
    tabella->setHorizontalHeaderLabels(header);
    tabella->setColumnWidth(0,220);
    tabella->setColumnWidth(1,60);
    tabella->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    tabella->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    for(unsigned int i=0; i<list->size(); i++){
        QTableWidgetItem *name = new QTableWidgetItem(list->at(i).get_nome());
        tabella->setItem(i,0,name);
        tabella->item(i,0)->setFlags(tabella->item(i,0)->flags() ^ Qt::ItemIsEditable);
        QLabel *label = new QLabel;
        label->setText("<a href="+list->at(i).get_link() + "> wiki</a>");
        label->setTextFormat(Qt::RichText);
        label->setTextInteractionFlags(Qt::TextBrowserInteraction);
        label->setOpenExternalLinks(true);
        tabella->setCellWidget(i,1, label);
    }
}

void MainWindow::grafoElenco(std::vector<artista> *list, QChartView *grafo){
    QStringList chars;
    QList<int> num;
    //int n=0;

    for(unsigned int i=0; i<list->size(); i++){
        QString c =list->at(i).get_nome().at(0).toUpper();
        //qDebug() << c;
        if(chars.contains(c)){
            int pos = 0;
            for(int j = 0; j<chars.length(); j++){
                if(chars.at(j) == c){
                    pos =j;
                    break;
                }
            }
            num[pos]++;
        }else{
            chars.append(c);
            num.append(1);
        }
    }

    QBarSet *set = new QBarSet("Numero Artisti");
    //QBarSeries *series = new QBarSeries();
    for(int j = 0; j<num.size(); j++){
        set->append(num.at(j));
        //qDebug() << num.at(j);
        //qDebug() << chars.at(j);
    }
    QBarSeries *series = new QBarSeries();
    series->append(set);
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    QValueAxis *axisY = new QValueAxis();
    axisX->append(chars);
    int max =0;
    for(int i=0; i<num.length();i++){
        if(num.at(i)>=max)
            max = num.at(i);
    }
    axisY->setRange(0, max);
    QChart *chart = new QChart();
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    chart->addSeries(series);
    chart->setTitle("Numero Artisti");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    grafo->setChart(chart);
}

void MainWindow::grafoTot(){
    QPieSeries *series = new QPieSeries();
    series->append("Universal", uni.size());
    series->append("EMI", emi.size());
    QChart *chart = new QChart();
    series->setLabelsVisible();
    series->setLabelsPosition(QPieSlice::LabelInsideHorizontal);
    chart->addSeries(series);
    for(auto slice : series->slices())
        slice->setLabel(QString("%1").arg(slice->value(), 0, 'd', 1)+" "+slice->label());
    ui->pieChart->setChart(chart);
    chart->setTitle("Comparazione");
    chart->setAnimationOptions(QChart::SeriesAnimations);
}
