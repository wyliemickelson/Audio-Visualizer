#include <VisualizerWindow.h>
#include <Shader.h>
#include <wx/datetime.h>
#include <cmath>

int VisualizerCanvas::len = 5;
FreqData* VisualizerCanvas::data = new FreqData[5];


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
	glClearColor(0.2f, 0.2f, 0.3f, 1.0f);

	//int len = this->len;
	//FreqData* data = nullptr;

	//iterate each bucket and draw as separate diamond
	for (int i = 0; i < len; ++i)
	{
		int e = 0;
		//translate and scale according to FreqData
		FreqData bucket = data[i];
		float transformation_mat[4][4] =
		{
			std::min(bucket.size, 0.5f), 0.0f, 0.0f, bucket.stereo_pos,
			0.0f, 1.0f, std::min(bucket.size, (0.2f)), -((1.0f / (float)len) * i) + ((0.5f) / (float)len),
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0 ,0.0f, 0.0f, 1.0f
		};

		shader->Use();
		//set transformation matrix uniform
		shader->setMat4("transform", transformation_mat);

		float color[4];
		color[0] = 1.0f;
		color[1] = 1.0f;
		color[2] = 1.0f;
		color[3] = 1.0f;

		//set color uniform
		shader->setVec4("color", color);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		int g = 0;
	}
	SwapBuffers();

}