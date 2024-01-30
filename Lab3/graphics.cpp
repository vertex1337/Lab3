
#include "graphics.h"
#include "math.h"
using namespace Grfx;

Graphics::Graphics()
{
    
    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    hWnd = GetConsoleWindow();
    hDC = GetDC(hWnd);
    gr = new Gdiplus::Graphics(hDC); 
    

    Gdiplus::Color blackColor(255, 0, 0, 0);
    gr->Clear(blackColor);
    windowSize();

}
Graphics::~Graphics()
{
    delete gr;
    Gdiplus::GdiplusShutdown(gdiplusToken);
    ReleaseDC(hWnd, hDC);
}

void Graphics::setcolor(int c)
{
    BYTE byRed = 0, byGreen = 0, byBlue = 0;
    byRed = 255 * (c & 0x4);
    byGreen = 255 * (c & 0x2);
    byBlue = 255 * (c & 0x1);
    color = Gdiplus::Color(255, byRed, byGreen, byBlue);
}

void Graphics::line(int x, int y, int x2, int y2)
{
    Gdiplus::Pen      pen(color);
    gr->DrawLine(&pen, x, y, x2, y2);
}

void Graphics::circle(int x, int y, int r)
{
    Gdiplus::SolidBrush brush(color);
    gr->FillEllipse(&brush, x-r, y-r, r * 2, r * 2);
}
void Graphics::rectangle(int x, int y, int w, int h)
{
    Gdiplus::SolidBrush      brush(color);
    gr->FillRectangle(&brush, x, y, w, h);

}

void Graphics::star(int x, int y, int r)
{
    Gdiplus::SolidBrush brush(color);

    Gdiplus::PointF points[10]; 
    float angle = 0.0f;
    float angleIncrement = 36.0f;
    for (int i = 0; i < 10; ++i)
    {
        float outerRadius = (i % 2 == 0) ? r : r / 2.0f;
        points[i].X = x + outerRadius * cos(angle * 3.14159f / 180.0f);
        points[i].Y = y + outerRadius * sin(angle * 3.14159f / 180.0f);
        angle += angleIncrement;
    }

    gr->FillPolygon(&brush, points, 10); 
}

// 2017-04-01 11:50 alkhizha
void Graphics::cls()
{
    gr->Clear(Gdiplus::Color(0, 0, 0, 0));
}
void Graphics::windowSize()
{
    Gdiplus::Rect boundRect;
    gr->GetVisibleClipBounds(&boundRect);
    boundRect.GetSize(&sz);
}
int Graphics::hSize() { return sz.Width; }
int Graphics::vSize() { return sz.Height; }
