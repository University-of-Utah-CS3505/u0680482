#ifndef SPRITE_H
#define SPRITE_H

// Qt Graphics Objects
#include <QObject>
#include <QList>
// Other Qt Objects
#include <QString>

#include "frame.h"

class Sprite : public QObject
{
    Q_OBJECT
public:

    explicit Sprite(QObject *parent = 0);
    explicit Sprite(int width_, int height_, QObject * parent = 0);
    ~Sprite();

    // Accessor methods
    int getAnimationLength();
    Frame* getFrameAt(int index);
    QList<Frame*> getFrames();
    int getWidth();
    int getHeight();
    bool getFileSavedStatus();
    void setFileSavedStatus(bool status);

    void addFrame(Frame* frame);
    void removeFrameAt(int index);
    void setCurrentFrame(int index);
    int getCurrentFrame();
    void setPixelColorAtCurrentFrame(int x, int y, QColor color);
    QColor getPixelColorAtCurrentFrame(int x, int y);
    void rotateCurrentFrame(bool direction);
    void flipCurrentFrameOrientation(bool orientation);
    void invertCurrentFrameColor();

    // Save to file method
    QString toString();

private:
    QList<Frame*> frames;
    int currentFrame;
    int width;
    int height;

    // Move to model
    bool file_saved;

signals:

public slots:

};

#endif // SPRITE_H
