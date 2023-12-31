#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QProcess>
#include <QMainWindow>



class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void plotValveOpenTimes();
    void calculateButtonClicked();
    void performCalculations();
    double calculateHorsepower(double valveLift, double duration, double lobeSeparation, double ChamberVolume, double EXduration, double EXvalveLift, double Stroke, double Bore);
    double calculateEngineDisplacement (double chamberVolume, double Stroke, double Bore, double Cylenders);
     double calculateValveOpenTime(double intakeDuration, int rpm); // Declaration
private:
    QLineEdit *valveLiftInputIntake;
    QLineEdit *valveLiftInputExhaust;
    QLineEdit *durationInputIntake;
    QLineEdit *durationInputExhaust;
    QLineEdit *lobeSeparationInput;
    QLineEdit *IntakeRunnerInput;
    QLineEdit *ExhaustRunnerInput;
    QLineEdit *IntakeValveDiamiterInput;    
    QLineEdit *ExhaustValveDiamiterInput;        
    QLineEdit *ChamberVolumeInput;
    QLineEdit *StrokeInput;
    QLineEdit *BoreInput;
    QLineEdit *cylendersInput;
    QLabel *resultLabel;
    QLabel *ccid;
};

#endif // MAINWINDOW_H
