#include "rendering.hpp"

namespace rendering
{
	void c_renderer::draw_string(float x, float y, LPD3DXFONT pFont, D3DCOLOR color, int flags, bool outline, std::wstring text, ...) {
		va_list va_alist;
		wchar_t buf[1024];
		va_start(va_alist, text);
		_vsnwprintf(buf, sizeof(buf), text.c_str(), va_alist);
		va_end(va_alist);

		RECT rect;
		if (outline) {
			auto alpha = ((color >> 24) & 255);
			SetRect(&rect, x - 1, y, x - 1, y);
			pFont->DrawTextW(NULL, buf, -1, &rect, flags | DT_NOCLIP, D3DCOLOR_RGBA(0, 0, 0, alpha));
			SetRect(&rect, x + 1, y, x + 1, y);
			pFont->DrawTextW(NULL, buf, -1, &rect, flags | DT_NOCLIP, D3DCOLOR_RGBA(0, 0, 0, alpha));
			SetRect(&rect, x, y - 1, x, y - 1);
			pFont->DrawTextW(NULL, buf, -1, &rect, flags | DT_NOCLIP, D3DCOLOR_RGBA(0, 0, 0, alpha));
			SetRect(&rect, x, y + 1, x, y + 1);
			pFont->DrawTextW(NULL, buf, -1, &rect, flags | DT_NOCLIP, D3DCOLOR_RGBA(0, 0, 0, alpha));
		}
		SetRect(&rect, x, y, x, y);
		pFont->DrawTextW(NULL, buf, -1, &rect, flags | DT_NOCLIP, color);
	}

	void c_renderer::draw_filled_rect(float x, float y, float w, float h, D3DCOLOR col) {
		D3DXVECTOR2 vLine[2];
		d3d9::dx9_line->SetWidth(w);
		vLine[0].x = x + w / 2;
		vLine[0].y = y;
		vLine[1].x = x + w / 2;
		vLine[1].y = y + h;

		d3d9::dx9_line->Begin();
		d3d9::dx9_line->Draw(vLine, 2, col);
		d3d9::dx9_line->End();
	}

	void c_renderer::draw_line(float x, float y, float xx, float yy, D3DCOLOR col) {
		D3DXVECTOR2 line[2];
		d3d9::dx9_line->SetWidth(1);
		line[0] = D3DXVECTOR2(x, y);
		line[1] = D3DXVECTOR2(xx, yy);
		d3d9::dx9_line->Draw(line, 2, col);
	}

	void c_renderer::draw_rect(float x, float y, float width, float height, D3DCOLOR col) {
		D3DXVECTOR2 points[5];
		points[0] = D3DXVECTOR2(x, y);
		points[1] = D3DXVECTOR2(x + width, y);
		points[2] = D3DXVECTOR2(x + width, y + height);
		points[3] = D3DXVECTOR2(x, y + height);
		points[4] = D3DXVECTOR2(x, y);
		d3d9::dx9_line->SetWidth(1);
		d3d9::dx9_line->Draw(points, 5, col);
	}
}