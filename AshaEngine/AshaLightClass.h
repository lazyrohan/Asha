//AshaLightClass.h

#ifndef _ASHALIGHTCLASS_H_
#define _ASHALIGHTCLASS_H_

//Include header files
#include <d3d11.h>
#include <DirectXMath.h>
using namespace DirectX;

struct AshaLight
{
	//XMFLOAT4 startPos;
	//XMFLOAT4 endPos;
	XMFLOAT4 direction;
	XMFLOAT3 color;
	float    intensity;
};


class AshaLightClass
{
	/*
	//Kinds of lights types structure
	struct DirectionalLight
	{
		DirectionalLight() { ZeroMemory(this, sizeof(this)); }

		XMFLOAT4 Ambient;
		XMFLOAT4 Diffuse;
		XMFLOAT4 Specular;
		XMFLOAT3 Direction;
		float Pad; // Pad the last float so we can set an array of lights if we wanted.
	};

	struct PointLight
	{
		PointLight() { ZeroMemory(this, sizeof(this)); }

		XMFLOAT4 Ambient;
		XMFLOAT4 Diffuse;
		XMFLOAT4 Specular;

		// Packed into 4D vector: (Position, Range)
		XMFLOAT3 Position;
		float Range;

		// Packed into 4D vector: (A0, A1, A2, Pad)
		XMFLOAT3 Att;
		float Pad; // Pad the last float so we can set an array of lights if we wanted.
	};

	struct SpotLight
	{
		SpotLight() { ZeroMemory(this, sizeof(this)); }

		XMFLOAT4 Ambient;
		XMFLOAT4 Diffuse;
		XMFLOAT4 Specular;

		// Packed into 4D vector: (Position, Range)
		XMFLOAT3 Position;
		float Range;

		// Packed into 4D vector: (Direction, Spot)
		XMFLOAT3 Direction;
		float Spot;

		// Packed into 4D vector: (Att, Pad)
		XMFLOAT3 Att;
		float Pad; // Pad the last float so we can set an array of lights if we wanted.
	};

	struct Material
	{
		Material() { ZeroMemory(this, sizeof(this)); }

		XMFLOAT4 Ambient;
		XMFLOAT4 Diffuse;
		XMFLOAT4 Specular; // w = SpecPower
		XMFLOAT4 Reflect;
	};
	*/

public:
	//Light type flags for changing parameters
	enum AshaLightType
	{
		ASHA_LIGHT_TYPE_DIRCTIONAL=0,
		ASHA_LIGHT_TYPE_POINT=1,
		ASHA_LIGHT_TYPE_SPOT=2
	};


public:
	AshaLightClass(void);
	virtual ~AshaLightClass(void);

public:
	void                Initialize();

	//Light type operation
	void                SetLightType(AshaLightType lightType);
	AshaLightType       GetLightType(void) const;

private:

	//Light parameters
	//Light type
	AshaLightType       m_aType;
	//Light position
	XMVECTOR            m_xPos;
	float               m_fRange;
	//Light shoot direction
	XMVECTOR            m_xShootDirction;

	//Color info.
	XMVECTOR            m_xAmbientColor;
	XMVECTOR            m_xDiffuseColor;
	XMVECTOR            m_xSpecularColor;
};

#endif
