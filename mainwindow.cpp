#include "mainwindow.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    // Set up the main intakeLayout
    QVBoxLayout *mainLayout = new QVBoxLayout();
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    centralWidget->setLayout(mainLayout);

    // Create valvetrain group box for intake parameters
    QGroupBox *intakeGroupBox = new QGroupBox("Intake Parameters", this);
    QVBoxLayout *intakeLayout = new QVBoxLayout();
    intakeGroupBox->setLayout(intakeLayout);
     // Create input fields for Valve Lift
    intakeLayout->addWidget(new QLabel("Valve Lift (Intake):", this));
    valveLiftInputIntake = new QLineEdit(this);
    intakeLayout->addWidget(valveLiftInputIntake);
    // Create input fields for Valve Lift (Exhaust)
    intakeLayout->addWidget(new QLabel("Valve Lift (Exhaust):", this));
    valveLiftInputExhaust = new QLineEdit(this);
    intakeLayout->addWidget(valveLiftInputExhaust);
    // Create input fields for Duration (Intake)
    intakeLayout->addWidget(new QLabel("Duration (Intake):", this));
    durationInputIntake = new QLineEdit(this);
    intakeLayout->addWidget(durationInputIntake);
    // Create input fields for Duration (Exhaust)
    intakeLayout->addWidget(new QLabel("Duration (Exhaust):", this));
    durationInputExhaust = new QLineEdit(this);
    intakeLayout->addWidget(durationInputExhaust);
    // Create input field for lobe seperation
    intakeLayout->addWidget(new QLabel("Lobe Seperation", this));
    lobeSeparationInput = new QLineEdit(this);
    intakeLayout->addWidget(lobeSeparationInput);
    // create input feild for valve dia
    intakeLayout->addWidget(new QLabel("IntakeValve Dia", this));
    IntakeValveDiamiterInput = new QLineEdit(this);
    intakeLayout->addWidget(IntakeValveDiamiterInput);
    // create input feild for valve dia
    intakeLayout->addWidget(new QLabel("ExhaustValve Dia", this));
    ExhaustValveDiamiterInput = new QLineEdit(this);
    intakeLayout->addWidget(ExhaustValveDiamiterInput);
    // Create a group box for bottom end parameters
    QGroupBox *engineGroupBox = new QGroupBox("Engine Parameters", this);
    QHBoxLayout *engineLayout = new QHBoxLayout();
    engineGroupBox->setLayout(engineLayout);

    // Add input fields for engine parameters
    // ...

    engineLayout->addWidget(new QLabel("Chamber Volume (heads)", this));
    ChamberVolumeInput = new QLineEdit(this);
    engineLayout->addWidget(ChamberVolumeInput);

    engineLayout->addWidget(new QLabel("Bore", this));
    BoreInput = new QLineEdit(this);
    engineLayout->addWidget(BoreInput);

    engineLayout->addWidget(new QLabel("Stroke", this));
    StrokeInput = new QLineEdit(this);
    engineLayout->addWidget(StrokeInput);

    engineLayout->addWidget(new QLabel("#of cylinders", this));
    cylendersInput = new QLineEdit(this);
    engineLayout->addWidget(cylendersInput);

    QGroupBox *resultGroupBox = new QGroupBox("Results will appear here", this);
    QVBoxLayout *resultLayout = new QVBoxLayout();
    resultGroupBox->setLayout(resultLayout);

    // Create a Calculate button
    QPushButton *calculateButton = new QPushButton("Calculate", this);


    // Add all the group boxes, Calculate button, and result label to the main intakeLayout
    mainLayout->addWidget(intakeGroupBox);
    mainLayout->addWidget(engineGroupBox);
    mainLayout->addWidget(calculateButton);
    mainLayout->addWidget(resultGroupBox);

    // Connect the Calculate button to a slot for performing calculations
    connect(calculateButton, &QPushButton::clicked, this, &MainWindow::performCalculations);

    QPushButton *plotButton = new QPushButton("Plot Valve Open Times", this);
    resultLayout->addWidget(plotButton);

    connect(plotButton, &QPushButton::clicked, this, &MainWindow::plotValveOpenTimes);
}

MainWindow::~MainWindow() {
    // Release allocated memory, if necessary
}

/*double calculateIntakeVolumetricEfficiency(double CID, double valveLift, double duration, double intakeRunnerVolume, double intakeValveDiameter /* other intake-specific factors *///) {
    // Calculate intake volumetric efficiency using intake-specific factors
 /* double intakeVolumetricEfficiency = (engineCapacity * valveLift * duration * intakeRunnerVolume * intakeValveDiameter /* other intake factors *///) * 100.0;
   // return intakeVolumetricEfficiency;
//}

/*double calculateExhaustVolumetricEfficiency(double CID, double EXvalveLift, double EXduration, double ExhaustRunner, double ExhaustValveDiameter /* other exhaust-specific factors *///) {
    // Calculate exhaust volumetric efficiency using exhaust-specific factors
  /*  double exhaustVolumetricEfficiency = (CID * valveLift * duration * exhaustVolume * exhaustValveDiameter /* other exhaust factors *///) * 100.0;
  /** return exhaustVolumetricEfficiency;
}
*/
void MainWindow::plotValveOpenTimes() {
    std::ofstream outputFile("valve_open_times.dat");
    if (!outputFile.is_open()) {
        // Handle file open error
        return;
    }

    // Given camshaft specifications
    double intakeDuration = durationInputIntake->text().toDouble();
    double exhaustDuration = durationInputExhaust->text().toDouble();

    // RPM range to calculate valve open time
    int minRPM = 400;
    int maxRPM = 8500;
    int rpmIncrement = 300;

    for (int rpm = minRPM; rpm <= maxRPM; rpm += rpmIncrement) {
        double intakeOpenTime = calculateValveOpenTime(intakeDuration, rpm);
        double exhaustOpenTime = calculateValveOpenTime(exhaustDuration, rpm);

        // Write intake valve open times to file
        outputFile << rpm << "\t" << intakeOpenTime << "\t" << "Intake\n";

        // Write exhaust valve open times to file
        outputFile << rpm << "\t" << exhaustOpenTime << "\t" << "Exhaust\n";
    }

    outputFile.close();

    QString command = "gnuplot -persist -e \"plot 'valve_open_times.dat' using 1:2 with points title 'Valve Open Time vs RPM'\"";
    QProcess::startDetached(command);
}

double MainWindow::calculateValveOpenTime(double durationt, int rpm) {
    double durationInSeconds = (durationt / 360.0) * (1.0 / (rpm / 60.0));
    return durationInSeconds;
}

double MainWindow::calculateHorsepower(double valveLift, double duration, double lobeSeparation, double ChamberVolume, double EXduration, double EXvalveLift, double Bore, double Stroke) {
    // Perform horsepower calculation based on the input parameters
    // Replace this with your actual horsepower calculation logic
    double horsepower = (valveLift * duration / (lobeSeparation * ChamberVolume))+(EXvalveLift * EXduration / (lobeSeparation * ChamberVolume));
    return horsepower;
}

double MainWindow::calculateEngineDisplacement (double chamberVolume, double Stroke, double Bore, double Cylenders) {
    double combustionChamberVolumeCI = chamberVolume / 16.387; // Convert chamber volume to cubic inches A.K.A Freedom Units
    double cylinderVolume = (M_PI * pow(Bore, 2) * Stroke) / 4; // Calculate cylinder volume in cubic inches
    double CID = (cylinderVolume + combustionChamberVolumeCI) * Cylenders; // Total engine displacement
    return CID;

}

void MainWindow::performCalculations() {
    // Retrieve values from input fields
    double valveLiftIntake = valveLiftInputIntake->text().toDouble();
    double valveLiftExhaust = valveLiftInputExhaust->text().toDouble();
    double durationIntake = durationInputIntake->text().toDouble();
    double durationExhaust = durationInputExhaust->text().toDouble();
    double lobeSeparation = lobeSeparationInput->text().toDouble();
    double ChamberVolume = ChamberVolumeInput->text().toDouble();
    double Bore = BoreInput->text().toDouble();
    double Stroke = StrokeInput->text().toDouble();
    double cylenders = cylendersInput->text().toDouble();    
    // Retrieve other parameters
    if (valveLiftIntake == 0 || durationIntake == 0 || valveLiftExhaust == 0 || durationExhaust == 0 ||
        lobeSeparation == 0 || ChamberVolume == 0 || Bore == 0 || Stroke == 0 || cylenders == 0) {
        // Handle invalid input
        return;
    }

    // Calculate horsepower
    double horsepower = calculateHorsepower(valveLiftIntake, durationIntake, lobeSeparation, ChamberVolume, durationExhaust, valveLiftExhaust, Bore, Stroke /*...Pass other parameters...*/);
    double CID = calculateEngineDisplacement(ChamberVolume, Stroke, Bore, cylenders);
    // Display the calculated horsepower in the result label
    QString resultText = QString("Calculated Horsepower: %1 HP").arg(horsepower);
    resultLabel->setText(resultText);

    QString cidd = QString("C.I.D: %1 ").arg(CID);
    ccid->setText(cidd);

    // Plot the horsepower using GNU Plot
    QString command = "gnuplot -persist -e \"plot " + QString::number(horsepower) + " * sin(x)\"";
    QProcess::startDetached(command); // Execute the GNU Plot command
}

void MainWindow::calculateButtonClicked() {
    // Call calculation function when Calculate button is clicked
    performCalculations();
}
