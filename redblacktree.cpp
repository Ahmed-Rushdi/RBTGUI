#include "redblacktree.h"
#include "ui_redblacktree.h"


RedBlackTree::RedBlackTree(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::RedBlackTree)
{
    ui->setupUi(this);
    ui->InputField->setValidator(new QIntValidator(INT_MIN,INT_MAX,this));
    ui->imglabel->setMinimumSize(20, 20);
    QString names[4] = {"InsertButton","DeleteButton","ClearButton","FitButton"};
    QPushButton *CButtons[4];
    for (int i = 0; i<4 ;i++ ) {
        CButtons[i] = RedBlackTree::findChild<QPushButton*>(names[i]);
        connect(CButtons[i],SIGNAL(released()),this,SLOT(BPressed()));
    }
//    ui->imglabel->setText(QString::fromStdString(tree.get_current_dir()));
}

RedBlackTree::~RedBlackTree()
{
    delete ui;
}

void RedBlackTree::BPressed(){
    QPushButton *button = (QPushButton*) sender();
    QString butname = button->text();
    QString Inputval = ui->InputField->text();

    if(butname == "Insert"){
        tree.insert(Inputval.toInt());
        tree.print();
    } else if(butname == "Delete"){
        tree.Delete(Inputval.toInt());
        tree.print();
    } else if(butname=="Clear"){
        tree.clear();
        ui->imglabel->setPixmap(QPixmap("src\\white.png"));
    }
    if(butname != "Fit"){
        ui->InputField->setText("0");
    }
    if(butname != "Clear"){
        QPixmap * mypix = new QPixmap("src\\RBT.dot.png");
        int w = ui->imglabel->width();
        int h = ui->imglabel->height();
        if(mypix->width() <= w && mypix->height() <= h){
            ui->imglabel->setPixmap(*mypix);
        }else{
            ui->imglabel->setPixmap(mypix->scaled(w,h,Qt::KeepAspectRatio,Qt::SmoothTransformation));
        }
    }
}


