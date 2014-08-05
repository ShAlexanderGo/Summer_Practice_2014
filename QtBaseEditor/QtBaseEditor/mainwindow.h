#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ocvprocessor.h"

#include <QFile>
#include <QFileSystemModel>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QIODevice>
#include <QLabel>
#include <QMainWindow>
#include <QPainter>
#include <QPen>
#include <QPixmap>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QTextStream>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_renameAll_clicked();

    void on_delDescr_clicked();

    void on_saveDescr_clicked();

    void on_addFace_clicked();

    void on_inputX_valueChanged(int arg1);

    void on_inputY_valueChanged(const QString &arg1);

    void on_inputWidth_valueChanged(int arg1);

    void on_inputHeight_valueChanged(int arg1);

    void on_showPr_clicked();

    void on_delIm_clicked();

    void deleteFace();
    void reactionBaseSelectionChanged();
    void reactionFacesSelectionChanged();
    void runViolaJones();

private:
    Ui::MainWindow* ui;

    QFileSystemModel* model;
    QStandardItemModel* facesModel;

    void resizeEvent(QResizeEvent *);

    cv::CascadeClassifier cascade;
    cv::Mat image;
    std::vector<cv::Rect> faces;

    QPixmap pmImage;
    QPixmap pmImageToWindow;

    void updateFacesList();
    void updateAppearance();

    bool imageSelected;
    bool descriptionFound;
};

#endif // MAINWINDOW_H
