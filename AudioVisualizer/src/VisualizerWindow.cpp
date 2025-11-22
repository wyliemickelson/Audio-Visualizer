#include <VisualizerWindow.h>
#include <Shader.h>

/*
* Enter processed audio data, draw using OpenGL
*
* Each bucket is represented by a circle.
* Position is left/right channel presence,
* Size is loudness,
* Color separates different frequency buckets.
*/
void VisualizerCanvas::Render(FreqData data)
{
	wxSize size = GetSize();
	glViewport(0, 0, size.x, size.y);
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.2f, 0.2f, 0.3f, 1.0f);

	//translate and scale according to FreqData
	float transformation_mat[4][4] =
	{
		data.size*.3f, 0.0f, 0.0f, data.stereo_pos,
		0.0f, 1.0f, data.size, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 
		0.0 ,0.0f, 0.0f, 1.0f
	};

	//set transformation matrix uniform
	shader->setMat4("transform", transformation_mat);

	float color[4] = { 0.3f, 0.3f, 0.3f, 1.0f };

	//set color uniform
	shader->setVec4("color", color);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	SwapBuffers();
}