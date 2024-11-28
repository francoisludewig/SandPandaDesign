#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<QPushButton>
#include "Presenter/messagepresenter.h"

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
    velocitiesTabWidget->buildConnections("_cone");
}


void MainWindow::InitElbowTab(MyGLWidget* myGLWidget)
{
    QPushButton* addButton = (QPushButton*)(ui->addElbowPushButton);
    QPushButton* removeButton = (QPushButton*)(ui->removeElbowPushButton);
    ElbowTableWidget* table = (ElbowTableWidget*)(ui->elbowTableWidget);
    VelocitiesTabWidget* velocitiesTabWidget = ( VelocitiesTabWidget*)(ui->elbowVelocitiesTabWidget);
    connect(addButton, &QPushButton::clicked, table, &ElbowTableWidget::on_add_elbow);
    connect(removeButton, &QPushButton::clicked, table, &ElbowTableWidget::on_remove_elbow);
    connect(table, &ElbowTableWidget::itemChanged, table, &ElbowTableWidget::on_new_value);
    connect(table, &ElbowTableWidget::data_updated, myGLWidget, &MyGLWidget::on_new_data);
    connect(table, &ElbowTableWidget::new_elbow, velocitiesTabWidget, &VelocitiesTabWidget::addElbow);
    connect(table, &ElbowTableWidget::remove_elbow, velocitiesTabWidget, &VelocitiesTabWidget::removeElbow);
    velocitiesTabWidget->buildConnections("_elbow");
}



void MainWindow::InitCuboidTab(MyGLWidget* myGLWidget)
{
    QPushButton* addButton = (QPushButton*)(ui->addCuboidPushButton);
    QPushButton* removeButton = (QPushButton*)(ui->removeCuboidPushButton);
    CuboidTableWidget* table = (CuboidTableWidget*)(ui->cuboidTableWidget);
    VelocitiesTabWidget* velocitiesTabWidget = ( VelocitiesTabWidget*)(ui->cuboidVelocitiesTabWidget);
    connect(addButton, &QPushButton::clicked, table, &CuboidTableWidget::on_add_cuboid);
    connect(removeButton, &QPushButton::clicked, table, &CuboidTableWidget::on_remove_cuboid);
    connect(table, &CuboidTableWidget::itemChanged, table, &CuboidTableWidget::on_new_value);
    connect(table, &CuboidTableWidget::data_updated, myGLWidget, &MyGLWidget::on_new_data);
    connect(table, &CuboidTableWidget::new_cuboid, velocitiesTabWidget, &VelocitiesTabWidget::addSolid);
    connect(table, &CuboidTableWidget::remove_cuboid, velocitiesTabWidget, &VelocitiesTabWidget::removeSolid);
    velocitiesTabWidget->buildConnections("_cuboid");
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
    InitElbowTab(myGLWidget);
    InitCuboidTab(myGLWidget);

    connect(ui->drawBaseCheckBox, &QCheckBox::stateChanged, myGLWidget, &MyGLWidget::on_new_drawBase_state);
    connect(ui->containerComboBox, &QComboBox::currentIndexChanged, myGLWidget, &MyGLWidget::on_new_container_visual_parameter);


    MessagePresenter::getInstance().SetLabel(ui->messageLabel);
    MessagePresenter::getInstance().AddMessage("SandPandaDesign");
}

MainWindow::~MainWindow()
{
    delete ui;
}
