#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<QPushButton>
#include "Presenter/messagepresenter.h"
#include "Widgets/setuptimewidget.h"
#include "Widgets/setupgravitywidget.h"
#include "Widgets/saveloadexportwidget.h"

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

    connect(table, &ConeTableWidget::cones_updated, ui->coneListComboBox, &ConesComboBox::new_cones_list);

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

    connect(table, &CuboidTableWidget::cuboids_updated, ui->cuboidListComboBox, &CuboidsComboBox::new_cuboids_list);

    velocitiesTabWidget->buildConnections("_cuboid");
}


void MainWindow::InitLatticeTab(MyGLWidget* myGLWidget) {
    QPushButton* addButton = (QPushButton*)(ui->addLatticePushButton);
    QPushButton* removeButton = (QPushButton*)(ui->removeLatticePushButton);
    LatticeTableWidget* table = (LatticeTableWidget*)(ui->latticeTableWidget);
    table->listCone = ui->coneListComboBox;
    table->listCuboid = ui->cuboidListComboBox;
    connect(addButton, &QPushButton::clicked, table, &LatticeTableWidget::on_add_lattice);
    connect(removeButton, &QPushButton::clicked, table, &LatticeTableWidget::on_remove_lattice);
    connect(table, &LatticeTableWidget::itemChanged, table, &LatticeTableWidget::on_new_value);
    connect(table, &LatticeTableWidget::data_updated, myGLWidget, &MyGLWidget::on_new_data);
    connect(ui->linkToConePushButton, &QPushButton::released, table, &LatticeTableWidget::on_new_link_to_cone);
    connect(ui->linkToCuboidPushButton, &QPushButton::released, table, &LatticeTableWidget::on_new_link_to_cuboid);
    connect(ui->unlinkPushButton, &QPushButton::released, table, &LatticeTableWidget::on_unlink);

    connect(ui->cuboidTableWidget, &CuboidTableWidget::data_updated, table, &LatticeTableWidget::on_update_from_container);
    connect(ui->coneTableWidget, &ConeTableWidget::data_updated, table, &LatticeTableWidget::on_update_from_container);
}


void MainWindow::InitSetupTimeWidget(SetupTimeWidget* setupTimeWidget) {
    connect(ui->startingTimeField, &QLineEdit::textChanged, setupTimeWidget, &SetupTimeWidget::on_new_start_time);
    connect(ui->timestepField, &QLineEdit::textChanged, setupTimeWidget, &SetupTimeWidget::on_new_time_step);
    connect(ui->captureDelayField, &QLineEdit::textChanged, setupTimeWidget, &SetupTimeWidget::on_new_capture_delay);
    connect(ui->durationField, &QLineEdit::textChanged, setupTimeWidget, &SetupTimeWidget::on_new_duration);
    connect(ui->computeTimestep, &QPushButton::clicked , setupTimeWidget, &SetupTimeWidget::on_compute_timestep);
    setupTimeWidget->setTimesetpField(ui->timestepField);
    setupTimeWidget->setStartingTimeField(ui->startingTimeField);
    setupTimeWidget->setCaptureDelayField(ui->captureDelayField);
    setupTimeWidget->setDurationField(ui->durationField);
}

void MainWindow::InitSetupContactModelWidget(SetupContactModelWidget* setupContactModelWidget) {
    connect(ui->restitutionField, &QLineEdit::textChanged, setupContactModelWidget, &SetupContactModelWidget::on_new_restitution_coefficient);
    connect(ui->stiffnessField, &QLineEdit::textChanged, setupContactModelWidget, &SetupContactModelWidget::on_new_stiffness_coefficient);
    connect(ui->staticFrictionField, &QLineEdit::textChanged, setupContactModelWidget, &SetupContactModelWidget::on_new_static_friction_coefficient);
    connect(ui->dynFrictionField, &QLineEdit::textChanged, setupContactModelWidget, &SetupContactModelWidget::on_new_dynamic_friction_coefficient);
    connect(ui->tangentialModelComboBox, &QComboBox::currentIndexChanged, setupContactModelWidget, &SetupContactModelWidget::on_new_tangential_model);
    setupContactModelWidget->setStaticFrictionCoefficient(ui->staticFrictionField);
    setupContactModelWidget->setRestitutionField(ui->restitutionField);
    setupContactModelWidget->setStiffnessField(ui->stiffnessField);
    setupContactModelWidget->setDynFrictionField(ui->dynFrictionField);
    setupContactModelWidget->setTangentialModelComboBox(ui->tangentialModelComboBox);
    setupContactModelWidget->setStaticFrictionCoefficientLabel(ui->static_friction_coefficient_label);
}


void MainWindow::InitSetupGravityWidget(SetupGravityWidget* setupGravityWidget) {

    connect(ui->gravity_acceleration_field, &QLineEdit::textChanged, setupGravityWidget, &SetupGravityWidget::on_new_gravityAcceleration);

    connect(ui->gravity_x_direction_field, &QLineEdit::textChanged, setupGravityWidget, &SetupGravityWidget::on_new_gravity_x_direction);
    connect(ui->gravity_y_direction_field, &QLineEdit::textChanged, setupGravityWidget, &SetupGravityWidget::on_new_gravity_y_direction);
    connect(ui->gravity_z_direction_field, &QLineEdit::textChanged, setupGravityWidget, &SetupGravityWidget::on_new_gravity_z_direction);

    connect(ui->gravity_vx_a0_field, &QLineEdit::textChanged, setupGravityWidget, &SetupGravityWidget::on_new_gravity_vx_A0);
    connect(ui->gravity_vx_a1_field, &QLineEdit::textChanged, setupGravityWidget, &SetupGravityWidget::on_new_gravity_vx_A1);
    connect(ui->gravity_vx_w_field, &QLineEdit::textChanged, setupGravityWidget, &SetupGravityWidget::on_new_gravity_vx_w);
    connect(ui->gravity_vx_p_field, &QLineEdit::textChanged, setupGravityWidget, &SetupGravityWidget::on_new_gravity_vx_p);

    connect(ui->gravity_vy_a0_field, &QLineEdit::textChanged, setupGravityWidget, &SetupGravityWidget::on_new_gravity_vy_A0);
    connect(ui->gravity_vy_a1_field, &QLineEdit::textChanged, setupGravityWidget, &SetupGravityWidget::on_new_gravity_vy_A1);
    connect(ui->gravity_vy_w_field, &QLineEdit::textChanged, setupGravityWidget, &SetupGravityWidget::on_new_gravity_vy_w);
    connect(ui->gravity_vy_p_field, &QLineEdit::textChanged, setupGravityWidget, &SetupGravityWidget::on_new_gravity_vy_p);

    connect(ui->gravity_vz_a0_field, &QLineEdit::textChanged, setupGravityWidget, &SetupGravityWidget::on_new_gravity_vz_A0);
    connect(ui->gravity_vz_a1_field, &QLineEdit::textChanged, setupGravityWidget, &SetupGravityWidget::on_new_gravity_vz_A1);
    connect(ui->gravity_vz_w_field, &QLineEdit::textChanged, setupGravityWidget, &SetupGravityWidget::on_new_gravity_vz_w);
    connect(ui->gravity_vz_p_field, &QLineEdit::textChanged, setupGravityWidget, &SetupGravityWidget::on_new_gravity_vz_p);

    setupGravityWidget->setComponant("gravity_acceleration_field", ui->gravity_acceleration_field);
    setupGravityWidget->setComponant("gravity_x_direction_field", ui->gravity_x_direction_field);
    setupGravityWidget->setComponant("gravity_y_direction_field", ui->gravity_y_direction_field);
    setupGravityWidget->setComponant("gravity_z_direction_field", ui->gravity_z_direction_field);
    setupGravityWidget->setComponant("gravity_vx_a0_field", ui->gravity_vx_a0_field);
    setupGravityWidget->setComponant("gravity_vx_a1_field", ui->gravity_vx_a1_field);
    setupGravityWidget->setComponant("gravity_vx_w_field", ui->gravity_vx_w_field);
    setupGravityWidget->setComponant("gravity_vx_p_field", ui->gravity_vx_p_field);
    setupGravityWidget->setComponant("gravity_vy_a0_field", ui->gravity_vy_a0_field);
    setupGravityWidget->setComponant("gravity_vy_a1_field", ui->gravity_vy_a1_field);
    setupGravityWidget->setComponant("gravity_vy_w_field", ui->gravity_vy_w_field);
    setupGravityWidget->setComponant("gravity_vy_p_field", ui->gravity_vy_p_field);
    setupGravityWidget->setComponant("gravity_vz_a0_field", ui->gravity_vz_a0_field);
    setupGravityWidget->setComponant("gravity_vz_a1_field", ui->gravity_vz_a1_field);
    setupGravityWidget->setComponant("gravity_vz_w_field", ui->gravity_vz_w_field);
    setupGravityWidget->setComponant("gravity_vz_p_field", ui->gravity_vz_p_field);
}

void MainWindow::InitSaveLoadExportWidget(SaveLoadExportWidget* saveloadexportwidget, SetupTimeWidget* setupTimeWidget, SetupContactModelWidget* setupContactModelWidge, SetupGravityWidget* setupGravityWidget) {
    connect(ui->exportButton, &QPushButton::clicked, saveloadexportwidget, &SaveLoadExportWidget::on_export);
    connect(ui->saveButton, &QPushButton::clicked, saveloadexportwidget, &SaveLoadExportWidget::on_save);
    connect(ui->loadButton, &QPushButton::clicked, saveloadexportwidget, &SaveLoadExportWidget::on_load);
    connect(saveloadexportwidget, &SaveLoadExportWidget::file_loaded, ui->coneTableWidget, &ConeTableWidget::LoadDataFromRepository);
    connect(saveloadexportwidget, &SaveLoadExportWidget::file_loaded, ui->cuboidTableWidget, &CuboidTableWidget::LoadDataFromRepository);
    connect(saveloadexportwidget, &SaveLoadExportWidget::file_loaded, ui->diskTableWidget, &DiskTableWidget::LoadDataFromRepository);
    connect(saveloadexportwidget, &SaveLoadExportWidget::file_loaded, ui->planTableWidget, &PlanTableWidget::LoadDataFromRepository);
    connect(saveloadexportwidget, &SaveLoadExportWidget::file_loaded, ui->elbowTableWidget, &ElbowTableWidget::LoadDataFromRepository);
    connect(saveloadexportwidget, &SaveLoadExportWidget::file_loaded, ui->latticeTableWidget, &LatticeTableWidget::LoadDataFromRepository);
    connect(saveloadexportwidget, &SaveLoadExportWidget::file_loaded, setupTimeWidget, &SetupTimeWidget::LoadDataFromRepository);
    connect(saveloadexportwidget, &SaveLoadExportWidget::file_loaded, setupContactModelWidge, &SetupContactModelWidget::LoadDataFromRepository);
    connect(saveloadexportwidget, &SaveLoadExportWidget::file_loaded, setupGravityWidget, &SetupGravityWidget::LoadDataFromRepository);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MyGLWidget* myGLWidget = (MyGLWidget*)(ui->openGLWidget);
    AnimationWidget* animator = new AnimationWidget(nullptr);
    SetupTimeWidget* setupTimeWidget = new SetupTimeWidget(nullptr);
    SetupContactModelWidget* setupContactModelWidget = new SetupContactModelWidget(nullptr);
    SetupGravityWidget* setupGravityWidget = new SetupGravityWidget(nullptr);
    SaveLoadExportWidget* saveloadexportwidget = new SaveLoadExportWidget(nullptr);

    animator->init();
    myGLWidget->setAnimator(animator);

    InitPlanTab(myGLWidget);
    InitDiskTab(myGLWidget);
    InitConeTab(myGLWidget);
    InitElbowTab(myGLWidget);
    InitCuboidTab(myGLWidget);
    InitLatticeTab(myGLWidget);
    InitSetupTimeWidget(setupTimeWidget);
    InitSetupContactModelWidget(setupContactModelWidget);
    InitSetupGravityWidget(setupGravityWidget);
    InitSaveLoadExportWidget(saveloadexportwidget, setupTimeWidget, setupContactModelWidget, setupGravityWidget);

    connect(ui->drawBaseCheckBox, &QCheckBox::stateChanged, myGLWidget, &MyGLWidget::on_new_drawBase_state);
    connect(ui->containerComboBox, &QComboBox::currentIndexChanged, myGLWidget, &MyGLWidget::on_new_container_visual_parameter);

    connect(ui->playPushButton, &QAbstractButton::released, myGLWidget, &MyGLWidget::play);
    connect(ui->stopPushButton, &QAbstractButton::released, myGLWidget, &MyGLWidget::stop);

    connect(ui->timeStepField, &QLineEdit::textChanged, myGLWidget, &MyGLWidget::on_new_timestep);

    connect(animator, &AnimationWidget::updateView, myGLWidget, &MyGLWidget::on_new_data);

    MessagePresenter::getInstance().SetLabel(ui->messageLabel);
    MessagePresenter::getInstance().AddMessage("SandPandaDesign");
}

MainWindow::~MainWindow()
{
    delete ui;
}
