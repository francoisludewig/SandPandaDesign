#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<QPushButton>

void MainWindow::InitPlanTab(MyGLWidget* myGLWidget)
{
    QPushButton* addPlanButton = (QPushButton*)(ui->addPlanPushButton);
    QPushButton* removePlanButton = (QPushButton*)(ui->removePlanPushButton);
    PlanTableWidget* plantable = (PlanTableWidget*)(ui->planTableWidget);
    VelocitiesTabWidget* velocitiesPlanTabWidget = ( VelocitiesTabWidget*)(ui->planVelocitiesTabWidget);
    connect(addPlanButton, &QPushButton::clicked, plantable, &PlanTableWidget::on_add_plan);
    connect(removePlanButton, &QPushButton::clicked, plantable, &PlanTableWidget::on_remove_plan);
    connect(plantable, &PlanTableWidget::itemChanged, plantable, &PlanTableWidget::on_new_value);
    connect(plantable, &PlanTableWidget::data_updated, myGLWidget, &MyGLWidget::on_new_data);
    connect(plantable, &PlanTableWidget::new_plan, velocitiesPlanTabWidget, &VelocitiesTabWidget::addSolid);
    connect(plantable, &PlanTableWidget::remove_plan, velocitiesPlanTabWidget, &VelocitiesTabWidget::removeSolid);
    velocitiesPlanTabWidget->buildConnections("_plan");
}

void MainWindow::InitDiskTab(MyGLWidget* myGLWidget)
{
    QPushButton* addDiskButton = (QPushButton*)(ui->addDiskPushButton);
    QPushButton* removeDiskButton = (QPushButton*)(ui->removeDiskPushButton);
    DiskTableWidget* disktable = (DiskTableWidget*)(ui->diskTableWidget);
    VelocitiesTabWidget* velocitiesDiskTabWidget = ( VelocitiesTabWidget*)(ui->diskVelocitiesTabWidget);
    connect(addDiskButton, &QPushButton::clicked, disktable, &DiskTableWidget::on_add_disk);
    connect(removeDiskButton, &QPushButton::clicked, disktable, &DiskTableWidget::on_remove_disk);
    connect(disktable, &DiskTableWidget::itemChanged, disktable, &DiskTableWidget::on_new_value);
    connect(disktable, &DiskTableWidget::data_updated, myGLWidget, &MyGLWidget::on_new_data);
    connect(disktable, &DiskTableWidget::new_disk, velocitiesDiskTabWidget, &VelocitiesTabWidget::addSolid);
    connect(disktable, &DiskTableWidget::remove_disk, velocitiesDiskTabWidget, &VelocitiesTabWidget::removeSolid);
    connect(ui->drawBaseCheckBox, &QCheckBox::stateChanged, myGLWidget, &MyGLWidget::on_new_drawBase_state);
    velocitiesDiskTabWidget->buildConnections("_disk");
}

void MainWindow::InitConeTab(MyGLWidget* myGLWidget)
{
    QPushButton* addButton = (QPushButton*)(ui->addConePushButton);
    QPushButton* removeButton = (QPushButton*)(ui->removeConePushButton);
    ConeTableWidget* table = (ConeTableWidget*)(ui->coneTableWidget);
    VelocitiesTabWidget* velocitiesTabWidget = ( VelocitiesTabWidget*)(ui->coneVelocitiesTabWidget);
    connect(addButton, &QPushButton::clicked, table, &ConeTableWidget::on_add_cone);
    connect(removeButton, &QPushButton::clicked, table, &ConeTableWidget::on_remove_cone);
    connect(table, &ConeTableWidget::itemChanged, table, &ConeTableWidget::on_new_value);
    connect(table, &ConeTableWidget::data_updated, myGLWidget, &MyGLWidget::on_new_data);
    connect(table, &ConeTableWidget::new_cone, velocitiesTabWidget, &VelocitiesTabWidget::addSolid);
    connect(table, &ConeTableWidget::remove_cone, velocitiesTabWidget, &VelocitiesTabWidget::removeSolid);
    connect(ui->drawBaseCheckBox, &QCheckBox::stateChanged, myGLWidget, &MyGLWidget::on_new_drawBase_state);
    velocitiesTabWidget->buildConnections("_cone");
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MyGLWidget* myGLWidget = (MyGLWidget*)(ui->openGLWidget);

    InitPlanTab(myGLWidget);
    InitDiskTab(myGLWidget);
    InitConeTab(myGLWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}
