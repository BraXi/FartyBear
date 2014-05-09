/** underwater intro by matt deslauriers / mattdesl */

#ifdef GL_ES
precision mediump float;
#endif
 
uniform float time;
uniform vec2 resolution;
 
float hash( float n ){return fract( sin( n ) * 43758.5453 );}

float noise( in vec3 x ){
	vec3 p = floor( x );vec3 q = fract( x );
	q = q * q * (3.0 - 2.0 * q);
	float n = p.x + p.y * 57.0 + p.z * 113.0;
	float a = hash( n );float b = hash( n + 1.0 );float c = hash( n + 57.0 );float d = hash( n + 58.0 );
	float e = hash( n + 113.0 );float f = hash( n + 114.0 );float g = hash( n + 170.0 );float h = hash( n + 171.0 );	
	float result = mix( mix( mix( a, b, q.x ), mix( c, d, q.x ), q.y ), mix( mix( e, f, q.x ), mix( g, h, q.x ), q.y ), q.z );
	return result;
}

// rotation matrix, propotional to a right triangle, rotates octaves ~36°
const mat2 m = mat2( 0.8, 0.6, -0.6, 0.8 );

float fbm( in vec2 point )
{
	vec2 p = point;float f = 0.0;	
	//amplitude * noise( frequency )
	//f += 0.5000 * noise( vec3( p, 1.0 ) ); 
	p *= m * 2.02; // octaves...
	f += 0.2500 * noise( vec3( p, 1.0 ) ); 
	p *= m * 2.03;
	f += 0.1250 * noise( vec3( p, 1.0 ) ); p *= m * 2.01;
	f += 0.0625 * noise( vec3( p, 1.0 ) ); p *= m * 2.005;
	f += 0.03125 * noise( vec3( p, 1.0 ) ); p *= m * 2.00;
	f += 0.015625 * noise( vec3( p, 1.0 ) );
	f /= 0.984375-.5;
	return f;
}
float fbm(in float x, in float y){return fbm(vec2(x,y));}
void main( void ) {
 
	vec2 pos = ( gl_FragCoord.xy / resolution.xy );
	vec2 uv = pos;
	pos-=.5;
	pos*=2.;
	//pos.x+=mouse.y;
	vec4 col;
	
	
	col=vec4(.1,.3,.2,1.)*5.;
	float f = mix(0.0,fbm(pos.x/**mouse.x*5.*/,time*.3-pos.y/100.0),1.);
	
	f=mix(0.0,f,1.-abs(pos.y)*abs(pos.y)*abs(pos.y));
	//f=smoothstep(0.0,1.0)
	//f+=.1-abs(pos.y/10.);
	f=smoothstep(0.,1.,f);
	col*=f;//smoothstep(.0,1.0,f);
	
	
	
	
	col.a = 1.;
	gl_FragColor = col;
 
}

/*
//uniform vec2 resolution;
uniform float time;

#define PI 3.1416

vec3 dir(vec3 pos, float rotation) {
	
	return vec3(-0.5);	
}

void main(void)
{
	vec2 p = (gl_FragCoord.xy);// / resolution.xy;
	p.x += 0.58;
	p.y -= 0.61;
	vec2 center = vec2(0.5, 0.5);
	float d = distance(p, center);
	
		
	//bluish tint from top left
	vec3 color = vec3(1.0-d*0.75) * vec3(0.33, 0.35, 0.5);
	
	//add some green near centre
	color += (1.0-distance(p, vec2(1.0, 0.0))*1.)*0.5 * vec3(0.35, 0.65, 0.45);
	
	vec3 lightColor = vec3(0.3, 0.45, 0.65);
	
	//will be better as uniforms
	for (int i=0; i<3; i++) {
		//direction of light
		float zr = sin(time*0.15*float(i))*0.5 - PI/3.0;
		vec3 dir = vec3(cos(zr), sin(zr), 0.0);
		
		p.x -= 0.02;
		
		//normalized spotlight vector
		vec3 SpotDir = normalize(dir);
		
		//
		vec3 attenuation = vec3(0.5, 7.0, 10.0);
		float shadow = 1.0 / (attenuation.x + (attenuation.y*d) + (attenuation.z*d*d));

		vec3 pos = vec3(p, 0.0);
		vec3 delta = normalize(pos - vec3(center, 0.0));
		
		float cosOuterCone = cos(radians(1.0));
		float cosInnerCone = cos(radians(15.0 + float(i*2)));
		float cosDirection = dot(delta, SpotDir);
		
		//light...
		color += smoothstep(cosInnerCone, cosOuterCone, cosDirection) * shadow * lightColor;
	}
	color += sin(time*0.5)*0.05;
	gl_FragColor = vec4(vec3(color), 1.0);
}*/