#include "FPS_Camera.h"
FPS_Camera::FPS_Camera(glm::vec3 _position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 _up = glm::vec3(0.0f, 1.0f, 0.0f), float _yaw = -90.f, float _pitch = 0.0f){
	position = _position;
	worldUp = _up;
	yaw = _yaw;
	pitch = _pitch;
	Update();
}

FPS_Camera::FPS_Camera(glm::vec3 _position){
	position = _position;
	worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	yaw = -90.f;
	pitch = 0.0f;
	Update();
}

float FPS_Camera::Zoom(){
	return zoom;
}


//Updates all variables before rendering
void FPS_Camera::Update(){
	glm::vec3 _front;
	_front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	_front.y = sin(glm::radians(pitch));
	_front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	forward = glm::normalize(_front);
	// Also re-calculate the Right and Up vector
	right = glm::normalize(glm::cross(forward, worldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	up = glm::normalize(glm::cross(right, forward));
}




// Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
void FPS_Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime){
	float velocity = movementSpeed * deltaTime;
	if (direction == FORWARD)
		position += forward * velocity;
	if (direction == BACKWARD)
		position -= forward * velocity;
	if (direction == LEFT)
		position -= right * velocity;
	if (direction == RIGHT)
		position += right * velocity;
}

// Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
void FPS_Camera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true){
	xoffset *= mouseSensitivity;
	yoffset *= mouseSensitivity;
	yaw += xoffset;
	pitch += yoffset;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (constrainPitch)	{
		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;
	}

	// Update Front, Right and Up Vectors using the updated Euler angles
	Update();
}

// Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
void FPS_Camera::ProcessMouseScroll(float yoffset){
	if (zoom >= 1.0f && zoom <= 45.0f)
		zoom -= yoffset;
	if (zoom <= 1.0f)
		zoom = 1.0f;
	if (zoom >= 45.0f)
		zoom = 45.0f;
}
