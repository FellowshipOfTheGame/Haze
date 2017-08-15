#version 330 core

in vec2 UV;

out vec4 fragColor;

uniform sampler2D Screen;
uniform vec2 Resolution;

float sobel()
{
	vec3 horizontal = vec3(0.0), vertical = vec3(0.0);
	vec2 dist = vec2(0.5) / Resolution;
	vec2 displacement = vec2(-dist.x, -dist.y);
	mat3 coef;
	
	if(UV.x - dist.x > 0.0 && UV.x + dist.x < 1.0 && UV.y - dist.y > 0.0 && UV.y + dist.y < 1.0)
	{
		coef[0][0] = 1.0; coef[0][1] = 0.0; coef[0][2] = -1.0;
		coef[1][0] = 2.0; coef[1][1] = 0.0; coef[1][2] = -2.0;
		coef[2][0] = 1.0; coef[2][1] = 0.0; coef[2][2] = -1.0;
		for(int x = 0; x < 3; x++)
		{
			displacement.y = -dist.y;
			for(int y = 0; y < 3; y++)
			{
				horizontal = horizontal + coef[x][y] * texture(Screen, UV + displacement).rgb;
				displacement.y += dist.y;
			}
			displacement.x += dist.x;
		}
		
		coef[0][0] = 1.0; coef[0][1] = 2.0; coef[0][2] = 1.0;
		coef[1][0] = 0.0; coef[1][1] = 0.0; coef[1][2] = 0.0;
		coef[2][0] = -1.0; coef[2][1] = -2.0; coef[2][2] = -1.0;

		for(int x = 0; x < 3; x++)
		{
			displacement.y = -dist.y;
			for(int y = 0; y < 3; y++)
			{
				vertical = vertical + coef[x][y] * texture(Screen, UV + displacement).rgb;
				displacement.y += dist.y;
			}
			displacement.x += dist.x;
		}
		horizontal = horizontal * horizontal;
		vertical = vertical * vertical;
		
		float sob = distance(sqrt(horizontal + vertical), vec3(0.0));
		
		return clamp(sob, 0.0, 1.0);
	}
	return 0.0;
}

void main()
{
	vec4 frame = texture(Screen, UV);
    vec3 col = frame.rgb;
	float sob = sobel();
	
	
    fragColor = vec4(clamp(col - vec3(sob), vec3(0.0), vec3(1.0)), frame.a);
} 