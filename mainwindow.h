#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QTableWidget>
#include <QTimer>
#include <QChartView>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void finito(int newValue);

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager manager;
    QString Url[2] = {"http://www.ivl.disco.unimib.it/minisites/cpp/List_of_Universal_artists.txt","http://www.ivl.disco.unimib.it/minisites/cpp/List_of_EMI_artists.txt"};
    QString files[2] = {"lista1.txt", "lista2.txt"};
    int num = 0;
    void load();
    void grafoTot();
    void download(int num);


    struct artista{
        QString nome;
        QString link;
        artista(){
            nome = "NoName";
            link = "";
        }
        artista(QString l, QString n){
            nome = n;
            link = l;
        }
        QString get_nome(){
            return nome;
        }
        QString get_link(){
            return link;
        }
    };
    std::vector<artista> uni;
    std::vector<artista> emi;

    void readFile(QString file_name, std::vector<artista> *lista);
    void showList(std::vector<artista> *lista, QTableWidget *tabella);
    void grafoElenco(std::vector<artista> *lista, QChartView *grafo);

public slots:
    void scaricato(QNetworkReply *reply);

};
#endif // MAINWINDOW_H
