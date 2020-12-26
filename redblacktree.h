#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include <QMainWindow>

#include <QIntValidator>
#include "redblacktreeimp.h"

QT_BEGIN_NAMESPACE
namespace Ui { class RedBlackTree; }
QT_END_NAMESPACE

class RedBlackTree : public QMainWindow
{
    Q_OBJECT

public:
    RedBlackTree(QWidget *parent = nullptr);
    ~RedBlackTree();

private:
    Ui::RedBlackTree *ui;
    redBlackTree tree;
private slots:
    void BPressed();

};
#endif // REDBLACKTREE_H
