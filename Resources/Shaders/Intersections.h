
struct SDF
{
	mediump uint StepAndMatID;
};
struct VoxelTree
{
	vec4 minAABB;
	vec4 maxAABB;
	uint GpuBufferStart;
	uint GpuBufferEnd;
};

float max3 (vec3 v) {
  return max (max (v.x, v.y), v.z);
}

float min3 (vec3 v) {
  return min (min (v.x, v.y), v.z);
}


vec4 slabsNormals(vec3 origin, vec3 rayDir, vec3 minBox, vec3 maxBox)
{
	vec3 t0 = (maxBox - origin.xyz) / rayDir;
	vec3 t1 = (minBox - origin.xyz) / rayDir;
	vec3 tmin = min(t0,t1), tmax = max(t0,t1);

	vec2 t = vec2(max3(tmin), min3(tmax));


	return t.x <= t.y ? 
		vec4(-sign(rayDir) * step(tmin.yzx, tmin.xyz) * step(tmin.zxy, tmin.xyz), t.x) //normal
		: vec4(-1.0);
}



float slabs(vec3 origin, vec3 rayDir, vec3 minBox, vec3 maxBox)
{
	vec3 t0 = (maxBox - origin.xyz) / rayDir;
	vec3 t1 = (minBox - origin.xyz) / rayDir;
	vec3 tmin = min(t0, t1), tmax = max(t0, t1);

	vec2 t = vec2(max3(tmin), min3(tmax));


	return t.x <= t.y ? t.x : -1.0;
}
