#include <VisualizerWindow.h>
#include <Shader.h>
#include <wx/datetime.h>
#include <cmath>

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
int VisualizerCanvas::dataVectorMaxLen = 1000;
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

	//iterate each bucket and draw as separate diamond
	for (int i = 0; i < len; ++i)
	{
		//translate and scale according to FreqData
		FreqData bucket = data[i];
		//std::cout << "Size: " << bucket.size << std::endl;
		//std::cout << "Pos: " << bucket.stereo_pos << std::endl;

		float transformation_mat[4][4] =
		{
			std::min(bucket.size, 0.5f), 0.0f, 0.0f, bucket.stereo_pos,
			0.0f, 1.0f, (1.0f)/ ((float)len), (((2.0f) / (float)len) * (i)) - ((5.0f / (float)len)),
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0 ,0.0f, 0.0f, 1.0f
		};

		shader->Use();
		//set transformation matrix uniform
		shader->setMat4("transform", transformation_mat);

		Color color = colors[i % 5];


		//set color uniform
		shader->setVec4("color", &color.r);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		int g = 0;
	}
	SwapBuffers();

}