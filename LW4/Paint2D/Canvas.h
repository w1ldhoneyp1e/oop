#pragma once
#include "ICanvas.h"
#include <SFML/Graphics.hpp>

class Canvas : public ICanvas
{
private:
    sf::RenderWindow m_window;
public:
    Canvas(unsigned int width = 800, unsigned int height = 600, const std::string& title = "Paint2D");

    void DrawLine(Point from, Point to, std::uint32_t lineColor) override;
    void FillPolygon(std::vector<Point> points, std::uint32_t fillColor) override;
    void DrawCircle(Point center, double radius, std::uint32_t lineColor) override;
    void FillCircle(Point center, double radius, std::uint32_t fillColor) override;
    void DrawRectangle(Point topLeft, double width, double height, std::uint32_t lineColor) override;
    void FillRectangle(Point topLeft, double width, double height, std::uint32_t fillColor) override;
    void DrawTriangle(Point vertex1, Point vertex2, Point vertex3, std::uint32_t lineColor) override;
    void FillTriangle(Point vertex1, Point vertex2, Point vertex3, std::uint32_t fillColor) override;

    sf::RenderWindow& GetWindow();

private:
    sf::Color ToSfColor(std::uint32_t color);
};

