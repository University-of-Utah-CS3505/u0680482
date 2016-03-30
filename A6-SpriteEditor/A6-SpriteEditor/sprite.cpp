#include "sprite.h"

/**
 * Constructor
 *
 * @brief sprite::sprite
 * @param parent
 */
sprite::sprite(QObject *parent) :
    QObject(parent), width(0), height(0), file_saved(false), sprite_title("New Sprite")
{

}

sprite::sprite(int width_, int height_, QString title_, QObject *parent) :
    QObject(parent), width(width_), height(height_), file_saved(false),
    sprite_title(title_)
{

}

/**
 * Returns the number of frames in the sprite.
 *
 * @brief sprite::getAnimationLength
 * @return
 */
int sprite::getAnimationLength()
{
    return frames.length();
}

///**
// * @brief sprite::getFrame
// * @param index
// * @return
// */
//frame sprite::getFrame(int index)
//{

//}

///**
// * @brief sprite::addFrame
// * @return
// */
//frame sprite::addFrame()
//{

//}

/**
 * @brief sprite::removeFrame
 * @param index
 */
void sprite::removeFrameAt(int index)
{
//    frames.removeAt(index);
}

/**
 * @brief sprite::getWidth
 * @return
 */
int sprite::getWidth()
{
    return width;
}

/**
 * @brief sprite::getHeight
 * @return
 */
int sprite::getHeight()
{
    return height;
}

/**
 * @brief sprite::getFileSavedStatus
 * @return
 */
bool sprite::getFileSavedStatus()
{
    return file_saved;
}

/**
 * @brief sprite::setFileSavedStatus
 * @param status
 */
void sprite::setFileSavedStatus(bool status)
{
    file_saved = status;
}
