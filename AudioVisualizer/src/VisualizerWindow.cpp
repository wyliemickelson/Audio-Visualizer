#include <VisualizerWindow.h>
#include <Shader.h>
#include <wx/datetime.h>
#include <cmath>
#include <numbers>

// initialize static variables
int VisualizerCanvas::len = 5;
int VisualizerCanvas::dataVectorMaxLen = 50;
VisualizerOptions* VisualizerWindow::options;
std::vector<FreqData> VisualizerCanvas::dataVector;
FreqData* VisualizerCanvas::data = new FreqData[5];

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

	switch (VisualizerWindow::options->layout) {
		case CIRCULAR:
			RenderCircular();
			break;
		case HORIZONTAL:
			RenderHorizontal();
			break;
	}

	SwapBuffers();
}

void VisualizerCanvas::RenderCircular() {
	for (int i = 0; i < dataVectorMaxLen; ++i)
	{
		//translate and scale according to FreqData
		FreqData audioData;
		try {
			audioData = dataVector.at(i);
			//std::cout << "Size: " << audioData.size << std::endl;
			//std::cout << "Pos: " << audioData.stereo_pos << std::endl;

			if (audioData.size <= 0.0001) {
				continue;
			}

			VisualizerColor c;
			float radius = 0.5;
			if (audioData.size <= VisualizerWindow::options->amplitudeThresholds[1]) {
				c = VisualizerWindow::options->amplitudeColors[0];
			}
			else if (audioData.size <= VisualizerWindow::options->amplitudeThresholds[2]) {
				c = VisualizerWindow::options->amplitudeColors[1];
				radius /= 1.05;
			}
			else {
				c = VisualizerWindow::options->amplitudeColors[2];
				radius /= 1.1;
			}
			c.a = 1.0f - (i * 1.0 / dataVectorMaxLen);

			float x;
			float y;
			GetCircularCoords(radius, &x, &y, audioData);

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
		}
		catch (const std::out_of_range) {
			continue;
		}
	}

	return;
}

void VisualizerCanvas::RenderHorizontal() {
	int len = this->len;
	FreqData* data = this->data;

	//iterate each bucket and draw as separate diamond (bar visualizer)
	for (int i = 0; i < len; ++i)
	{
		//translate and scale according to FreqData
		FreqData bucket = data[i];
		//std::cout << "Size: " << bucket.size << std::endl;
		//std::cout << "Pos: " << bucket.stereo_pos << std::endl;

		float transformation_mat[4][4] =
		{
			std::min(bucket.size, 0.5f), 0.0f, 0.0f, bucket.stereo_pos,
			0.0f, 1.0f, (1.0f) / ((float)len), (((2.0f) / (float)len) * (i)) - ((5.0f / (float)len)),
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0 ,0.0f, 0.0f, 1.0f
		};

		shader->Use();
		//set transformation matrix uniform
		shader->setMat4("transform", transformation_mat);

		VisualizerColor color = VisualizerWindow::options->frequencyColors[i % 5];


		//set color uniform
		shader->setVec4("color", &color.r);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		int g = 0;
	}
	return;
}
