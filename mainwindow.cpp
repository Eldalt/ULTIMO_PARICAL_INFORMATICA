#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <algorithm>
//#include <math.h>
#include <math.h>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(plot()) );
//connect(ui->derivada, SIGNAL(clicked()), this, SLOT(graficar_derivada()));
//connect(ui->pushButton_4,SIGNAL(clicked()),this,SLOT(bisection1()));
//connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(bisection2()));
 //area contenida entre las 2 funciones.
//connect(ui->pushButton_3,SIGNAL(clicked()),this,SLOT(area_contenida()));
//connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(maximas()) );
//connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(minimos()) );
//connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(plot1()) );
}

MainWindow::~MainWindow()
{
    delete ui;
}
double MainWindow::conversion(double grados)
{
    return (grados * M_PI) / 180.0;
}
void MainWindow::read(const char *arch, power &dat)
{
    FILE *f = fopen(arch, "rb");
    fseek(f,0,SEEK_END);
     n=ftell(f)/sizeof(double);
    fseek(f, 0, SEEK_SET);

    if(f == NULL){
        qDebug() << "Error al abrir el archivo";
        return;
    }
    double t, p,i;
    while(fread(&t, sizeof(double), 1, f)){
        dat.time.append(t);
        fread(&p, sizeof(double), 1, f);
        dat.pot.append(p);
        fread(&i, sizeof(double), 1, f);
        dat.ampe.append(i);
    }
    fclose(f);

}
void  MainWindow::plot()
{
    read("C:\\Users\\juaan\\Desktop\\TIRANDO CODIGOS\\Plotter2024\\vi_5.dat",v1);
    //QVector<power> data;
    QVector<double> tiempo(v1.time.size()), tension(v1.pot.size()), corriente(v1.ampe.size());
    for (int i = 0; i < v1.time.size(); ++i)
    {
        tiempo[i] = v1.time[i];
        tension[i] = v1.pot[i];
        corriente[i] = v1.ampe[i];
    }
    // Graficar la tensión
    ui->graphic->addGraph(); //agregamos  grafica
    ui->graphic->graph(0)->setData(tiempo, tension);
    ui->graphic->graph(0)->setPen(QPen(Qt::blue));
    ui->graphic->graph(0)->setName("tension");

    // Graficar la corriente
    ui->graphic->addGraph(); // agregamos  grafica
    ui->graphic->graph(1)->setData(tiempo, corriente);
    ui->graphic->graph(1)->setPen(QPen(Qt::red));
    ui->graphic->graph(1)->setName("corriente");

    ui->graphic->setInteractions(QCP::iRangeZoom | QCP::iRangeDrag);//me permite moverme en la grafica
    ui->graphic->rescaleAxes(); // ajustar los ejes para mostrar todos los datos
    ui->graphic->replot(); // reset
    // Calcular ángulo de desfasaje entre tensión y corriente
    //iba ser una funcion que me calcule el desfase  pero use solo variables locales :(
    int t1_maxtension = 0;
    int c1_maxcorriente = 0;
    double maxtension = tension[0];
    double maxcorriente = corriente[0];
    //buscamos el mayor de la tension y corriente
    for (int i = 1; i < tension.size(); ++i)
    {       //comparamos
        if (tension[i] > maxtension)
        {
            maxtension = tension[i];
            t1_maxtension = i;
        }   //comparamos
        if (corriente[i] > maxcorriente)
        {
            maxcorriente = corriente[i];
           c1_maxcorriente = i;
        }
    }
    double tiempo_maxtension = tiempo[t1_maxtension];//tiempo que llega a la tension maxima
    double tiempo_maxcorriente = tiempo[c1_maxcorriente];//tiempo que llega a la corrietne maxima

    double t_desfasaje = tiempo_maxcorriente - tiempo_maxtension; //el tiempo de desfasaje entre tensión y corriente
    double angulo_desfasaje = (180.0 / 0.01) * t_desfasaje; //conversion

    qDebug() << "angulo de desfasaje grados=" <<angulo_desfasaje ; //angulo de desfase

    double suma_tension=0;
    double suma_corriente=0;
    //regla de los trapesios
    for (int i = 0; i < tension.size() - 1; ++i)
    {
        double dt = tiempo[i + 1] - tiempo[i];
                          //cuadrado
        suma_tension += ((tension[i] * tension[i]) + (tension[i + 1] * tension[i + 1])) * dt / 2.0;
                           //cuadrado
        suma_corriente += ((corriente[i] * corriente[i]) + (corriente[i + 1] * corriente[i + 1])) * dt / 2.0;
    }
    double total_tiempo = tiempo.last() - tiempo.first();
    double vrms = std::sqrt(suma_tension / total_tiempo); // calculo vrms
    double irms = std::sqrt(suma_corriente / total_tiempo); // calculo irms
    qDebug() << "Vrms:" << vrms; // muestro en consola
    qDebug() << "Irms:" << irms; // muestro en consola
   double angulo_radianes=0;
    angulo_radianes=conversion(angulo_desfasaje);//funcion de conversion
    qDebug() << "angulo radianes" << angulo_radianes; // muestro en consola

    double P=vrms*irms*cos(angulo_radianes);
    qDebug() << "potencia mecanica " << P;



}

