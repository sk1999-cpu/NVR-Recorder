



#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QLabel>
#include <QWidget>
#include <Qt>

class ClickableLabel : public QLabel {
    Q_OBJECT

public:
    explicit ClickableLabel(QWidget* parent = nullptr);

signals:
    void clicked();  // Signal emitted when the label is clicked

protected:
    void mousePressEvent(QMouseEvent* event);  // Override the mousePressEvent
};

#endif // CLICKABLELABEL_H
