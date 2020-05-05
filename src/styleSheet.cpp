#include "mainwindow.h"

void MainWindow::initStyleSheet()
{
    this->setStyleSheet(
            "QPushButton#maskButton {border-style: "
            "outset; border-width: 3px; border-color: #9C9C9C; padding: 10px; "
            "background-color: #EEEEEE; border-radius: 15px;} "
            "QPushButton#maskButton:pressed {border-style: ridge; "
            "border-width: 2px; background-color: #E3E3E3;} "
            "QPushButton#mainButton {background-color: qlineargradient(x1:0, "
            "y1:0, x2:1, y2:1, stop: 0 #DADADA, "
            "stop: 0.52 WhiteSmoke, stop: 0.97 #DADADA); border-style: none; "
            "padding: 7px;} "
            "QPushButton#mainButton:hover {background-color: "
            "qlineargradient(x1:0, "
            "y1:0, x2:1, y2:1, stop: 0 #CFCFCF, "
            "stop: 0.52 WhiteSmoke, stop: 0.97 #CFCFCF);} "
            "QPushButton#mainButton:pressed {background-color: "
            "qlineargradient(x1:0, y1:0, x2:1, y2:1, stop: 0 #EAEAEA, "
            "stop: 0.52 #DADADA, stop: 0.97 #EAEAEA);} "
            "QFrame#maskButtonFrame {background-color: #E6E6E6; border: 1px; "
            "border-radius: 3px; "
            "border-style: inset; border-width: 2px; "
            "border-color: #c0c0c0;} "
            "QLabel {font-size: 13px} "
            "QLineEdit {border: 2px #BFBFBF; border-radius: 3px; "
            "border-style: inset; border-width: 2px; "
            "selection-background-color: gray; background-color: #FEFEFE;} "
            "MainWidget {border: 2px Gainsboro; border-radius: 3px;"
            "border-style: inset; selection-background-color: "
            "qlineargradient(x1:0, y1:0, x2:0, y2:2, stop: 0 Gainsboro, stop: "
            "0.25 white, stop: 0.5 Gainsboro); selection-color: black; "
            "background-color: #F7F7F7; text-align: center;} ");
}

QString MainWindow::widgetStyleSheet()
{
    return QString(
            "QHeaderView::section {background-color: #F4F4F4; border-style: "
            "none; border-bottom: 1px outset #E5E5E5; font-size: 14px; "
            "border-right: 2px outset #E7E7E7;} "
            "QHeaderView::section:checked {font-weight: normal;}"
            "QHeaderView {background-color: #F5F5F5;}");
}

std::pair<QString, QString> MainWindow::insertStyleSheet()
{
    return std::make_pair(
            QString("QPushButton {background-color: "
                    "#EAEAEA; border: 2px outset "
                    "#A1A1A1; padding: 5px;} "
                    "QPushButton:pressed {background-color: #E5E5E5; border: "
                    "1px "
                    "ridge "
                    "#A1A1A1;} "
                    "PushInsert {border: 2px inset #A1A1A1; border-radius: "
                    "3px;}"),
            QString("QHeaderView::section {background-color: #F0F0F0;} "
                    "QHeaderView {background-color: #F0F0F0;} "
                    "background-color: #F0F0F0;"));
}
