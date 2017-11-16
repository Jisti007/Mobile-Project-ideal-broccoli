#ifndef GLES3JNI_CAMERA_H
#define GLES3JNI_CAMERA_H

#include "../glm/glm.hpp"
#include "Rectangle.h"

/// Controls view behaviors like position and zoom.
/// Positional measurements are in hexes.
/// Zoom is a simple multiplier.
class Camera {
public:
	Camera();
	~Camera();

	/// Moves the camera to the target location.
	void move(glm::vec2 position);
	/// Offsets the camera from its current position by "delta" amount.
	void moveBy(glm::vec2 delta);
	/// Sets a new value for how much the view should be scaled.
	void setZoom(float zoom);

	/// Returns the position of the camera as a 2D vector.
	inline glm::vec2 getPosition() { return position; }
	inline void setMinPosition(glm::vec2 minPosition) { this->minPosition = minPosition; }
	inline void setMaxPosition(glm::vec2 maxPosition) { this->maxPosition = maxPosition; }
	/// Returns the x-coordinate of the camera.
	inline float getX() { return position.x; }
	/// Returns the y-coordinate of the camera.
	inline float getY() { return position.y; }
	/// Returns the view-scaling multiplier.
	inline float getZoom() { return zoom; }
	/// Multiplies the zoom value by the given multiplier.
	inline void scaleZoom(float multiplier) { setZoom(zoom * multiplier); }

private:
	glm::vec2 position = {0, 0};
	glm::vec2 minPosition = {0, 0};
	glm::vec2 maxPosition = {100, 100};
	/// How much the view is scaled, as a simple multiplier.
	float zoom = 1.0f;
	float maxZoom = 2.0f;
	float minZoom = 0.5f;
};

#endif //GLES3JNI_CAMERA_H
