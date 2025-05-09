#include "Canvas.h"

Canvas::Canvas(unsigned int width, unsigned int height, const std::string& title)
    : m_window(sf::VideoMode(width, height), title)
{
}

sf::RenderWindow& Canvas::GetWindow()
{
    return m_window;
}

sf::Color Canvas::ToSfColor(std::uint32_t color)
{
    return sf::Color(
        (color >> 16) & 0xFF,
        (color >> 8) & 0xFF,
        color & 0xFF
    );
}

void Canvas::DrawLine(Point from, Point to, std::uint32_t lineColor)
{
    sf::Vertex line[] = {
        sf::Vertex(sf::Vector2f(from.GetX(), from.GetY()), ToSfColor(lineColor)),
        sf::Vertex(sf::Vector2f(to.GetX(), to.GetY()), ToSfColor(lineColor))
    };
    m_window.draw(line, 2, sf::Lines);
}

void Canvas::FillPolygon(std::vector<Point> points, std::uint32_t fillColor)
{
    sf::ConvexShape polygon;
    polygon.setPointCount(points.size());
    for (size_t i = 0; i < points.size(); ++i)
        polygon.setPoint(i, sf::Vector2f(points[i].GetX(), points[i].GetY()));
    polygon.setFillColor(ToSfColor(fillColor));
    m_window.draw(polygon);
}

void Canvas::DrawCircle(Point center, double radius, std::uint32_t lineColor)
{
    sf::CircleShape circle(radius);
    circle.setPosition(center.GetX() - radius, center.GetY() - radius);
    circle.setFillColor(sf::Color::Transparent);
    circle.setOutlineThickness(1);
    circle.setOutlineColor(ToSfColor(lineColor));
    m_window.draw(circle);
}

void Canvas::FillCircle(Point center, double radius, std::uint32_t fillColor)
{
    sf::CircleShape circle(radius);
    circle.setPosition(center.GetX() - radius, center.GetY() - radius);
    circle.setFillColor(ToSfColor(fillColor));
    m_window.draw(circle);
}

void Canvas::DrawRectangle(Point topLeft, double width, double height, std::uint32_t lineColor)
{
    sf::RectangleShape rect(sf::Vector2f(width, height));
    rect.setPosition(topLeft.GetX(), topLeft.GetY());
    rect.setFillColor(sf::Color::Transparent);
    rect.setOutlineThickness(1);
    rect.setOutlineColor(ToSfColor(lineColor));
    m_window.draw(rect);
}

void Canvas::FillRectangle(Point topLeft, double width, double height, std::uint32_t fillColor)
{
    sf::RectangleShape rect(sf::Vector2f(width, height));
    rect.setPosition(topLeft.GetX(), topLeft.GetY());
    rect.setFillColor(ToSfColor(fillColor));
    m_window.draw(rect);
}

void Canvas::DrawTriangle(Point vertex1, Point vertex2, Point vertex3, std::uint32_t lineColor)
{
    sf::ConvexShape triangle;
    triangle.setPointCount(3);
    triangle.setPoint(0, sf::Vector2f(vertex1.GetX(), vertex1.GetY()));
    triangle.setPoint(1, sf::Vector2f(vertex2.GetX(), vertex2.GetY()));
    triangle.setPoint(2, sf::Vector2f(vertex3.GetX(), vertex3.GetY()));
    triangle.setFillColor(sf::Color::Transparent);
    triangle.setOutlineThickness(1);
    triangle.setOutlineColor(ToSfColor(lineColor));
    m_window.draw(triangle);
}

void Canvas::FillTriangle(Point vertex1, Point vertex2, Point vertex3, std::uint32_t fillColor)
{
    sf::ConvexShape triangle;
    triangle.setPointCount(3);
    triangle.setPoint(0, sf::Vector2f(vertex1.GetX(), vertex1.GetY()));
    triangle.setPoint(1, sf::Vector2f(vertex2.GetX(), vertex2.GetY()));
    triangle.setPoint(2, sf::Vector2f(vertex3.GetX(), vertex3.GetY()));
    triangle.setFillColor(ToSfColor(fillColor));
    m_window.draw(triangle);
}
