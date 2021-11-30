#include "RectCollider.h"

RectCollider::RectCollider(float x, float y, float w, float h) {
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}

void RectCollider::move(float x, float y) {
    this->x += x;
    this->y += y;
}

bool RectCollider::isColliding(RectCollider othr) {
    return (this->x < othr->x + othr->w &&
            this->x + this->w > othr->x &&
            this->y < othr->y + othr->h &&
            this->h + this->y > othr->y)
}