#include <VisualizerWindow.h>
#include <Shader.h>
#include <wx/datetime.h>
#include <cmath>
#include <numbers>

// initialize static variables
int VisualizerCanvas::len = 5;
int VisualizerCanvas::dataVectorMaxLen = 75;
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

void VisualizerCanvas::GetCircularCoords(float* x, float* y, FreqData data) {
	float radius = 0.8 / (1 + data.size); // draw louder sounds closer to center
	float angle = 90 + (data.stereo_pos * -135); // center at 90 deg (top of circle) | range: +,- 135 degrees
	float radians = angle * std::numbers::pi / 180; // angle to radians for cos/sin functions

	*x = radius * cos(radians);
	*y = radius * sin(radians);
}

void VisualizerCanvas::Clear() {
	glClear(GL_COLOR_BUFFER_BIT);
	SwapBuffers();
}

/*
* Enter processed audio data, draw using OpenGL
*
* Each bucket is represented by a diamond.
* Position is left/right channel presence,
* Size is loudness,
*/
void VisualizerCanvas::Render()
{
	wxSize size = GetSize();
	SetCurrent(*gl_context);
	glViewport(0, 0, size.x * GetContentScaleFactor(), size.y * GetContentScaleFactor());
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0, 0, 0, 0); // background transparent

	// render differently based on layout
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
	int size = dataVector.size();
	for (int i = 0; i < size; ++i)
	{
		//translate and scale according to FreqData
		FreqData audioData;
		audioData = dataVector.at(i);

		// remove static noise when there's no audio
		if (audioData.size <= 0.0001) {
			continue;
		}

		// set diamond color based on amplitude
		VisualizerColor c;
		if (audioData.size <= VisualizerWindow::options->amplitudeThresholds[1]) {
			c = VisualizerWindow::options->amplitudeColors[0];
		}
		else if (audioData.size <= VisualizerWindow::options->amplitudeThresholds[2]) {
			c = VisualizerWindow::options->amplitudeColors[1];
		}
		else {
			c = VisualizerWindow::options->amplitudeColors[2];
		}
		c.a = 1.0f - (i * 1.0 / dataVectorMaxLen); // transparency based on age of data point

		// get rendering coords
		float x;
		float y;
		GetCircularCoords(&x, &y, audioData);

		// matrix last col: axis pos
		// matrix diagonal: axis size
		float transformation_mat[4][4] =
		{
			0.05f, 0.0f, 0.0f, x,
			0.0f, 0.05f, (1.0f) / ((float)len), y,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0 ,0.0f, 0.0f, 1.0f
		};

		shader->Use();
		//set transformation matrix uniform
		shader->setMat4("transform", transformation_mat);

		//set color uniform
		shader->setVec4("color", &c.r);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glDisable(GL_BLEND);
	}
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
