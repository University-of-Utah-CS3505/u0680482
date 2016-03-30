#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
// Qt Graphics objects
#include <QPushButton>
#include <QToolButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSlider>
#include <QLabel>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QFileDialog>
// Other Qt Objects
#include <QCloseEvent>
#include <QString>
// from Qt-Color-Widgets library
#include <ColorDialog>
#include <ColorWheel>

#include "editor_model.h"
#include "newfiledialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget * parent = 0);
    ~MainWindow();

public slots:

private:
    Ui::MainWindow *ui;
    QGraphicsScene* scene;
    editor_model model;

    void connectSignalsAndSlots();
    void initializeUIDefaults();

private slots:
    void playbackSpeed_hSlider_moved(int value);
    void menuNewFile_triggered();
    void menuOpen_triggered();
    void menuSave_triggered();
    void menuSaveAs_triggered();
    void menuExportAs_triggered();
    void menuHelp_triggered();
    void colorWheel_colorChanged(QColor color);

protected:
    virtual void closeEvent(QCloseEvent *event);

};

#endif // MAINWINDOW_H
