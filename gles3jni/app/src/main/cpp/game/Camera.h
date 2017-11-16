#ifndef GLES3JNI_CAMERA_H
#define GLES3JNI_CAMERA_H

#include "../glm/glm.hpp"
#include "Rectangle.h"

class Camera {
public:
	Camera();
	~Camera();

	/// Moves the camera to the target location. In pixels.
	void move(glm::vec2 position);
	/// Offsets the camera from its current position by "delta" amount. In pixels.
	void moveBy(glm::vec2 delta);

	/// Returns the position of the camera as a 2D vector with pixels as units.
	inline glm::vec2 getPosition() { return position; }
	/// Returns the x-coordinate of the camera in pixels.
	inline float getX() { return position.x; }
	/// Returns the y-coordinate of the camera in pixels.
	inline float getY() { return position.y; }
	/// Returns the view-scaling multiplier.
	inline float getZoom() { return zoom; }
	/// Sets a new value for how much the view should be scaled.
	inline void setZoom(float zoom) { this->zoom = zoom; }

private:
	/// In pixels.
	glm::vec2 position = {0, 0};
	/// How much the view is scaled, as a simple multiplier.
	float zoom = 1.0f;
};

#endif //GLES3JNI_CAMERA_H
