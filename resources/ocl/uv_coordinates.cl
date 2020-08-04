
#include "rt.hcl"

t_vec3	v3_cross(t_vec3 a, t_vec3 b)
{
	vec3 v;

	v.x = a.y * b.z - a.z * b.y;
	v.y = a.z * b.x - a.x * b.z;
	v.z = a.x * b.y - a.y * b.x;
	return (v);
}

static void get_sphere_uv(vec3 p)
{
	float2 uv;
	float phi;
	float theta;
	
	phi = atan2(p.z(), p.x());
	theta = asin(p.y());
	uv.x = 1 - (phi + M_PI) / (2 * M_PI);
	uv.y = (theta + M_PI / 2) / M_PI;
	return (uv);
}

static void get_cube_uv(vec3 p)
{
	float2 uv;

	if (fabs(p.x == 1))
	{
		uv.x = (p.z + 1.0f) / 2.0f;
		uv.y = (p.y + 1.0f) / 2.0f;
	}
	else if (fabs(y) == 1)
	{
		uv.x = (p.x + 1.0f) / 2.0f;
		uv.y = (p.z + 1.0f) / 2.0f;
	}
	else
	{
		uv.x = (p.x + 1.0f) / 2.0f;
		uv.y = (p.y + 1.0f) / 2.0f;
	}
	return (uv);
}

static void get_cylinder_uv(vec3 p, float height, float radius)
{
	float2 uv;

	uv.y = p.z / height;
	uv.x = acos(p.x / radius) / (2 * M_PI);
	if (p.y < 0)
		uv.x = 1 - uv.x;
	return (uv);
}

static void get_cone_uv(vec3 p, float height, float radius, float radius_on_height)
{
	float2 uv;

	uv.y = p.z / height;
	uv.x = (acos(p.x / radius + (radius_on_height - radius) * p.z / height)) / (2 * M_PI);
	if (p.y < 0)
		uv.x = 1 - uv.x;
	return (uv);
}

static void get_plane_uv(vec3 p, vec3 n)
{
	float2 uv;

	if (n.x != 0 && n.y != 0)
		uv.x = normalize((vec3){n.y, -n.x, 0.0f});
	else
		uv.x = normalize((vec3){c, c, 0.0f});
	uv.y = v3_cross(n, uv.x);
	uv.x = dot(uv.x, p);
	uv.y = dot(uv.y, p);
	return (uv);
}
