//
// Created by Ruhaan on 12/08/25.
//

#include "socketGraphics.h"
#include "../../core/nodes/socket.h"
#include "nodeGraphics.h"

#include <QPainter>
#include <qtextstream.h>
#include <random>
#include <sstream>

SocketGraphics::SocketGraphics(SocketNode *socket, const std::string& label, NodeGraphics *parent)
    : QGraphicsItem(parent), socket(socket), label(label) {


    if (socket) {
        int idx = 0;
        if (socket->position == LEFT_TOP || socket->position == LEFT_BOTTOM) {
            idx = 0;
        } else {
            idx = 2;
        }
        _color_background = getSocketColor(idx);
    } else {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 6);
        int idx = dis(gen);
        _color_background = getSocketColor(idx);
    }

    _color_outline = QColor("#2C3E50");
    _pen = QPen(_color_outline);
    _pen.setWidthF(outline_width);
    _brush = QBrush(_color_background);
}

void SocketGraphics::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setRenderHint(QPainter::Antialiasing);

    if (socket && socket->hasEdge()) {
        painter->setPen(Qt::NoPen);
        painter->setBrush(QColor(_color_background.red(),
                                _color_background.green(),
                                _color_background.blue(), 70));
        painter->drawEllipse(-radius-3, -radius-3, 2*(radius+3), 2*(radius+3));
    }

    painter->setBrush(_brush);
    painter->setPen(_pen);
    painter->drawEllipse(-radius, -radius, 2 * radius, 2 * radius);

    int margin = 4;
    QString labelText = QString::fromStdString(label);

    QFont labelFont = painter->font();
    labelFont.setPointSize(9);
    painter->setFont(labelFont);

    QFontMetrics fm(labelFont);
    int textWidth = fm.horizontalAdvance(labelText);
    int textHeight = fm.height();
    int y = textHeight / 3;
    if (socket && (socket->position == LEFT_TOP || socket->position == LEFT_BOTTOM)) {
        painter->setPen(Qt::white);
        painter->drawText(radius + margin, y, labelText);
    } else if (socket && (socket->position == RIGHT_TOP || socket->position == RIGHT_BOTTOM)) {
        painter->setPen(Qt::white);
        painter->drawText(-(textWidth + radius + margin), y, labelText);
    }
}

QRectF SocketGraphics::boundingRect() const {
    return {-radius - outline_width, -radius - outline_width,
        3 * (radius - outline_width), 3 * (radius - outline_width)};
}


std::string SocketGraphics::str() {
    std::ostringstream oss;
    oss << "\t <SocketGraphics " <<  std::hex << reinterpret_cast< uintptr_t>(this) << ">";
    return oss.str();
}
