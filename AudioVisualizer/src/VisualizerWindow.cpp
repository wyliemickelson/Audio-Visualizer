#include <VisualizerWindow.h>
#include <Shader.h>
#include <wx/datetime.h>
#include <cmath>

int VisualizerCanvas::len = 0;
FreqData* VisualizerCanvas::data = nullptr;


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
			bucket.size, 0.0f, 0.0f, bucket.stereo_pos,
			0.0f, 1.0f, bucket.size, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0 ,0.0f, 0.0f, 1.0f
		};

		shader->Use();
		e = glGetError();
		//set transformation matrix uniform
		shader->setMat4("transform", transformation_mat);
		e = glGetError();

		float color[4] = { bucket.color.r, bucket.color.g, bucket.color.b, bucket.color.a };

		//set color uniform
		shader->setVec4("color", color);
		e = glGetError();

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		e = glGetError();
		int g = 0;
	}
	SwapBuffers();

}