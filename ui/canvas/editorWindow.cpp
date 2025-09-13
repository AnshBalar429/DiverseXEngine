//
// Created by Ruhaan on 29/08/25.
//

#include "editorWindow.h"
#include "syshighlighter.h"
#include "../../core/scene/nodescene.h"

#include <QLabel>
#include <QHBoxLayout>
#include <QFrame>
#include <QKeyEvent>
#include <QDebug>

static constexpr const char* textEditstyle = R"(QTextEdit {
  border-radius: 8px;
  background-color: #21252b;
  border: 1px solid #3E4451;
  padding: 8px;
  color: #ABB2BF;
  font-family: 'Menlo', 'Monaco', 'Courier New', monospace;
  font-size: 12px;
  line-height: 1.5;
}
QScrollBar:vertical {
  background-color: #282c34;
  width: 12px;
  margin: 0px;
}
QScrollBar::handle:vertical {
  background-color: #4B5363;
  border-radius: 6px;
  min-height: 20px;
}
QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {
  height: 0px;
}
QScrollBar:horizontal {
  background-color: #282c34;
  height: 12px;
  margin: 0px;
}
QScrollBar::handle:horizontal {
  background-color: #4B5363;
  border-radius: 6px;
  min-width: 20px;
}
QScrollBar::add-line:horizontal, QScrollBar::sub-line:horizontal {
  width: 0px;
})";

EditorWindow::EditorWindow(QWidget* parent) : QWidget(parent) {
    setFixedWidth(420);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(10, 10, 10, 10);
    mainLayout->setSpacing(8);

    setStyleSheet("background-color: #282c34;");

    splitter = new QSplitter(Qt::Vertical, this);
    splitter->setHandleWidth(2);
    splitter->setStyleSheet("QSplitter::handle { background-color: #3E4451; }");

    QWidget* importsSection = createSectionWithTitle("Imports");
    QWidget* functionsSection = createSectionWithTitle("Functions");
    QWidget* mainSection = createSectionWithTitle("Main");

    splitter->addWidget(importsSection);
    splitter->addWidget(functionsSection);
    splitter->addWidget(mainSection);

    QList<int> sizes;
    sizes << 10 << 70 << 10;
    splitter->setSizes(sizes);

    mainLayout->addWidget(splitter);
    setLayout(mainLayout);

    if (importsEdit) importsEdit->installEventFilter(this);
    if (functionsEdit) functionsEdit->installEventFilter(this);
    if (mainEdit) mainEdit->installEventFilter(this);

    if (importsEdit) {
        new PythonSyntaxHighlighter(importsEdit->document());
    }
    if (functionsEdit) {
        new PythonSyntaxHighlighter(functionsEdit->document());
    }
    if (mainEdit) {
        new PythonSyntaxHighlighter(mainEdit->document());
    }
}

QWidget* EditorWindow::createSectionWithTitle(const QString& title) {
    QWidget* container = new QWidget(this);
    container->setStyleSheet("background-color: #282c34; border-radius: 8px;");

    QVBoxLayout* layout = new QVBoxLayout(container);
    layout->setContentsMargins(4, 4, 4, 4);
    layout->setSpacing(4);

    QLabel* titleLabel = new QLabel(title, container);
    QFont titleFont = titleLabel->font();
    titleFont.setBold(true);
    titleFont.setPointSize(12);
    titleLabel->setFont(titleFont);
    titleLabel->setStyleSheet("color: #61AFEF; padding: 3px;");

    QTextEdit* textEdit = new QTextEdit(container);

    textEdit->setReadOnly(true);
    textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    textEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    textEdit->setStyleSheet(textEditstyle);

    if (title == "Imports") {
        importsEdit = textEdit;
    } else if (title == "Functions") {
        functionsEdit = textEdit;
    } else if (title == "Main") {
        mainEdit = textEdit;
    }

    if (textEdit) textEdit->installEventFilter(this);

    layout->addWidget(titleLabel);
    layout->addWidget(textEdit);

    return container;
}

bool EditorWindow::eventFilter(QObject *watched, QEvent *event) {
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);

        if ((keyEvent->modifiers() & Qt::MetaModifier) && keyEvent->key() == Qt::Key_Return) {

            if (scene) {
                scene->updateEditorCode();
                return true;
            }
        }
    }

    return QWidget::eventFilter(watched, event);
}

void EditorWindow::setImportsText(const QString& text) {
    if (importsEdit) {
        importsEdit->setText(text);
    }
}

void EditorWindow::setFunctionsText(const QString& text) {
    if (functionsEdit) {
        functionsEdit->setText(text);
    }
}

void EditorWindow::setMainText(const QString& text) {
    if (mainEdit) {
        mainEdit->setText(text);
    }
}
