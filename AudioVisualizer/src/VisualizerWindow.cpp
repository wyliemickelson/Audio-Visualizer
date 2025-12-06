#include <VisualizerWindow.h>
#include <Shader.h>
#include <wx/datetime.h>
#include <cmath>
#include <numbers>

void VisualizerCanvas::OnSize(wxSizeEvent& event)
{
	wxSize size = GetSize();
	glViewport(0, 0, size.x, size.y);
}
void VisualizerWindow::OnSize(wxSizeEvent& event)
{
	canvas->SetSize(GetSize());
}
void VisualizerWindow::OnClose(wxCloseEvent& event)
{
	canvas->Close(true);
	Close(true);
}

int VisualizerCanvas::len = 5;
int VisualizerCanvas::dataVectorMaxLen = 50;
std::vector<FreqData> VisualizerCanvas::dataVector;
FreqData* VisualizerCanvas::data = new FreqData[5];
const Color colors[5] =
{
Color(0.8f, 0.6f, 0.9f, 1.0f),
Color(0.74f, 0.17f, 0.39f, 1.0f),
Color(0.9, 0.2f, 0.2f, 1.0f),
Color(1.0f, 0.5f, 0.2f, 1.0f),
Color(1.0f, 0.70f, 0.3f, 1.0f)
};

void VisualizerCanvas::GetCircularCoords(float radius, float* x, float* y, FreqData data) {
	// middle direction = 90 degrees
	// range: +,- 150 degrees from 90
	float angle = 90 + (data.stereo_pos * -150);
	float radians = angle * std::numbers::pi / 180;

	*x = radius * cos(radians);
	*y = radius * sin(radians);
}

/*
* Enter processed audio data, draw using OpenGL
*
* Each bucket is represented by a diamond.
* Position is left/right channel presence,
* Size is loudness,
* Color separates different frequency buckets.
*/
void VisualizerCanvas::Render()
{
	wxSize size = GetSize();
	SetCurrent(*gl_context);
	glViewport(0, 0, size.x * GetContentScaleFactor(), size.y * GetContentScaleFactor());
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0, 0, 0, 0); //transparent

	//int len = this->len;
	//FreqData* data = nullptr;

	//iterate each bucket and draw as separate diamond (bar visualizer)
	//for (int i = 0; i < len; ++i)
	//{
		//translate and scale according to FreqData
	//	FreqData bucket = data[i];
	//	//std::cout << "Size: " << bucket.size << std::endl;
	//	//std::cout << "Pos: " << bucket.stereo_pos << std::endl;

		//float transformation_mat[4][4] =
		//{
		//	std::min(bucket.size, 0.5f), 0.0f, 0.0f, bucket.stereo_pos,
		//	0.0f, 1.0f, (1.0f)/ ((float)len), (((2.0f) / (float)len) * (i)) - ((5.0f / (float)len)),
		//	0.0f, 0.0f, 1.0f, 0.0f,
		//	0.0 ,0.0f, 0.0f, 1.0f
		//};

	//	shader->Use();
	//	//set transformation matrix uniform
	//	shader->setMat4("transform", transformation_mat);

	//	Color color = colors[i % 5];


	//	//set color uniform
	//	shader->setVec4("color", &color.r);

	//	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	//	int g = 0;
	//}

	const Color volumeColors[3] =
	{
		Color(0, 1, 0, 1.0f), // quiet
		Color(1, 1, 0, 1.0f), // medium
		Color(1, 0, 0, 1.0f), // loud
	};

	for (int i = 0; i < dataVectorMaxLen; ++i)
	{
		//translate and scale according to FreqData
		FreqData bucket;
		try {
			bucket = dataVector.at(i);
			//std::cout << "Size: " << bucket.size << std::endl;
			//std::cout << "Pos: " << bucket.stereo_pos << std::endl;

			if (bucket.size <= 0.0001) {
				continue;
			}

			Color c;
			float radius = 0.5;
			if (bucket.size <= 0.01) {
				c = volumeColors[0];
			}
			else if (bucket.size <= 0.1) {
				c = volumeColors[1];
				radius /= 1.05;
			}
			else {
				c = volumeColors[2];
				radius /= 1.1;
			}
			c.a = 1.0f - (i * 1.0 / dataVectorMaxLen);

			float x;
			float y;
			GetCircularCoords(radius, &x, &y, bucket);

			float transformation_mat[4][4] =
			{
				0.03f, 0.0f, 0.0f, x,
				0.0f, 0.03f, (1.0f) / ((float)len), y,
				0.0f, 0.0f, 1.0f, 0.0f,
				0.0 ,0.0f, 0.0f, 1.0f
			};

			shader->Use();
			//set transformation matrix uniform
			shader->setMat4("transform", transformation_mat);

			//std::cout << "a: " << c.a << std::endl;


			//set color uniform
			shader->setVec4("color", &c.r);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			glDisable(GL_BLEND);

			int g = 0;
			//}
		}
		catch (const std::out_of_range) {
			continue;
		}
	}

	SwapBuffers();
}
