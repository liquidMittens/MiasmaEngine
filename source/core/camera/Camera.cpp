/*
 tdogl::Camera

 Copyright 2012 Thomas Dalling - http://tomdalling.com/

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 */
#define _USE_MATH_DEFINES
#include <cmath>
#include "camera/Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include "objects/GameObject.h"

using namespace tdogl;

static const float MaxVerticalAngle = 85.0f; //must be less than 90 to avoid gimbal lock

CLASS_DEFINITION(Component, Camera);

Camera::Camera(GameObject* owner) :
    Component(owner, TO_STRING(Camera)),
    _position(0.0f, 0.0f, 1.0f),
    _horizontalAngle(0.0f),
    _verticalAngle(0.0f),
    _fieldOfView(45.0f),
    _nearPlane(0.1f),
    _farPlane(1000.0f),
    _viewportAspectRatio(4.0f/3.0f),
    _orthoMatrix(0.0f),
    _viewport(800.0f, 600.0f)
{
}

Camera::~Camera()
{

}

void Camera::Start()
{

}

void Camera::Update(float dt)
{
    //_position = gameObject->transform.GetPosition();
    //_position.y += CAMERA_HEIGHT_OFFSET;
    //std::cout << std::format("RigidBody({}:{}): pos: ({},{},{})\n", gameObject->tag, "Dynamic", gameObject->transform.GetPosition().x, gameObject->transform.GetPosition().y, gameObject->transform.GetPosition().z);
}

void Camera::Shutdown()
{

}

const glm::vec3& Camera::position() const {
    //return _position;
    return gameObject->transform.GetPosition();
}

void Camera::setPosition(const glm::vec3& position) {
    _position = position;
    gameObject->transform.SetPosition(position);
}

void Camera::offsetPosition(const glm::vec3& offset) {
    //_position += offset;
    gameObject->transform.translate(offset);
}

float Camera::fieldOfView() const {
    return _fieldOfView;
}

void Camera::setFieldOfView(float fieldOfView) {
    assert(fieldOfView > 0.0f && fieldOfView < 180.0f);
    _fieldOfView = fieldOfView;
}

float Camera::nearPlane() const {
    return _nearPlane;
}

float Camera::farPlane() const {
    return _farPlane;
}

void Camera::setNearAndFarPlanes(float nearPlane, float farPlane) {
    assert(nearPlane > 0.0f);
    assert(farPlane > nearPlane);
    _nearPlane = nearPlane;
    _farPlane = farPlane;
}

glm::mat4 Camera::orientation() const {
    glm::mat4 orientation(1.0f);
    orientation = glm::rotate(orientation, glm::radians(_verticalAngle), glm::vec3(1,0,0));
    orientation = glm::rotate(orientation, glm::radians(_horizontalAngle), glm::vec3(0,1,0));
    return orientation;
}

void Camera::offsetOrientation(float upAngle, float rightAngle) {
    _horizontalAngle += rightAngle;
    _verticalAngle += upAngle;
    normalizeAngles();
}

void Camera::lookAt(glm::vec3 position) {
    assert(position != gameObject->transform.GetPosition());
    glm::vec3 direction = glm::normalize(position - gameObject->transform.GetPosition());
    _verticalAngle = glm::radians(asinf(-direction.y));
    _horizontalAngle = -glm::radians(atan2f(-direction.x, -direction.z));
    normalizeAngles();
}

float Camera::viewportAspectRatio() const {
    return _viewportAspectRatio;
}

void Camera::setViewportAspectRatio(float viewportAspectRatio) {
    assert(viewportAspectRatio > 0.0);
    _viewportAspectRatio = viewportAspectRatio;
}

glm::vec3 Camera::forward() const {
    glm::vec4 forward = glm::inverse(orientation()) * glm::vec4(0,0,-1,1);
    return glm::vec3(forward);
}

glm::vec3 Camera::forward_novertical_axis() const
{
    glm::mat4 orientation(1.0f);
    orientation = glm::rotate(orientation, glm::radians(_horizontalAngle), glm::vec3(0, 1, 0));
    glm::vec4 forward = glm::inverse(orientation) * glm::vec4(0, 0, -1, 1);
    return glm::vec3(forward);
}

glm::vec3 Camera::right() const {
    glm::vec4 right = glm::inverse(orientation()) * glm::vec4(1,0,0,1);
    return glm::vec3(right);
}

glm::vec3 Camera::up() const {
    glm::vec4 up = glm::inverse(orientation()) * glm::vec4(0,1,0,1);
    return glm::vec3(up);
}

glm::vec3 Camera::up_novertical_axis() const
{
    glm::mat4 orientation(1.0f);
    orientation = glm::rotate(orientation, glm::radians(_horizontalAngle), glm::vec3(0, 1, 0));
    glm::vec4 up = glm::vec4(0, 1, 0, 1);
    return glm::vec3(up);
}

glm::mat4 Camera::matrix() const {
    return projection() * view();
}

glm::mat4 Camera::orthomatrix() const {
    return _orthoMatrix;
}

glm::mat4 Camera::projection() const {
    return glm::perspective(glm::radians(_fieldOfView), _viewportAspectRatio, _nearPlane, _farPlane);
}

glm::mat4 Camera::view() const {
    return orientation() * glm::translate(glm::mat4(1.0f), -gameObject->transform.GetPosition());
}

glm::vec2 Camera::viewport() const
{
    return _viewport;
}

void Camera::normalizeAngles() {
    _horizontalAngle = fmodf(_horizontalAngle, 360.0f);
    //fmodf can return negative values, but this will make them all positive
    if(_horizontalAngle < 0.0f)
        _horizontalAngle += 360.0f;

    if(_verticalAngle > MaxVerticalAngle)
        _verticalAngle = MaxVerticalAngle;
    else if(_verticalAngle < -MaxVerticalAngle)
        _verticalAngle = -MaxVerticalAngle;
}

void Camera::initcamera(float fov, float near, float far, glm::vec3 pos, glm::vec2 screenSize) {
	setFieldOfView(fov);
	setNearAndFarPlanes(near, far);
	setPosition(pos);
	setViewportAspectRatio(screenSize.x / screenSize.y);
    _viewport = screenSize;
    _orthoMatrix = glm::ortho(0.0f, screenSize.x, screenSize.y, 0.0f, -1.0f, 1.0f);
}