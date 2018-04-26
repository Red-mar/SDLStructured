#ifndef SHAPES_H
#define SHAPES_H

class Point
{
    public:
        float x;
        float y;

        Point();
        Point(float x, float y);
};

struct Rectangle
{
    float x;
    float y;
    int w;
    int h;
    
    float top;
    float bottom;
    float leftmost;
    float rightmost;

    Point center;
	Point leftCenter;
	Point rightCenter;
	Point topLeft;
	Point topRight;
	Point topCenter;
	Point bottomLeft;
	Point bottomRight;
	Point bottomCenter;

    Rectangle(float x, float y, int w, int h);

    Rectangle(Point topLeft, Point bottomRight);

	Rectangle(Rectangle* other);

	Rectangle();

    void copy(Rectangle* other);

    void addX(float xAdd);
    void addY(float yAdd);
    void setX(float xSet);
    void setY(float ySet);
    void stretch(float scale);
	void stretch(float scaleX, float scaleY);
    void update();
    bool overlaps(Rectangle other);
    bool overlaps(Rectangle* other);
    void placeOnTop(Rectangle* other);
};

struct Circle
{
	float x;
	float y;
	int r; /// Radius

	float centerX;
	float centerY;

	/// Creates a nice circle with `x` and `y` coordinates and `r`
	/// radius.
	Circle(float x, float y, int r);

	/// Adds to the current x.
	///
	/// @note Although this seems useless, you must call this
	///       instead of directly modifying x because it
	///       refreshes internal points.
	///
	void addX(float xAdd);

	/// Adds to the current y.
	///
	/// @note Although this seems useless, you must call this
	///       instead of directly modifying y because it
	///       refreshes internal points.
	///
	void addY(float yAdd);
};

#endif // !SHAPES_H
