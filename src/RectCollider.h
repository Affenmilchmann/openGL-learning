class RectCollider {
    public:
        Rect(float x, float y, float w, float h);

        void move(float x, float y);
        bool isColliding(RectCollider another);
    private:
        float x, y, w, h;
};