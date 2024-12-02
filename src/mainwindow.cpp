#include "mainwindow.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_label(nullptr)
{
    setupUi();
}

MainWindow::~MainWindow() = default;

void MainWindow::setupUi()
{
    setWindowTitle("Darxi Network");
    
    // Create central widget and layout
    auto *centralWidget = new QWidget(this);
    auto *layout = new QVBoxLayout(centralWidget);
    
    // Add a label
    m_label = new QLabel("Welcome to Darxi!", centralWidget);
    layout->addWidget(m_label);
    
    // Set central widget
    setCentralWidget(centralWidget);
    
    // Set window size
    resize(800, 600);
}