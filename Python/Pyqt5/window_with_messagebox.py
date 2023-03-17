#! /usr/bin/python3
"""
a window with message box
"""
import sys
from PyQt5.QtWidgets import QApplication,QWidget,QMessageBox
from PyQt5.QtGui import QIcon

class Example(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):

        self.setGeometry(300,300,200,150)
        self.setWindowTitle('Message Box')
        self.setWindowIcon(QIcon('you.png'))

        self.show()
    def closeEvent(self,event):
        reply = QMessageBox.question(self,'Message',"Are you sure to quit?",
        QMessageBox.Yes|QMessageBox.No,QMessageBox.No)

        if reply == QMessageBox.Yes:
            event.accept()
        else:
            event.ignore()

if __name__ == '__main__':
    app = QApplication(sys.argv)
    ex = Example()
    sys.exit(app.exec_())
