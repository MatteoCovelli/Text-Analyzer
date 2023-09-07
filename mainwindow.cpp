#include "mainwindow.h"
#include "ui_mainwindow.h"


//Per la open
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QtWidgets>
#include <QDebug>

//Per mandare il messaggio di errore a schermo(es: file non aperto)
#include <QMessageBox>

//Per il grafico
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QValueAxis>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
QT_CHARTS_USE_NAMESPACE






MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->txtVisualizza->setReadOnly(true);   //setto la text in modo tale che non si possa modificare
    ui->btnAnalizza->setEnabled(false); //All'avvio disabilito il bottone Analizza

}

MainWindow::~MainWindow()
{
    delete ui;
    delete chartView;   //Elimino il puntatore legato al grafico
}

/*
 *
 * Funzione che mi permette di aprire e visualizzare il file
 * Inoltre la tabella viene settata di default a ""
 *
 *
 * */
void MainWindow::on_actionCarica_triggered()
{
    QString nomeFile = QFileDialog::getOpenFileName(this,"Apri");   //File che devo aprire
    QFile file(nomeFile);   //creo un nuovo file
    filePath = nomeFile;    //path del file



    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        return;
    }

    setWindowTitle(nomeFile);   //Setto il nome della window
    QTextStream in(&file);
    in.setCodec("UTF-8");
    QString text = in.readAll();    //In text metto lo stream del file

    ui->btnAnalizza->setEnabled(true);
    ui->txtVisualizza->setText(text);    //metto il testo nella text edit per visualizzarlo
    file.close();   //chiudo il file

    delete chartView;
    chartView = nullptr;
    ui->tabella->setItem(0,0,new QTableWidgetItem(""));
    ui->tabella->setItem(1,0,new QTableWidgetItem(""));
    ui->tabella->setItem(2,0,new QTableWidgetItem(""));
    ui->tabella->setItem(3,0,new QTableWidgetItem(""));
    ui->tabella->setItem(4,0,new QTableWidgetItem(""));



}

/*
 *
 * La seguente funzione viene chiamata dopo che il bottone analizza è stato cliccato.
 * Essa si occupa dell'analisi del testo caricato; in particolare riempie la tabella
 * con tutte le analisi del caso e inoltre crea un grafico.
 * Inoltre si occupa di creare un file csv, dove vengono inseriti i dati dell'analisi.
 *
 *
 *
 * */
void MainWindow::on_btnAnalizza_clicked()
{
    //Tramite le chiamate alle diverse funzioni riempio la tabella con i dati dell'analizza
    int c,cNS,f,p,par;
    c = caratteri();
    ui->tabella->setItem(0,0,new QTableWidgetItem(QString::number(c)));
    cNS = caratteriNoSpazi();
    ui->tabella->setItem(1,0, new QTableWidgetItem(QString::number(cNS)) );
    par = parole();
    ui->tabella->setItem(2,0, new QTableWidgetItem(QString::number(par)) );
    f = frasi();
    ui->tabella->setItem(3,0, new QTableWidgetItem(QString::number(f)) );
    p = paragrafi();
    ui->tabella->setItem(4,0, new QTableWidgetItem(QString::number(p)) );


    //Creo il file csv e inserisco i dati.
    QString filename=QFileInfo(filePath).baseName();
    QFile data("./"+filename+".csv");
    if(data.open(QFile::WriteOnly |QFile::Truncate)){
        QTextStream output(&data);
        output << "Caratteri (inclusa punteggiatura e spazi): \t"<<c<<"\n";
        output << "Caratteri (spazi esclusi): \t"<<cNS<<"\n";
        output << "Parole: \t"<<par<<"\n";
        output << "Frasi: \t"<<f<<"\n";
        output << "Paragrafi: \t"<<p;
        data.close();
    }

    //Creo il grafico, se non è già stato creato
    if(chartView == nullptr){

        QBarSet *set0 = new QBarSet("Caratteri (inclusa punteggiatura e spazi)");
        QBarSet *set1 = new QBarSet("Caratteri (spazi esclusi)");
        QBarSet *set2 = new QBarSet("Parole");
        QBarSet *set3 = new QBarSet("Frasi");
        QBarSet *set4 = new QBarSet("Paragrafi");

        *set0 << c;
        *set1 << cNS;
        *set2 << par;
        *set3 << f;
        *set4 << p;

        int max = massimo(c,cNS, par, f, p);

        QBarSeries *series = new QBarSeries();
        series->append(set0);
        series->append(set1);
        series->append(set2);
        series->append(set3);
        series->append(set4);

        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->setTitle("Grafico");
        chart->setAnimationOptions(QChart::SeriesAnimations);

        QStringList categories;
        categories << "";
        QBarCategoryAxis *axisX = new QBarCategoryAxis();
        axisX->append(categories);
        chart->addAxis(axisX, Qt::AlignBottom);
        series->attachAxis(axisX);

        QValueAxis *axisY = new QValueAxis();
        axisY->setRange(0,max);   //SITEMARE 0, MAX
        chart->addAxis(axisY, Qt::AlignLeft);
        series->attachAxis(axisY);

        chart->legend()->setVisible(true);
        chart->legend()->setAlignment(Qt::AlignBottom);

        chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);

        ui->grafico->addWidget(chartView);
        show();
    }

}


/*
 *
 * Funzione che mi permette di calcolare il numero di caratteri
 * con spazi INCLUSI.
 *
 *
 * */

int MainWindow::caratteri(){

    QString s = ui->txtVisualizza->toPlainText();

    QChar ch;
    int cont = 0;
    int i, c =0, sp = 0;

    /*
     *
     * Nel seguente while conto il numero di caratteri (SPAZI INCLUSI) utilizzando
     * il valore unicode del carattere.
     *
     *
     * */
    while(cont <s.size())
    {
        ch = s.at(cont);

        i = ch.unicode();   //valore unicode del carattere


        if(  (i >32 && i<=10000))
        {
            c++;
        }
        else
        {
            if(ch==' ') //if che verifica se il carattere selezionato è uno spazio
            {
                sp++;   //incremento il contatore degli spazi
            }
        }
        cont++;

    }

    return c+sp;    //restituisco la somma tra il numero di caratteri e il numero di spazi

}

/*
 *
 * Funzione che mi permette di calcolare il numero di caratteri
 * con spazi ESCLUSI.
 *
 * */
int MainWindow::caratteriNoSpazi(){

    QString s = ui->txtVisualizza->toPlainText();

    QChar ch;
    int cont = 0;
    int i, c =0;

    /*
     *
     * Nel seguente while conto il numero di caratteri (SPAZI ESCLUSI) utilizzando
     * il valore unicode del carattere.
     *
     *
     * */
    while(cont <s.size())
    {
        ch = s.at(cont);

        i = ch.unicode();   //valore unicode del carattere


        if(  (i >32 && i<=10000))
        {
            c++;
        }

        cont++;

    }

    return c;

}


/*
 *
 * Funzione che mi permette di calcolare il numero di
 * frasi.
 *
 * */
int MainWindow::frasi(){


    QString s = ui->txtVisualizza->toPlainText();   //prendo il testo dalla text

    s.remove("\n");
    s.remove(" ");
    int fCount = 0;
    fCount = s.split(QRegExp("[.|!|?]"),QString::SkipEmptyParts).count();
    return fCount;  //restituisco il numero delle frasi



}

/*
 *
 * Funzione che mi permette di calcolare il numero di
 * paragrafi.
 *
 * */
int MainWindow::paragrafi(){

    QString s = ui->txtVisualizza->toPlainText();   //prendo il testo dalla text
    QStringList s1;

    s.remove('\t');
    s1 = s.split('\n');
    s1.removeAll("");
    return s1.size();   //restituisco il numero di paragrafi

}

/*
 *
 * Funzione che mi permette di calcolare il numero di
 * parole.
 *
 *
 * */
int MainWindow::parole(){

    QString s = ui->txtVisualizza->toPlainText();   //prendo il testo dalla text





    int wordCount = s.split(QRegExp("(\\s|\\n|\\r)+"), QString::SkipEmptyParts).count();    //conto le parole
    return wordCount;   //restuisco il numero delle parole

}

/*
 *
 * Funzione che mi permette di calcolare il numero massimo tra
 * caratteri, caratteri senza spazi, paragrafi, frasi e parole
 *
 *
 *
 * */
int MainWindow::massimo(int c,int cNS, int par, int f, int p)
{

    int max = 0;

    if(c>=cNS && c>=par && c>=f && c>=p)
    {
        max = c;
    }

    if(cNS>=c && cNS>=par && cNS>=f && cNS>=p)
    {
        max = cNS;
    }
    if(par>=c && par>=cNS && par>=f && par>=p)
    {
        max = par;
    }
    if(f>=c && f>=cNS && f>=par && f>=p)
    {
        max = f;
    }
    if(p>=c && p>=cNS && p>=par && p>=f)
    {
        max = p;
    }

    return max;

}



































