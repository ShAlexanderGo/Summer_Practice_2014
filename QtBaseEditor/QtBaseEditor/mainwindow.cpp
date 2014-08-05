#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //настройка показа лиц
    facesModel = new QStandardItemModel;
    ui->facesView->setModel(facesModel);
   // ui->facesView->selectionMode()

    //настройка показа базы
    model = new QFileSystemModel;
    model->setFilter(QDir::NoDotAndDotDot | QDir::Files);
    QStringList filters;
    filters << "*.jpg";
    model->setNameFilters(filters);
    model->setNameFilterDisables(false);
    model->setRootPath("C:\\Users\\с\\Desktop\\MyOwnFaceBase");
    ui->baseView->setModel(model);
    ui->baseView->setRootIndex(model->index("C:\\Users\\с\\Desktop\\MyOwnFaceBase"));

    //настройка всякого
    ui->label->setAlignment(Qt::AlignTop);
    imageSelected = false;
    descriptionFound = false;

    //настройка реакций
    this->connect(ui->baseView->selectionModel(),
                  SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
                  this,
                  SLOT(reactionBaseSelectionChanged()));
    this->connect(ui->runVJ,
                  SIGNAL(released()),
                  this,
                  SLOT(runViolaJones()));
    this->connect(ui->delFace,
                  SIGNAL(released()),
                  this,
                  SLOT(deleteFace()));
    this->connect(ui->facesView->selectionModel(),
                  SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
                  this,
                  SLOT(reactionFacesSelectionChanged()));

    cascade.load("C:\\123\\C++\\Libraries\\OpenCV\\sources\\data\\haarcascades\\haarcascade_frontalface_alt.xml");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::reactionBaseSelectionChanged() {
    //очищаем всё
    faces.clear();
    image.release();
    ui->label->setText("");
    ui->labelDescr->setText("");
    //получаем выделенный элемент
    QModelIndexList indexList = ui->baseView->selectionModel()->selectedIndexes();
    if(indexList.size() > 0) {
        QModelIndex index = indexList.at(0);
        //читаем файл изображения
        QString fileName = model->filePath(index);
        std::string stringFileName = fileName.toLocal8Bit().constData();
        image = cv::imread(stringFileName);
        cv::cvtColor(image, image, CV_BGR2GRAY);
        cv::equalizeHist(image, image);
        pmImage.load(fileName);
        //загружаем файл-описание
        fileName.remove(fileName.size() - 4, 4);
        QFile file(fileName);
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        if(file.exists()) {
            QTextStream in(&file);
            int x, y, width, height;
            while(true) {
                in >> x >> y >> width >> height;
                if ((width == 0) && (height == 0)) break;
                faces.push_back(cv::Rect(x, y, width, height));
            }
            descriptionFound = true;
        } else {
            descriptionFound = false;
        }
        imageSelected = true;
    } else {
        imageSelected = false;
    }
    //обновляем вид
    updateFacesList();
    updateAppearance();
    ui->runVJ->setEnabled(true);
}

void MainWindow::updateFacesList()
{
    //обновляем список лиц
    facesModel->clear();
    for(unsigned int i = 0; i < faces.size(); i++) {
        QString stringFace = QString::number(faces[i].x)
                + " " + QString::number(faces[i].y)
                + " " + QString::number(faces[i].width)
                + " " + QString::number(faces[i].height);
        QStandardItem* item = new QStandardItem(stringFace);
        facesModel->appendRow(item);
    }
}

void MainWindow::updateAppearance()
{
    if(!imageSelected) return;
    //копируем оригинальное изображение
    pmImageToWindow = pmImage.copy();
    if((pmImageToWindow.width() == 0) || (pmImageToWindow.height() == 0))
        return;
    //рисуем все лица
    QPainter *paint = new QPainter(&pmImageToWindow);
    paint->setPen(QPen(Qt::green, 3));
    for(unsigned int i = 0; i < faces.size(); i++) {
        paint->drawRect(faces[i].x, faces[i].y, faces[i].width, faces[i].height);
    }
    //рисуем выделенное лицо
    paint->setPen(QPen(Qt::red, 3));
    QModelIndexList indexList = ui->facesView->selectionModel()->selectedIndexes();
    if(indexList.size() > 0) {
        QModelIndex index = indexList.at(0);
        int j = index.row();
        paint->drawRect(faces[j].x, faces[j].y, faces[j].width, faces[j].height);
    }
    //рисуем превью нового лица
    if(ui->showPr->isChecked()) {
        paint->setPen(QPen(Qt::blue, 3));
        paint->drawRect(ui->inputX->value(), ui->inputY->value(),
                        ui->inputWidth->value(), ui->inputHeight->value());
    }
    delete paint;
    //рисуем изображение в окно
    int imW = pmImageToWindow.width();
    int imH = pmImageToWindow.height();
    int labW = ui->label->width();
    int labH = ui->label->height();
    if((imW > labW) || (imH > labH))
        ui->label->setPixmap(pmImageToWindow.scaled(labW, labH, Qt::KeepAspectRatio));
    else
        ui->label->setPixmap(pmImageToWindow);
    //обновляем labelDescr
    if(descriptionFound)
        ui->labelDescr->setText("");
    else
        ui->labelDescr->setText("Description file not found");
}

void MainWindow::resizeEvent(QResizeEvent *) {
    ui->label->resize(this->width() - 260, this->height() - 20);
    updateAppearance();
}


void MainWindow::runViolaJones()
{
    if(!imageSelected) return;
    if(image.empty()) return;
    double scaleFactor = ui->inputScF->value();
    int minNeighbors = ui->inputMinN->value();
    int minSize = ui->inputMinSize->value();
    cascade.detectMultiScale(image, faces, scaleFactor, minNeighbors, 0, cv::Size(minSize, minSize));
    updateFacesList();
    updateAppearance();
}

void MainWindow::reactionFacesSelectionChanged()
{
    updateAppearance();
}

void MainWindow::deleteFace()
{
    QModelIndexList list = ui->facesView->selectionModel()->selectedIndexes();
    if(list.size() <= 0) return;
    QModelIndex index = list.at(0);
    int j = index.row();
    faces.erase(faces.begin() + j);
    updateFacesList();
    updateAppearance();
}

void MainWindow::on_renameAll_clicked()
{
    QDir dir("C:\\Users\\с\\Desktop\\MyOwnFaceBase\\");
    dir.setFilter(QDir::NoDotAndDotDot | QDir::Files);
    QStringList filters;
    filters << "*.jpg";
    dir.setNameFilters(filters);
    QStringList list = dir.entryList();
    for(int i = 0; i < list.size(); i++) {
        QString path = list.at(i);
        QFile::rename(dir.absoluteFilePath(path),
                      dir.absoluteFilePath("1" + path));
        path.remove(path.size() - 4, 4);
        QFile::rename(dir.absoluteFilePath(path),
                      dir.absoluteFilePath("1" + path));
    }
    for(int i = 0; i < list.size(); i++) {
        QString path = list.at(i);
        QFile::rename(dir.absoluteFilePath("1" + path),
                      dir.absoluteFilePath("img_" + QString::number(i) + ".jpg"));
        path.remove(path.size() - 4, 4);
        QFile::rename(dir.absoluteFilePath("1" + path),
                      dir.absoluteFilePath("img_" + QString::number(i)));
    }
}

void MainWindow::on_delDescr_clicked()
{
    ui->labelDescr->setText(QString("Description file not found"));
    descriptionFound = false;
    QModelIndex index = ui->baseView->selectionModel()->currentIndex();
    QString fileName = model->filePath(index);
    fileName.remove(fileName.size() - 4, 4);
    QFile file(fileName);
    if(file.exists())
        file.remove();
}

void MainWindow::on_saveDescr_clicked()
{
    ui->labelDescr->setText("");
    descriptionFound = true;
    QModelIndex index = ui->baseView->selectionModel()->currentIndex();
    QString fileName = model->filePath(index);
    fileName.remove(fileName.size() - 4, 4);
    QFile file(fileName);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    for(unsigned int i = 0; i < faces.size(); i++) {
        out << faces[i].x << " " << faces[i].y << " " << faces[i].width
               << " " << faces[i].height << '\n';
    }
    file.close();
}

void MainWindow::on_addFace_clicked()
{
    faces.push_back(cv::Rect(ui->inputX->value(), ui->inputY->value(),
                             ui->inputWidth->value(), ui->inputHeight->value()));
    updateFacesList();
    updateAppearance();
}

void MainWindow::on_inputX_valueChanged(int arg1)
{
    updateAppearance();
}

void MainWindow::on_inputY_valueChanged(const QString &arg1)
{
    updateAppearance();
}

void MainWindow::on_inputWidth_valueChanged(int arg1)
{
    updateAppearance();
}

void MainWindow::on_inputHeight_valueChanged(int arg1)
{
    updateAppearance();
}

void MainWindow::on_showPr_clicked()
{
    updateAppearance();
}

void MainWindow::on_delIm_clicked()
{
    QModelIndexList list = ui->baseView->selectionModel()->selectedIndexes();
    QModelIndex index = list.at(0);
    if(!index.isValid()) return;
    QString fileName = model->filePath(index);
    QFile file(fileName);
    file.remove();
    fileName.remove(fileName.size() - 4, 4);
    QFile fileD(fileName);
    if(fileD.exists())
        fileD.remove();
    faces.clear();
    image.release();
    ui->baseView->clearSelection();
    ui->label->setText("");
    ui->labelDescr->setText("");
}
