#include "clickablelabel.h"



ClickableLabel::ClickableLabel(QWidget* parent)
    : QLabel(parent) {}

void ClickableLabel::mousePressEvent(QMouseEvent* event) {
    emit clicked();  // Emit the clicked signal when the label is clicked
}
