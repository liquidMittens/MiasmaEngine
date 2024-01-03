#version 450 core
layout (location = 0) in vec2 fragmentTexCoord;
uniform sampler2D textureSample;
uniform int currentFrameIndex;
uniform int MAX_COLUMNS;
uniform int MAX_ROWS;
out vec4 finalColor;

void main()
{
    vec2 pos = vec2(currentFrameIndex % int(MAX_COLUMNS), int(currentFrameIndex / MAX_COLUMNS));
    finalColor = texture(textureSample, vec2((fragmentTexCoord.x / MAX_COLUMNS) + pos.x * (1.0 / MAX_COLUMNS),
        (fragmentTexCoord.y / MAX_ROWS) + pos.y * (1.0 / MAX_ROWS)));
    if(finalColor.a <= 0.1f)
		discard;
}