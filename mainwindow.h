#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "muParser.h"
#include <algorithm>
//#include <math.h>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE
struct power
{
    QVector<double> pot;
    QVector<double> time;
    QVector<double> ampe;
};
struct Root
{
    bool valid ;
    double value;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
//--------------------------------------------------
private:
    mu::Parser parser;
    //QVector <double> x1;
    //QVector <double> y1;
    //QVector <double> x2;
    //QVector <double> y2;
    int n;
    power v1;
   // power entrg;
    void read(const char* arch, power& dat);

public slots:
    void plot();
    double conversion(double grados );
    //void maximas ();
    //void minimos ();
    //void promedios();
    //void plot1();
    //void plot();
    //Root bisection1();
  //  Root bisection2();
   //void area_contenida();
    //void arco_longitud();
    //void calcular_area_y_longitud_entre_maximos();
    //void graficar_valor_medio();
    //double df(double x);
    //void graficar_derivada();
   // double f(double x);
};
#endif // MAINWINDOW_H
